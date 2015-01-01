# -*- coding: utf-8 -*-
"""
Created on Thu Dec 11 12:27:31 2014

@author: frederik
"""

import numpy as np

result_file = 'new.txt'


f = open(result_file, 'r')

new = False

index = 1
best_index = 0
best_result = np.inf
actual_index = 2

number_of_image = 0
number_of_true = 0

for line in f:
    datalist = line.split(' ')
#    print datalist

    if len(datalist) == 1 and new == False:
        new = True
        print datalist[0]
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        actual_index = int(tmp[-1])
        number_of_image += 1
    elif len(datalist) == 1 and new == True:
#        print best_index
#        print actual_index        
        if best_index == actual_index:
#            print True
            number_of_true += 1
#            print best_result
        new =True
#        print datalist[0]
        number_of_image += 1
        index = 1
        best_index = 0
        best_result = np.inf
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        actual_index = int(tmp[-1])
#        print datalist
    else:
#        print datalist[0]
        number = datalist[1]#[1:-1]
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

print "number_of_true", number_of_true


f = open(result_file, 'r')

new = False

index = 1
best_index = 0
best_result = np.inf
actual_index = 2

number_of_true = 0

for line in f:
    datalist = line.split(' ')



    if len(datalist) == 1 and new == False:
        new = True
#        print datalist[0][-9:-7]
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        actual_index = int(tmp[-1])
#        print datalist
    elif len(datalist) == 1 and new == True:
#        print datalist
#        print best_index
#        print actual_index        
        if best_index == actual_index:
#            print True
            number_of_true += 1
#        print "datalist", datalist[0]
#        print "best_result", best_result
        new =True
        index = 1
        best_index = 0
        best_result = np.inf
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        actual_index = int(tmp[-1])
#        print datalist
        
    else:
#        print best_result
#        print datalist[0]
#        number = datalist[1]#[1:-1]
        tmp = datalist[0].split('.')
#        print tmp[0]
        tmp = tmp[0].split('D')
#        print tmp[-1]
        index = int(tmp[-1])
    
#        if index == actual_index:
#            print "number", number
        number = datalist[2][:-2]
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

print "number_of_true", number_of_true

print "number_of_image", number_of_image