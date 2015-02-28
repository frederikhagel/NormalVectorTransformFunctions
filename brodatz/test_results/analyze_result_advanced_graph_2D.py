# -*- coding: utf-8 -*-
"""
Created on Thu Dec 11 12:27:31 2014

@author: frederik
"""

import numpy as np

result_file = 'gabor_results_2D.txt'

        
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#fig = plt.figure()
#ax = fig.add_subplot(111, projection='3d')




lines = []



histogram_list = []



f = open(result_file, 'r')

userdict = {}


result_list = []    
new = False

index = 1
best_index = 0
best_result = np.inf
actual_index = 2

number_of_image = 0
number_of_true = 0


rotations = []

X = []
Y = []
Z = []




for line in f:
    datalist = line.split(' ')
#    print datalist

    if len(datalist) > 3 and new == False:
        new = True
#            print datalist[0]

        number_of_image += 1

        tmp = datalist[0].split('.')
        tmp = tmp[0].split('D')
        actual_index = int(tmp[-1])

        actual_rotation = datalist[1:]
        if datalist[1:] not in rotations:
            rotations.append(datalist[1:])

        print actual_rotation[2][:-2]

    elif len(datalist) > 3 and new == True:
#        print best_index
#        print actual_index        
        if not (actual_rotation[1], actual_rotation[2][:-2]) in userdict:
                userdict[(actual_rotation[1], actual_rotation[2][:-2])] = 0        
        if best_index == actual_index:
#            print True
            number_of_true += 1
            
            print actual_rotation[1]
            print actual_rotation[2][:-2]
#            result_original_rot[ actual_rotation[1] ][ actual_rotation[2][:-2] ] = result_original_rot[ actual_rotation[1] ][ actual_rotation[2][:-2] ] + 1


            
            userdict[(actual_rotation[1], actual_rotation[2][:-2])] += 1
            
#            print best_result
        new =True
#        print datalist[0]
        number_of_image += 1
        index = 1
        best_index = 0
        best_result = np.inf

        tmp = datalist[0].split('.')
        tmp = tmp[0].split('D')
        actual_index = int(tmp[-1])
        
#            if actual_rotation != datalist[1:]:
#                print "not the same"
        
        actual_rotation = datalist[1:]
        if datalist[1:] not in rotations:
            rotations.append(datalist[1:])


    else:
#        print datalist[0]
        number = datalist[ 1 ]#[1:-1]
#            print actual_index

#        print number
#        number = datalist[2][:-2]
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        index = int(tmp[-1])
#        print number
        if number[-4:-2] == "e+":
            number = float(number[:-4]) * (10 ** float(number[-1]))
        else:
            number = float(number)
#        print number
        if number < best_result:
            best_index = index
            best_result = number
        #print datalist[1]
#        index = index + 1
        #for data in datalist:
        #print data

print 
print "number_of_true", number_of_true

print "number_of_image", number_of_image
    
print "expected correct for each rotation", number_of_image / ( 9 * 9)
    
list_of_results = []

for large_index in ['0.0', '0.174532925199', 
   '0.349065850399', '0.523598775598', 
    '0.698131700798', '0.872664625997', 
    '1.0471975512', '1.2217304764', '1.3962634016' ]:

    result = []    

    for index in ['0.0', '0.174532925199', 
       '0.349065850399', '0.523598775598', 
        '0.698131700798', '0.872664625997', 
        '1.0471975512', '1.2217304764', '1.3962634016' ]:
#        print "rotation " + index + "\t" + str(result_original_rot[large_index][index]) + "\t" + str(result_original_rot[large_index][index]/110.)
        result.append(userdict[(large_index,index)] / (number_of_image / ( 9.0 * 9)) ) # Correction for possible number of corrects  
        
        
    list_of_results.append(result)        
        
    tmp, = plt.plot([ 0.0, 0.174532925199, 
       0.349065850399, 0.523598775598, 
        0.698131700798, 0.872664625997, 
        1.0471975512, 1.2217304764,1.3962634016], result, label='Line 2')  
    
    
    lines.append(tmp)
    
#    plt.xlabel('Rotation')
#    plt.ylabel('Recognized')
#    plt.legend([lines[0]], [ large_index ])
#    plt.grid()
#    plt.show()                    
    
Z = np.array( list_of_results )    
    
axis = [ 0.0, 0.174532925199, 
       0.349065850399, 0.523598775598, 
        0.698131700798, 0.872664625997, 
        1.0471975512, 1.2217304764,1.3962634016]   
    
X, Y = np.meshgrid(axis, axis)    
    
from matplotlib import cm     
    
fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot_surface(X, Y, Z, cmap=cm.jet, rstride=1, cstride=1)
plt.show()