# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 22:29:16 2020

@author: DzL
"""

import torch
import torch.nn as nn
import torchtext
from torchtext import datasets
from torchtext.data import Field
from tqdm import tqdm
import numpy as np
from torch.nn.utils import clip_grad_norm_
from torch.autograd import Variable as V
import matplotlib.pyplot as plt
import TTLSTMFull

def plot_figure(x_axis,y_axis):
    plt.title("Testing Status")
    plt.plot(x_axis, y_axis, color="r", linestyle="-", linewidth=1.0)
    plt.xlabel("Testing epochs")
    plt.ylabel("Perplexity")
    plt.show()

class LSTM_model(nn.Module):
    def __init__(self,vocab_num,input_dim,hidden_dim,num_layers):
        super(LSTM_model,self).__init__()
        self.embed=nn.Embedding(vocab_num,input_dim)
        self.lstm=nn.LSTM(input_dim,hidden_dim,num_layers)
        self.decoder=nn.Linear(hidden_dim,vocab_num)

    def forward(self,x):
        x=self.embed(x)
        #out,(h,c)=self.lstm(x,h)
        out,states=self.lstm(x)
        out = out.reshape(out.size(0) * out.size(1), out.size(2))
        out=self.decoder(out)
        #return out,(h,c)
        return out

class RNNModel(nn.Module):
    def __init__(self, ntoken, ninp,
                 nhid, nlayers, bsz,
                 dropout=0.5, tie_weights=True):
        super(RNNModel, self).__init__()
        self.nhid, self.nlayers, self.bsz = nhid, nlayers, bsz
        self.drop = nn.Dropout(dropout)
        self.encoder = nn.Embedding(ntoken, ninp)
        #self.rnn = nn.LSTM(ninp, nhid, nlayers, dropout=dropout)
        self.concat_tt_shape=[10,6,5,10]
        self.output_tt_shape=[10,6,5,5]
        self.tt_1_ranks=[1,10,10,10,1]
        self.tt_2_ranks=[1,20,20,20,1]
        self.tt_1=TTLSTMFull.TTLSTMFullCell(self.concat_tt_shape,self.output_tt_shape,self.tt_1_ranks)
        self.tt_2=TTLSTMFull.TTLSTMFullCell(self.concat_tt_shape,self.output_tt_shape,self.tt_2_ranks)
        self.decoder = nn.Linear(nhid, ntoken)
        self.init_weights()
        self.hidden = self.init_hidden(bsz)  # the input is a batched consecutive corpus
        # therefore, we retain the hidden state across batches

    def init_weights(self):
        initrange = 0.1
        self.encoder.weight.data.uniform_(-initrange, initrange)
        self.decoder.bias.data.fill_(0)
        self.decoder.weight.data.uniform_(-initrange, initrange)

    def forward(self, input):
        emb = self.drop(self.encoder(input))
        #output, self.hidden = self.rnn(emb, self.hidden)
        hidden = self.tt_1(emb)
        hidden=self.drop(hidden)
        output =self.tt_2(hidden)
        output = self.drop(output)
        decoded = self.decoder(output.view(output.size(0) * output.size(1), output.size(2)))
        return decoded.view(output.size(0), output.size(1), decoded.size(1))

    def init_hidden(self, bsz):
        weight = next(self.parameters()).data
        return (V(weight.new(self.nlayers, bsz, self.nhid).zero_().cuda()),
                V(weight.new(self.nlayers, bsz, self.nhid).zero_()).cuda())

    def reset_history(self):
        self.hidden = tuple(V(v.data) for v in self.hidden)
        #self.tt_1.reset_parameters()
        #self.tt_2.reset_parameters()

def get_parameter_number(net):
    total_num = sum(p.numel() for p in net.parameters())
    trainable_num = sum(p.numel() for p in net.parameters() if p.requires_grad)
    return {'Total parameter number': total_num, 'Trainable parameter number': trainable_num}

def main():
    #hyper parameters
    device = torch.device("cuda")
    # load PTB dataset
    batch_size = 20
    learning_rate=0.009 #should be 30
    epochs=40
    #torch.manual_seed(141)
    #preparing datasets
    TEXT=Field(sequential=True,eos_token=True,unk_token=True,pad_token=False)
    train,valid,test = datasets.PennTreebank.splits(root='./data',text_field=TEXT, train='ptb.train.txt', validation='ptb.valid.txt', test='ptb.test.txt')
    TEXT.build_vocab(train)
    train_iter, valid_iter, test_iter = torchtext.data.BPTTIterator.splits(
        (train, valid, test),
        batch_size=batch_size,
        bptt_len=35,  # this is where we specify the sequence length
        device=device,
        repeat=False)
    #train_iter,valid_iter,test_iter=datasets.PennTreebank.iters(batch_size=1328,bptt_len=35,device=device,root='./data')
    #apply models, loss functions and optimizer
    #model=LSTM_model(10002,1500,1500,2).to(device)
    model=RNNModel(10002,1500,1500,2,20,dropout=0.65).to(device) #Dropout rate should be 0.65
    #model.load_state_dict(torch.load("./Long_trained.pt"))
    print(get_parameter_number(model))
    loss_function=nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    #Do training
    Epoch_idxs=[]
    testing_status = []
    for epoch in range(1,epochs+1):
        """
        if epoch > 14:
            learning_rate=learning_rate/1.15
            optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
        """
        model.train()
        for batch in tqdm(train_iter):
            model.reset_history()
            model.zero_grad()
            text, target = batch.text, batch.target
            optimizer.zero_grad()
            output = model(text)
            loss = loss_function(output.view(-1,10002), torch.squeeze(target.view(-1)))
            loss.backward()
            clip_grad_norm_(model.parameters(), 0.25)
            #for p in model.parameters():
            #    p.data.add_(-learning_rate, p.grad.data)
            optimizer.step()

        #Test validation set
        model.eval()
        valid_sum_loss=0
        valid_perplexities=[]

        with torch.no_grad():
            for valids in valid_iter:
                model.reset_history()
                text, target = valids.text,valids.target
                output = model(text)
                loss = loss_function(output.view(-1, 10002), target.view(-1))
                valid_sum_loss+=loss.item()
                perplexity=np.exp(loss.item())
                valid_perplexities.append(perplexity)
        valid_avg=np.exp(valid_sum_loss/len(valid_iter))

        print('\nEpoch: {}/{}, Validation set average perplexity:{:5.2f}\n'
            .format(epoch, epochs, valid_avg))

        #Do testing every epoch
        model.eval()
        perplexitis=[]
        sum_loss=0
        with torch.no_grad():
            for tests in test_iter:
                model.reset_history()
                text, target = tests.text,tests.target
                output = model(text)
                #loss = loss_function(output, target.reshape(-1))  # sum up batch loss
                loss = loss_function(output.view(-1, 10002), torch.squeeze(target.view(-1)))
                sum_loss+=loss.item()
                perplexity=np.exp(loss.item())
                perplexitis.append(perplexity)
        low=min(perplexitis)
        high=max(perplexitis)
        avg=np.exp(sum_loss/len(test_iter))
        testing_status.append(avg)

        print('\nEpoch: {}/{}, Lowest perplexity: {:5.2f}, Highest perplexity:{:5.2f}, Test set average perplexity:{:5.2f}\n'
            .format(epoch, epochs, low, high, avg))
        Epoch_idxs.append(epoch)
    #calculating parameter number
    torch.save(model.state_dict(), "./Long_trained.pt")
    para_num = get_parameter_number(model)
    print(para_num)
    plot_figure(Epoch_idxs,testing_status)

if __name__=="__main__":
    main()