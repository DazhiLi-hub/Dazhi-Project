import numpy as np

def sigmoid(x):
    results=1/(1+np.exp(-x))
    return results

#def Cross_Entropy_loss(y_train,results):


def training(x_train,y_train,weights):
    matrix=np.dot(x_train,weights)
    results=sigmoid(matrix)
    print(results)

#def testing():


def main():
    init_weights = -1 + 2 * np.random.random(4).reshape(2, 2)
    x_train = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
    y_train=[0,1,1,0]
    print("The init weights are:\n" + str(init_weights))
    training(x_train,y_train,init_weights)

if __name__=="__main__":
    main()