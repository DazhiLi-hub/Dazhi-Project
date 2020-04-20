import numpy as np

def sigmoid(x):
    results=1/(1+np.exp(-x))
    return results

def labels(x):
    list=[]
    for i in x:
        if i >= 0.5:
            list.append(1)
        else:
            list.append(0)
    return np.array(list)

def MSE_loss(y_train,results):
    return ((np.array(y_train).reshape(4,1)-results)**2).sum()/4
    #return ((y_train-results)**2).sum()/4

def training(x_train,y_train,weights_1,weights_2,lr,error):
    bias_1=2
    bias_2=3
    a=1
    while(a>error):
        outputs=[]
        for i in range(len(x_train)):
            print('training data is:')
            print(x_train[i])
            f1=np.dot(weights_1,x_train[i])+bias_1
            f2=sigmoid(f1)
            f3=np.dot(weights_2,f2)+bias_2
            output=sigmoid(f3)
            outputs.append([float(output)])
            loss=(y_train[i]-output)**2
            b1 = -2*(y_train[i] - output)
            b2 = b1 * (1 - output) * output
            weights_2_gradient=np.dot(b2,f2.T)
            b3=np.dot(weights_2.T,b2)
            b4=b3*(1-b3)*b3
            weights_1_gradient=np.dot(b4,x_train[i].T)
            weights_2= weights_2-lr*weights_2_gradient
            weights_1= weights_1-lr*weights_1_gradient
            print(output)
        results=np.array(outputs)
        a=MSE_loss(y_train,results)

#def testing():

def main():
    init_weights_1 = -1 + 2 * np.random.random(4).reshape(2, 2)
    init_weights_2 = -1 + 2*np.random.random(2).reshape(1,2)
    #learning rate lr
    lr=0.01
    e=0.1
    x_train = [np.array([0,0]).reshape(2,1),np.array([0,1]).reshape(2,1),np.array([1,0]).reshape(2,1),np.array([1,1]).reshape(2,1)]
    y_train=[0,1,1,0]
    print("The first init weights are:\n" + str(init_weights_1)+'\n'+\
          "The second init weights are:\n"+str(init_weights_2))
    training(x_train,y_train,init_weights_1,init_weights_2,lr,e)

if __name__=="__main__":
    main()