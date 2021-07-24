from __future__ import print_function
import torch
import torch.nn as nn
import torch.optim as optim
import time
import PUF_Data_Loader
import matplotlib.pyplot as plt


class PUF_fast_net(nn.Module):
    def __init__(self,n):
        self.n=n
        super(PUF_fast_net, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(64, pow(2,self.n-1)),
            nn.Tanh(),
            nn.Linear(pow(2,self.n-1), pow(2,self.n)),
            nn.Tanh(),
            nn.Linear(pow(2,self.n), pow(2,self.n-1)),
            nn.Tanh(),
            nn.Linear(pow(2,self.n-1), 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        out = self.fc(x)
        return out
'''
Model = torch.nn.Sequential(
    nn.Linear(64, 16),
    nn.Tanh(),
    nn.Linear(16, 32),
    nn.Tanh(),
    nn.Linear(32, 16),
    nn.Tanh(),
    nn.Linear(16, 1),
    nn.Sigmoid())
'''
class PUF_data_set():
    def __init__(self, y_label, x_data, transform=None, target_transform=None):
        self.labels = y_label
        self.data = x_data
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self):
        return len(self.labels)

    def __getitem__(self, idx):
        sample_data = self.data[idx]
        sample_label = self.labels[idx]
        if self.transform:
            image = self.transform(sample_data)
        if self.target_transform:
            label = self.target_transform(sample_label)
        sample = [sample_data, sample_label]
        return sample

# defining training progress
def train(model, device, train_loader, optimizer, epoch):
    model.train()
    print(train_loader)
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        data = data.view(-1, 64)
        target=target.view(-1,1)
        output = model(data)
        loss_fn = nn.BCELoss()
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
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            data = data.view(-1, 64)
            target=target.view(-1,1)
            output = model(data)
            for i in range(len(output)):
                if output[i]>=0.5:
                    output[i]=1
                else:
                    output[i]=0
            for i in range(len(output)):
                if output[i]==target[i]:
                    correct=correct+1
        print('\nTest set: Accuracy:{}/{} ({:.0f}%)\n'.format(
            correct, len(test_loader.dataset),
            100. * correct / len(test_loader.dataset)))
    return 100. * correct / len(test_loader.dataset)


# main function
def main():
    device = torch.device("cuda")
    training_sample_rate=0.8
    PUF_data=PUF_Data_Loader.PUF_data("./Data/5XOR_64bit_Prof_gen_100K.txt",training_sample_rate)
    PUF_data.get_data()
    batch_size = 1000
    test_batch_size = int(PUF_data.get_len()*(1-training_sample_rate))
    training_set=PUF_data_set(PUF_data.training_set[1],PUF_data.training_set[0])
    testing_set = PUF_data_set(PUF_data.testing_set[1], PUF_data.testing_set[0])
    print("data:",training_set.__getitem__(10))
    print("label:",training_set.__getitem__(10))
    train_loader =torch.utils.data.DataLoader(training_set,batch_size=batch_size)
    test_loader =torch.utils.data.DataLoader(testing_set,batch_size=test_batch_size)
    # set optimizer
    lr = 0.01
    model = PUF_fast_net(5).to(device)
    optimizer = optim.Adam(model.parameters(), lr=lr)
    time0 = time.time()
    # Training settings
    epochs = 40
    # start training
    time0 = time.time()
    accuracies=[]
    for epoch in range(1, epochs + 1):
        train(model, device, train_loader, optimizer, epoch)
        accuracy=test(model, device, test_loader)
        accuracies.append(accuracy)
    time1 = time.time()
    print('Training and Testing total excution time is: %s seconds ' % (time1 - time0))
    x_label=list(range(0,40))
    plt.plot(x_label,accuracies)
    plt.show()


if __name__ == '__main__':
    main()