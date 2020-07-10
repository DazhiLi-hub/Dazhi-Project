# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 22:29:16 2020

@author: DzL
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torchtext
from torchtext import datasets
from torchtext.data import Field
from torch.autograd import Variable

class LSTM_model(nn.Module):
    def __init__(self,vocab_num,input_dim,hidden_dim,num_layers):
        super(LSTM_model,self).__init__()
        self.embed=nn.Embedding(vocab_num,input_dim)
        self.lstm=nn.LSTM(input_dim,hidden_dim,num_layers)
        self.decoder=nn.Linear(hidden_dim,vocab_num)

    def forward(self,x):
        x=self.embed(x)
        #out,(h,c)=self.lstm(x,h)
        out=self.lstm(x)
        out = out.reshape(out.size(0) * out.size(1), out.size(2))
        out=self.decoder(out)
        #return out,(h,c)
        return out

def train(model,device,train_loader,optimizer,epoch,loss_func):
    model.train()
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        data, target = Variable(data), Variable(target)
        optimizer.zero_grad()
        output = model(data)
        loss=loss_func(output,target)
        loss.backward()
        optimizer.step()
        if batch_idx % 10 == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                       100. * batch_idx / len(train_loader), loss.item()))

def test(model,device,test_loader):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item()  # sum up batch loss
            pred = output.argmax(dim=1, keepdim=True)  # get the index of the max log-probability
            correct += pred.eq(target.view_as(pred)).sum().item()
    test_loss /= len(test_loader.dataset)

    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))

def main():
    #hyper parameters
    device = torch.device("cpu")
    # load PTB dataset
    batch_size = 128
    test_batch_size = 42068
    learning_rate=0.1
    epochs=10
    #preparing datasets
    TEXT=Field(sequential=True,eos_token=True,unk_token=True,pad_token=False)
    train,valid,test = datasets.PennTreebank.splits(root='./data',text_field=TEXT, train='ptb.train.txt', validation='ptb.valid.txt', test='ptb.test.txt')
    TEXT.build_vocab(train)
    train_iter,valid_iter,test_iter=datasets.PennTreebank.iters(batch_size=1328,bptt_len=35,device=device,root='./data')
    train_loader = torch.utils.data.DataLoader(train_iter, batch_size=1)
    test_loader = torch.utils.data.DataLoader(test_iter, shuffle=False)
    #apply models, loss functions and optimizer
    model=LSTM_model(10000,1500,1500,2).to(device)
    loss_function=nn.NLLLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    #Do training
    for epoch in range(1,epochs+1):
        train(model,device,train_loader,optimizer,epoch,loss_function)
        test(model,device,test_loader)

if __name__=="__main__":
    main()