import math
x_1=2
w_1=1
x_2=3
w_2=2
def manual_com():
    f_1=x_1*w_1
    f_2=math.sin(f_1)
    f_3=f_2**2
    f_4=x_2*w_2
    f_5=math.cos(f_4)
    f_6=f_5+f_3
    f_7=f_6+2
    f_8=1/f_7
    d_8=1.00
    d_7=d_8*(-1/f_7**2)
    d_6=d_7*1
    d_5=d_6*1
    d_4=d_5*(-math.sin(f_4))
    d_x_2=d_4*w_2
    d_w_2=d_4*x_2
    d_3=d_5*1
    d_2=d_3*2*f_2
    d_1=d_2*math.cos(f_1)
    d_x_1=d_1*w_1
    d_w_1=d_1*x_1
    print("The result of forward propagation is "+str(f_8))
    print("The gradient of x1 is "+str(d_x_1))
    print("The gradient of w1 is "+str(d_w_1))
    print("The gradient of x2 is "+str(d_x_2))
    print("The gradient of w2 is "+str(d_w_2))

manual_com()