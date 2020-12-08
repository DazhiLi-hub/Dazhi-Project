# -*- coding:utf-8 -*-
# 
# Author: MIAO YIN
# Time: 2020/9/28 20:35

import torch
import numpy as np
import math

from torch.nn import Parameter, ParameterList, ModuleList
from torch.nn import init
from torch.nn import Hardsigmoid


class TTLSTMFullCell(torch.nn.Module):
    __constants__ = ['concat_tt_shape', 'output_tt_shape', 'tt_ranks']

    def __init__(self, concat_tt_shape, output_tt_shape, tt_ranks, use_bias=True):
        super(TTLSTMFullCell, self).__init__()
        self.concat_tt_shape = concat_tt_shape
        self.output_tt_shape = output_tt_shape
        self.tt_ranks = tt_ranks
        self.use_bias = use_bias

        self.hidden_size = int(np.prod(output_tt_shape))
        self.input_size = int(np.prod(concat_tt_shape)) - self.hidden_size
        self.n_dim = len(concat_tt_shape)

        self.output_tt_shape[0] *= 4

        self.cores = ParameterList(
            [Parameter(torch.Tensor(self.tt_ranks[i]*self.output_tt_shape[i],
                                    self.concat_tt_shape[i]*self.tt_ranks[i+1]))
             for i in range(self.n_dim)])
        self.output_tt_shape[0] = self.output_tt_shape[0] // 4

        if self.use_bias:
            self.bias = Parameter(torch.zeros(self.hidden_size*4))
        else:
            self.register_parameter('bias', None)

        self.reset_parameters()

    def reset_parameters(self):
        for i in range(self.n_dim):
            init.xavier_uniform_(self.cores[i])

    def forward(self, x):
        hiddens = []
        h = torch.Tensor(torch.zeros(x.shape[1], self.hidden_size))
        c = torch.Tensor(torch.zeros(x.shape[1], self.hidden_size))
        n_seq = x.shape[0]
        if x.is_cuda:
            h = h.cuda()
            c = c.cuda()
        for step in range(n_seq):
            h, c = self.step(x[step], h, c)
            hiddens.append(h)
        if x.is_cuda:
            res = torch.stack(hiddens).cuda()
        else:
            res = torch.stack(hiddens)
        return res  

    def step(self, x, h_tm1, c_tm1):
        res = torch.cat([x, h_tm1], dim=1)

        for k in range(self.n_dim - 1, -1, -1):
            res = torch.reshape(res, [-1, self.concat_tt_shape[k]])
            res = torch.transpose(res, 0, 1)
            res = torch.reshape(res, [self.tt_ranks[k+1]*self.concat_tt_shape[k], -1])
            res = torch.matmul(self.cores[k], res)

        res = torch.reshape(res, [-1, x.shape[0]])
        res = torch.transpose(res, 0, 1)

        if self.use_bias:
            res = torch.add(res, self.bias)

        z0 = res[:, :self.hidden_size]
        z1 = res[:, self.hidden_size:2*self.hidden_size]
        z2 = res[:, 2*self.hidden_size:3*self.hidden_size]
        z3 = res[:, 3*self.hidden_size:]

        i = Hardsigmoid()(z0)
        f = Hardsigmoid()(z1)
        c = f * c_tm1 + i * torch.tanh(z2)
        o = Hardsigmoid()(z3)

        h = o * torch.tanh(c)

        return h, c

    def extra_repr(self):
        return 'concat_tt_shape={}, output_tt_shape={}, tt_ranks={}, bias={}'.format(
            self.concat_tt_shape, self.output_tt_shape, self.tt_ranks, self.bias is not None
        )

