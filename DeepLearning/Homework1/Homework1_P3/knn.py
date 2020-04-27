#import math
import numpy as np  
from download_mnist import load
#import operator  
import time
from collections import Counter
# classify using kNN  
#x_train = np.load('../x_train.npy')
#y_train = np.load('../y_train.npy')
#x_test = np.load('../x_test.npy')
#y_test = np.load('../y_test.npy')
x_train, y_train, x_test, y_test = load()
x_train = x_train.reshape(60000,28,28)
x_test  = x_test.reshape(10000,28,28)
x_train = x_train.astype(float)
x_test = x_test.astype(float)
def kNNClassify(newInput, dataSet, labels, k): 
    result=[]
    ########################
    # Input your code here #
    ########################
    for i in newInput:
        L2_dist=0
        L2=[]
        for j in dataSet:
            '''
            This kind of method is low_efficient and low_accurate
            for row in range(28):
                for column in range(28):
                    L2_dist+=np.sqrt((i[row][column]-j[row][column])**2)
            '''
            L2_dist=np.sum(np.sqrt((i-j)**2))
            L2.append(L2_dist)
        Min_list=[]
        for a in range(k):
            Min_list.append(L2.index(min(L2)))
            L2[L2.index(min(L2))]=float("inf")
        classifier=[]
        for b in Min_list:
            classifier.append(labels[b])
        #print(classifier)
        result.append(Counter(classifier).most_common(1)[0][0])  
       
    
    
    ####################
    # End of your code #
    ####################
    return result

start_time = time.time()
outputlabels=kNNClassify(x_test[0:20],x_train,y_train,10)
result = y_test[0:20] - outputlabels
result = (1 - np.count_nonzero(result)/len(outputlabels))
print ("---classification accuracy for knn on mnist: %s ---" %result)
print ("---execution time: %s seconds ---" % (time.time() - start_time))
