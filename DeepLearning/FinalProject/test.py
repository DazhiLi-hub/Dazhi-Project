import numpy as np
import matplotlib.pyplot as plt
#创建自变量数组
x_label= ["Classic","BN_nodrop","noBN_drop","BN_drop"]
#创建函数值数组
time_list =[261,241,269,245]
Accuracy_list=[97,95.5,98.8,99.9]
epoch=[1,2,3,4,5,6,7,8,9,10]
acc_epoch=[78.6,80.6,85.6,86,87,88,89,91,92,95]
#创建图形
plt.figure(1)
'''
意思是在一个2行2列共4个子图的图中，定位第1个图来进行操作（画图）。
最后面那个1表示第1个子图。那个数字的变化来定位不同的子图
'''
#第一行第一列图形
ax1 = plt.subplot(2,2,1)
#第一行第二列图形
ax2 = plt.subplot(2,2,2)
#第二行
ax3 = plt.subplot(2,1,2)
#选择ax1
plt.sca(ax1)
#绘制红色曲线
plt.bar(range(len(time_list)),time_list,color='red',tick_label=x_label)
#限制y坐标轴范围
#plt.ylim(-1.2,1.2)
#选择ax2
plt.sca(ax2)
#绘制蓝色曲线
plt.bar(range(len(Accuracy_list)),Accuracy_list,color='blue',tick_label=x_label)
#plt.ylim(-1.2,1.2)
#选择ax3
plt.sca(ax3)
plt.plot(epoch,acc_epoch,'g--')
#plt.ylim(-1.2,1.2)
plt.show()