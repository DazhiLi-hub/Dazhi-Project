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
        self.rnn = nn.LSTM(ninp, nhid, nlayers, dropout=dropout)
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
        output, self.hidden = self.rnn(emb, self.hidden)
        output = self.drop(output)
        decoded = self.decoder(output.view(output.size(0) * output.size(1), output.size(2)))
        return decoded.view(output.size(0), output.size(1), decoded.size(1))

    def init_hidden(self, bsz):
        weight = next(self.parameters()).data
        return (V(weight.new(self.nlayers, bsz, self.nhid).zero_().cuda()),
                V(weight.new(self.nlayers, bsz, self.nhid).zero_()).cuda())

    def reset_history(self):
        self.hidden = tuple(V(v.data) for v in self.hidden)

def get_parameter_number(net):
    total_num = sum(p.numel() for p in net.parameters())
    trainable_num = sum(p.numel() for p in net.parameters() if p.requires_grad)
    return {'Total parameter number': total_num, 'Trainable parameter number': trainable_num}

def main():
    #hyper parameters
    device = torch.device("cuda")
    # load PTB dataset
    batch_size = 20
    learning_rate=0.001
    epochs=39
    torch.manual_seed(100)
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
    model=RNNModel(10002,1500,1500,2,20,dropout=0.5).to(device)
    print(get_parameter_number(model))
    loss_function=nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    #Do training
    for epoch in range(1,epochs+1):
        if epoch > 6:
            learning_rate=learning_rate/1.2
            optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
        model.train()
        for batch in tqdm(train_iter):
            model.reset_history()
            text, target = batch.text, batch.target
            optimizer.zero_grad()
            output = model(text)
            loss = loss_function(output.view(-1,10002), target.view(-1))
            loss.backward()
            clip_grad_norm_(model.parameters(), 0.2)
            optimizer.step()
        #Do testing every epoch
        model.eval()
        perplexitis=[]
        correct = 0
        with torch.no_grad():
            for tests in test_iter:
                model.reset_history()
                text, target = tests.text,tests.target
                output = model(text)
                #loss = loss_function(output, target.reshape(-1))  # sum up batch loss
                loss = loss_function(output.view(-1, 10002), target.view(-1))
                perplexity=np.exp(loss.item())
                perplexitis.append(perplexity)
        low=min(perplexitis)
        high=max(perplexitis)

        print('\nEpoch: {}/{}, Lowest perplexity: {:5.2f}, Highest perplexity:{:5.2f}\n'
            .format(epoch, epochs, low, high))
    #calculating parameter number
    para_num = get_parameter_number(model)
    print(para_num)

if __name__=="__main__":
    main()