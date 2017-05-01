# -*- coding: utf-8 -*-

#We need to divide vector of size N into M<N equal parts. Extra elements can be located at the beginning and at the end of segmented area,
#and the size of these tails should be minimal
#The result should be indices of beginning and the end of each part 


import numpy as np


data = np.zeros(31) #our vector to split

M = 7 # number of parts to split

extra = data.shape[0] % M #number of extra elements
lesser_tail = extra % 2 #size of lesser left tail
step = data.shape[0] / M #length of one chunk

beginnings =  np.arange(lesser_tail,data.shape[0]-extra+lesser_tail,step)
ends = np.arange(lesser_tail+step-1,data.shape[0],step)

print "Step size: ", step 
print beginnings
print ends