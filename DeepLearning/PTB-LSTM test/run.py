# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 22:29:16 2020

@author: DzL
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchtext import datasets

def main(model_kind):
    device = torch.device("gpu")
    # load PTB dataset
    batch_size = 128
    test_batch_size = 10000
    train_loader = torch.utils.data.DataLoader(
        datasets.PennTreebank('./data', train=True, download=True,
        batch_size=batch_size, shuffle=True))
    test_loader = torch.utils.data.DataLoader(
        datasets.PennTreebank('./data', train=False,
        batch_size=test_batch_size, shuffle=True))
    # set optimizer
    lr = 0.01
    model = model_kind.to(device)
    optimizer = optim.SGD(model.parameters(), lr=lr)
    #time0 = time.time()
    # Training settings
    epochs = 10
    loss = 'CE'
    

if __name__=="__main__":
    main()