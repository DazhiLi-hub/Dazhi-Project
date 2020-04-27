import numpy.matlib
import numpy as np
import math
W=np.matlib
W=[[0.1,0.4,0.2],[0.2,0.5,0.7],[0.2,0.6,0.3]]
X=np.array([[0.5],[1.5],[1.1]])

def sigmoid(array):
    temp=[]
    for i in array:
        k=1/(1+math.exp(-i))
        temp.append([k])
    a=np.array(temp).reshape(3,1)
    return  a

def L2(array):
    sum=0
    for i in array:
        sum+=i**2
    return sum

def forward_pass():
    global f_1
    f_1 = numpy.dot(W, X)
    global f_2
    f_2 = sigmoid(f_1)
    global f_3
    f_3 = L2(f_2)
    print("W * X result:\n",f_1)
    print("\nSigmoid result:\n",f_2)
    print("\nL2 distance result:\n",f_3)

def W_derivate_cal():
    temp=[]
    for i in np.nditer(d_1):
        for j in np.nditer(X):
            Mij=i*j
            temp.append(Mij)
    a=np.array(temp).reshape(3,3)
    return a

def X_derivate_cal():
    temp=[]
    for i in range(3):
        xi=0
        for j in range(3):
            xi+=d_1[j][0]*W[j][i]
        temp.append(xi)
    a=np.array(temp).reshape(3,1)
    return a

def back_propagation():
    global d_3
    d_3=1
    global d_2
    d_2=d_3 * 2 * f_2
    global d_1
    d_1=d_2*(1-sigmoid(f_1))*sigmoid(f_1)
    d_w=W_derivate_cal()
    d_x=X_derivate_cal()
    print("\nThe derivate of L2 is:\n",d_2)
    print("\nThe derivate of Sigmoid is:\n",d_1)
    print("\nThe derivate respects to w is:\n",d_w)
    print("\nThe derivate respects to x is:\n",d_x)

forward_pass()
back_propagation()