# -*- coding: utf-8 -*-
"""
Created on Thu Dec 11 12:27:31 2014

@author: frederik
"""

import numpy as np

result_file = '../new_part_1.txt'
result_file = '../complete_comparison_results_vertical.txt'

        
import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)

lines = []



histogram_list = []


for correction in [1, 2]:
    f = open(result_file, 'r')
    
    result_to_rot = {'0.0':0, '0.1745':0, 
       '0.3491':0, '0.5236':0, 
        '0.6981':0, '0.8727':0, 
        '1.047':0, '1.222':0}
    
    result_list = []    
    new = False
    
    index = 1
    best_index = 0
    best_result = np.inf
    actual_index = 2
    
    number_of_image = 0
    number_of_true = 0

    
    rotations = []
    

    
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


        elif len(datalist) > 3 and new == True:
    #        print best_index
    #        print actual_index        
            if best_index == actual_index:
    #            print True
                number_of_true += 1
                result_to_rot[ actual_rotation[1] ] = result_to_rot[ actual_rotation[1] ] + 1
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
            number = datalist[ correction ]#[1:-1]
#            print actual_index
            #1.047 and 0.5236 and 1.222
            if actual_index == 99 and actual_rotation[1] == '1.222' and correction == 2:
                histogram_list.append(number)
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

    result = []    
            
    for index in [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222' ]:
        print "rotation " + index + "\t" + str(result_to_rot[index]) + "\t" + str(result_to_rot[index]/110.)
        result.append(result_to_rot[index])        
        
    tmp, = plt.plot([ 0.0, 0.1745, 0.3491, 0.5236, 0.6981, 0.8727, 1.047, 1.222 ], result, label='Line 2')  

    
    lines.append(tmp)

plt.xlabel('Rotation')
plt.ylabel('Recognized')
plt.legend([lines[0], lines[1]], ['No correction', 'Correction'])
plt.grid()
plt.show()                    



x = []
y = []
color = []
for index, result in enumerate(histogram_list):
    if index + 1 == 98:
#        color.append(1)
        pass
    else:
        color.append((1,1,0))
#    from matplotlib import pyplot as plt
        x.append(result)
        y.append(0)  
  


    
plt.scatter(x, y, s=400, c=color)
x = []
y = []
color = []

color.append( (1,0,0) )
x.append(histogram_list[97])
y.append(0)  

plt.scatter(x, y, s=600, c=color)
plt.xlim(0,1)

frame = plt.gca()

frame.axes.get_yaxis().set_ticks([])
plt.xlabel('Squared Distance')
plt.show()
