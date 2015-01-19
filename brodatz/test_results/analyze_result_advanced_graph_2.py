# -*- coding: utf-8 -*-
"""
Created on Thu Dec 11 12:27:31 2014

@author: frederik
"""

import numpy as np

result_file = '../new_part_1.txt'

x = []
        
import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)

distances = []

best_result = 0
actual_position = 0

rotation_list = [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222' ]

used_rotation = rotation_list[3]
used_correction = 1


for correction in [1, 2]:
    f = open(result_file, 'r')
    
    result_to_rot = {'0.0':0, '0.1745':0, 
       '0.3491':0, '0.5236':0, 
        '0.8727':0, '1.047':0, 
        '1.222':0}
    
    result_list = []    
    new = False
        
    for line in f:
        datalist = line.split(' ')
    #    print datalist
    
        if len(datalist) > 3 and new == False:
            new = True
#            print datalist[0]

            tmp = datalist[0].split('.')
            tmp = tmp[0].split('D')
            actual_index = int(tmp[-1])

            actual_rotation = datalist[1:]


        elif len(datalist) > 3 and new == True:
            
            if actual_rotation[1] == used_rotation and correction == used_correction:
                x.append( best_result - actual_position)
                print actual_position - best_result   
                print "actual_number", actual_position
                print best_result
                print actual_index

            new =True

           
            best_index = 0
            best_result = np.inf
            actual_number = 0
            actual_index = 0

            tmp = datalist[0].split('.')
            tmp = tmp[0].split('D')
            actual_index = int(tmp[-1])
                        
            actual_rotation = datalist[1:]


        else:
    #        print datalist[0]
            number = datalist[ correction ]#[1:-1]
#            print actual_index
            #1.047 and 0.5236

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
                
            if actual_index == index and actual_rotation[1] == used_rotation and correction == used_correction:
                actual_position = number    
            elif number < best_result:
                best_index = index
                best_result = number
            #print datalist[1]
    #        index = index + 1
            #for data in datalist:
            #print data

    if actual_rotation[1] == used_rotation and correction == used_correction:
        x.append( best_result - actual_number )
        print actual_number - best_result   
        print actual_index
            
            
print
print 'hist_' +  used_rotation + ' correction_' + str(used_correction)
print len(x)
print np.mean(x)
print np.var(x)

#data=x
#binwidth = 0.1
# 
#
#print data
#bins=np.arange(-1. ,1., binwidth)
#print "bint", bins
#
##print plt.hist(data, bins=np.arange(-1.,1., binwidth))
#hist, bins, _ = plt.hist(data, bins=20, range=[-1,1])
##plt.show()
#print bins
#width = 0.5 * (bins[1] - bins[0])
#center = (bins[:-1] + bins[1:]) / 2
#print center
#print hist
##plt.bar(center, hist, align='center', width=width)
#
#plt.xlabel('Distance from best wrong guess')
#plt.ylabel('Number of each distance')
#plt.grid()
#plt.xlim(-1.,1.)
#plt.show()
#
##used_rotation = rotation_list[6]
##used_correction = 1
#
#plt.savefig( '../../../Dropbox/1-Kandidat/VIS3/repport/' + 'hist_' +  used_rotation.replace(".","") + 'correction_' + str(used_correction) + '.png')