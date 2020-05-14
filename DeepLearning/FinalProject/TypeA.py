'''
This is a program shows how Batch Normalization adn Dropout influence Neural Network
There are 4 kinds of model:
1. No BN + No Dropout
2. BN + no Dropout
3. No BN + Dropout
4. BN + Dropout
Metrics are accuracy, time
'''

from __future__ import print_function
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
import time
from collections import OrderedDict

class LeNet(nn.Module):
    def __init__(self):
        self.name='LeNet'
        super(LeNet, self).__init__()
        self.convnet = nn.Sequential(OrderedDict([
            ('c1', nn.Conv2d(1, 6, kernel_size=(5, 5),padding=2)),
            ('relu1', nn.ReLU()),
            ('s2', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c3', nn.Conv2d(6, 16, kernel_size=(5, 5))),
            ('relu3', nn.ReLU()),
            ('s4', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c5', nn.Conv2d(16, 120, kernel_size=(5, 5))),
            ('relu5', nn.ReLU())
        ]))
        self.fc = nn.Sequential(OrderedDict([
            ('f6', nn.Linear(120, 84)),
            ('relu6', nn.ReLU()),
            ('f7', nn.Linear(84, 10)),
            ('sig7', nn.LogSoftmax(dim=-1))
        ]))
    def forward(self, x):
        x = self.convnet(x)
        x = x.view(x.size()[0], -1)
        out = self.fc(x)
        return out

class LeNet_BN_noDropout(nn.Module):
    def __init__(self):
        self.name='LeNet_BN_noDropout'
        super(LeNet_BN_noDropout, self).__init__()
        self.convnet = nn.Sequential(OrderedDict([
            ('c1', nn.Conv2d(1, 6, kernel_size=(5, 5),padding=2)),
            ('bn1', nn.BatchNorm2d(6)),
            ('relu1', nn.ReLU()),
            ('s2', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c3', nn.Conv2d(6, 16, kernel_size=(5, 5))),
            ('bn3', nn.BatchNorm2d(16)),
            ('relu3', nn.ReLU()),
            ('s4', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c5', nn.Conv2d(16, 120, kernel_size=(5, 5))),
            ('bn5', nn.BatchNorm2d(120)),
            ('relu5', nn.ReLU())
        ]))
        self.fc = nn.Sequential(OrderedDict([
            ('f6', nn.Linear(120, 84)),
            ('relu6', nn.ReLU()),
            ('f7', nn.Linear(84, 10)),
            ('sig7', nn.LogSoftmax(dim=-1))
        ]))
    def forward(self, x):
        x = self.convnet(x)
        x = x.view(x.size()[0], -1)
        out = self.fc(x)
        return out

class LeNet_noBN_Dropout(nn.Module):
    def __init__(self):
        self.name='LeNet_noBN_Dropout'
        super(LeNet_noBN_Dropout, self).__init__()
        self.convnet = nn.Sequential(OrderedDict([
            ('c1', nn.Conv2d(1, 6, kernel_size=(5, 5),padding=2)),
            ('relu1', nn.ReLU()),
            ('s2', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c3', nn.Conv2d(6, 16, kernel_size=(5, 5))),
            ('relu3', nn.ReLU()),
            ('s4', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c5', nn.Conv2d(16, 120, kernel_size=(5, 5))),
            ('relu5', nn.ReLU())
        ]))
        self.fc = nn.Sequential(OrderedDict([
            ('f6', nn.Linear(120, 84)),
            ('drop6', nn.Dropout(0.5)),
            ('relu6', nn.ReLU()),
            ('f7', nn.Linear(84, 10)),
            ('drop7', nn.Dropout(0.5)),
            ('sig7', nn.LogSoftmax(dim=-1))
        ]))
    def forward(self, x):
        x = self.convnet(x)
        x = x.view(x.size()[0], -1)
        out = self.fc(x)
        return out

class LeNet_BN_Dropout(nn.Module):
    def __init__(self):
        self.name='LeNet_BN_Dropout'
        super(LeNet_BN_Dropout, self).__init__()
        self.convnet = nn.Sequential(OrderedDict([
            ('c1', nn.Conv2d(1, 6, kernel_size=(5, 5),padding=2)),
            ('bn1', nn.BatchNorm2d(6)),
            ('relu1', nn.ReLU()),
            ('s2', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c3', nn.Conv2d(6, 16, kernel_size=(5, 5))),
            ('bn3', nn.BatchNorm2d(16)),
            ('relu3', nn.ReLU()),
            ('s4', nn.MaxPool2d(kernel_size=(2, 2), stride=2)),
            ('c5', nn.Conv2d(16, 120, kernel_size=(5, 5))),
            ('bn5', nn.BatchNorm2d(120)),
            ('relu5', nn.ReLU())
        ]))
        self.fc = nn.Sequential(OrderedDict([
            ('f6', nn.Linear(120, 84)),
            ('drop6', nn.Dropout(0.5)),
            ('relu6', nn.ReLU()),
            ('f7', nn.Linear(84, 10)),
            ('drop7', nn.Dropout(0.5)),
            ('sig7', nn.LogSoftmax(dim=-1))
        ]))
    def forward(self, x):
        x = self.convnet(x)
        x = x.view(x.size()[0], -1)
        out = self.fc(x)
        return out

# defining training progress
def train(model, device, train_loader, optimizer, loss, epoch):
    model.train()
    count = 0
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)

        optimizer.zero_grad()
        output = model(data)
        if loss == 'CE':
            # CrossEntropy Loss
            loss_fn = nn.CrossEntropyLoss()
        if loss == 'MSE':
            # MSE Loss
            y_onehot = target.numpy()
            y_onehot = (np.arange(10) == y_onehot[:, None]).astype(np.float32)
            target = torch.from_numpy(y_onehot)
            loss_fn = nn.MSELoss()
        loss_ = loss_fn(output, target)
        loss_.backward()
        optimizer.step()
        if batch_idx % 10 == 0:
            print('Train Epoch:{}[{}/{}({:.0f}%)]\tLoss:{:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                       100. * batch_idx / len(train_loader), loss_.item()))


# defining testing
def test(model, device, test_loader):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item()
            # sum up batch loss,negative log likelihood loss

            pred = output.argmax(dim=1, keepdim=True)
            # get the index of the max log-probability
            correct += pred.eq(target.view_as(pred)).sum().item()
        test_loss /= len(test_loader.dataset)
        accuracy=100. * correct / len(test_loader.dataset)
        print('\nTest set: Average loss:{:.4f},Accuracy:{}/{} ({:.0f}%)\n'.format(
            test_loss, correct, len(test_loader.dataset),
            accuracy))
        return accuracy



# main function
def main(model_kind):
    device = torch.device("cpu")
    # load MNIST dataset
    batch_size = 128
    test_batch_size = 10000
    train_loader = torch.utils.data.DataLoader(
        datasets.MNIST('./data', train=True, download=True,
                       transform=transforms.Compose([
                           transforms.ToTensor(),
                           transforms.Normalize((0.1307,), (0.3081,))
                       ])),
        batch_size=batch_size, shuffle=True)
    test_loader = torch.utils.data.DataLoader(
        datasets.MNIST('./data', train=False, transform=transforms.Compose([
            transforms.ToTensor(),
            transforms.Normalize((0.1307,), (0.3081,))
        ])),
        batch_size=test_batch_size, shuffle=True)
    # set optimizer
    lr = 0.01
    model = model_kind.to(device)
    optimizer = optim.SGD(model.parameters(), lr=lr)
    #time0 = time.time()
    # Training settings
    epochs = 10
    loss = 'CE'
    # start training
    epoch_time=[]
    epoch_accuracy=[]
    time0 = time.time()
    for epoch in range(1, epochs + 1):
        time3=time.time()
        train(model, device, train_loader, optimizer, loss, epoch)
        total_accuracy=test(model, device, test_loader)
        time4=time.time()
        epoch_time.append(time4-time3)
        epoch_accuracy.append(total_accuracy)
    time1 = time.time()
    total_time=time1-time0
    print('Training and Testing total excution time is: %s seconds ' % total_time)
    return total_time,total_accuracy,epoch_time,epoch_accuracy


if __name__ == '__main__':
    time_list=[]
    accuracy_list=[]
    detail={}
    model_list=[LeNet(),LeNet_BN_noDropout(),LeNet_noBN_Dropout(),LeNet_BN_Dropout()]
    for model in model_list:
        temp_time,temp_accuracy,detail[model.name+'_time'],detail[model.name+'_accuracy']=main(model)
        time_list.append(temp_time)
        accuracy_list.append(temp_accuracy)
    print(time_list,accuracy_list)
    print(detail)
