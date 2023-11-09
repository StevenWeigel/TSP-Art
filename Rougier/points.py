# -*- coding: utf-8 -*-
import numpy as np
import scipy
data = np.load('C:/Projects/Rougier-2017-master/data/leafs-stipple.npy', mmap_mode = 'r')
data = data.astype('float32')
data = np.sort(data)
tree = scipy.spatial.KDTree(data)
print(tree.query(data, k=2))
print("X: ", data[:,0].min(), data[:, 0].max())
print("Y: ", data[:,1].min(), data[:, 1].max())
print("points: ", len(data))
file1 = open("C:/Projects/Rougier-2017-master/data/points.txt", "w")
for row in data:
    np.savetxt(file1, row, '%20.10f')
    
file1.close()