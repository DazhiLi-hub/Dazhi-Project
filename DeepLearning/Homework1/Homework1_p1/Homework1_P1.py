import numpy as np
import heapq
from collections import Counter
#Input the training_data
class_A=[(0,1,0),(0,1,1),(1,2,1),(1,2,0)]
class_B=[(1,2,2),(2,2,2),(1,2,-1),(2,2,3)]
class_C=[(-1,-1,-1),(0,-1,-2),(0,-1,1),(-1,-2,1)]
sample=(1,0,1)
L2=[]
#Calculate the distance and remember the training_data
for i in class_A:
    L2_dist=np.sqrt((i[0]-sample[0])**2+(i[1]-sample[1])**2+(i[2]-sample[2])**2)
    new={'class':'class_A','L2_dist':L2_dist}
    L2.append(new)
for i in class_B:
    L2_dist=np.sqrt((i[0]-sample[0])**2+(i[1]-sample[1])**2+(i[2]-sample[2])**2)
    new={'class':'class_B','L2_dist':L2_dist}
    L2.append(new)
for i in class_C:
    L2_dist=np.sqrt((i[0]-sample[0])**2+(i[1]-sample[1])**2+(i[2]-sample[2])**2)
    new={'class':'class_C','L2_dist':L2_dist}
    L2.append(new)
#print(L2)
#Define the KNN classifier to get the output label
def KNN_classifier(k):
    if k==1:
        print("\nWhen K=1,")
        shortest=heapq.nsmallest(k+1, L2, key=lambda s: s['L2_dist'])
        if shortest[0]['L2_dist']==shortest[1]['L2_dist']:
            print("Sample point "+str(sample)+" can be classified to :"+\
                  shortest[0]['class']+"/"+shortest[1]['class'])
        else:
            print("Sample point "+str(sample)+" can be classified to: "+\
                  shortest[0]['class'])
    elif k==3:
        print("\nWhen K=3,")
        shortest=heapq.nsmallest(k, L2, key=lambda s: s['L2_dist'])
        A=[]
        A.append(shortest[0]['class'])
        A.append(shortest[1]['class'])
        A.append(shortest[2]['class'])
        B=Counter(A).most_common(1)
        if B[0][1]==1:
            print("Sample point "+str(sample)+" can not be classified")
        else:
            print("Sample point "+str(sample)+" can be classified to :"+\
                  B[0][0])
    elif k==5:
        print("\nWhen K=5,")
        shortest=heapq.nsmallest(k, L2, key=lambda s: s['L2_dist'])
        A=[]
        A.append(shortest[0]['class'])
        A.append(shortest[1]['class'])
        A.append(shortest[2]['class'])
        A.append(shortest[3]['class'])
        A.append(shortest[4]['class'])
        B=Counter(A).most_common(1)
        if B[0][1]==1:
            print("Sample point "+str(sample)+" can not be classified")
        else:
            print("Sample point "+str(sample)+" can be classified to :"+\
                  B[0][0])
KNN_classifier(1)
KNN_classifier(3)
KNN_classifier(5)