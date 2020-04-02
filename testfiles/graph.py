import matplotlib.pyplot as plt 

x = [100000,200000,500000,800000,1000000]
y1 = [68.37452, 170.73516, 636.4596, 1290.79444, 1743.6106000000002]
y2 = [2.01952,4.72612,10.5344,18.86704,21.00956]
y = []
for i in range(len(y1)):
    y.append(y1[i]/y2[i])


plt.scatter(x,y)
plt.show()
