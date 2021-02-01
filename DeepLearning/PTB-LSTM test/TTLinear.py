# -*- coding:utf-8 -*-
# 
# Author: YIN MIAO
# Time: 2020/8/4 23:32

import math
import torch
import numpy as np
from torch.nn import Module
from torch.nn import init
from torch.nn import functional as F
from torch.nn import Parameter
from torch.nn import ParameterList

#from tt_svd import mat2tt


class TTLinear(Module):
    __constants__ = ['input_tt_shape', 'output_tt_shape', 'tt_ranks']

    def __init__(self, input_tt_shape, output_tt_shape, tt_ranks,
                 bias=True, from_dense=False, dense_w=None, dense_b=None):
        super(TTLinear, self).__init__()
        self.input_tt_shape = input_tt_shape
        self.output_tt_shape = output_tt_shape
        self.n_dim = len(input_tt_shape)
        self.output_size = int(np.prod(self.output_tt_shape))
        if from_dense:
            #tt_cores, self.tt_ranks = mat2tt(dense_w.cpu().detach().numpy(), output_tt_shape, input_tt_shape, tt_ranks)
            #self.cores = ParameterList([Parameter(torch.from_numpy(core).detach()) for core in tt_cores])
            if bias:
                self.bias = Parameter(dense_b.clone().detach())
            else:
                self.register_parameter('bias', None)
        else:
            self.tt_ranks = tt_ranks
            self.cores = ParameterList([Parameter(
                torch.Tensor(self.tt_ranks[i] * self.output_tt_shape[i],
                             self.input_tt_shape[i] * self.tt_ranks[i + 1]))
                for i in range(self.n_dim)])
            if bias:
                self.bias = Parameter(torch.zeros(self.output_size))
            else:
                self.register_parameter('bias', None)
            self.reset_parameters()

    def get_tt_ranks(self):
        str_tt_ranks = [str(r) for r in self.tt_ranks]
        return ', '.join(str_tt_ranks)

    def reset_parameters(self):
        for i in range(self.n_dim):
            init.xavier_uniform_(self.cores[i])
            # init.kaiming_uniform_(self.cores[i], a=math.sqrt(5))
        # if self.bias is not None:
        #     fan_in, _ = init._calculate_fan_in_and_fan_out(self.weight)
        #     bound = 1 / math.sqrt(fan_in)
        #     init.uniform_(self.bias, -bound, bound)

    def forward(self, x):
        res = x
        for k in range(self.n_dim - 1, -1, -1):
            res = torch.reshape(res, [-1, self.input_tt_shape[k]])
            res = torch.transpose(res, 0, 1)
            res = torch.reshape(res, [self.tt_ranks[k + 1] * self.input_tt_shape[k], -1])
            res = torch.matmul(self.cores[k], res)
        res = torch.reshape(res, [self.output_size, -1])
        res = torch.transpose(res, 0, 1)
        res = torch.add(res, self.bias)

        return res

        # return F.linear(input, self.weight, self.bias)

    def extra_repr(self):
        return 'input_tt_shape={}, output_tt_shape={}, tt_ranks={}, bias={}'.format(
            self.input_tt_shape, self.output_tt_shape, self.tt_ranks, self.bias is not None
        )
