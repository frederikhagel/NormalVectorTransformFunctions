# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space_octave import jetSpace
#from jet_space import jetSpace
#for rotations in [6,8,10,12]:
#    for scales in []    :
#        for frequency in 1/(0.2*np.pi/2):
#    

#for scaling in [ 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3]:
#for scaling in [0.6, 0.5, 0.4, 0.3, 0.2]:
#for scaling in [x / 100.0 for x in range(95, 105, 1)]:

#for scaling in range(1,2):
#for scaling in [1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3]:

#for scaling in [0.6, 0.5, 0.4, 0.3, 0.2]:

import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)

lines = []



histogram_list = []
result_file = '../../brodatz/complete_comparison_results_vertical.txt'

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

            print actual_rotation[2][:-2]

        elif len(datalist) > 3 and new == True:
    #        print best_index
    #        print actual_index        
            if best_index == actual_index:
    #            print True
                number_of_true += 1
                result_to_rot[ actual_rotation[2][:-2] ] = result_to_rot[ actual_rotation[2][:-2] ] + 1
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

    print len(lines)

#    print len(tmp)


for scaling in [1]:
    gabor_jet_kernel = jetSpace(101, 21, np.pi*1.6, np.pi*1.5,(1, 6, 1), 8, 1 )
    
    result_to_rot = {'0.0':0, '0.1745':0, 
    '0.3491':0, '0.5236':0, 
    '0.6981':0, '0.8727':0, 
    '1.047':0, '1.222':0}    
    
    #gabor_jet_kernel = jetSpace(101, 11, np.pi, np., pi,6,12,1)
    pixel_jets = []
          
#    gabor_jet_kernel.inspect_kernel(0)
    
        
    for testD in range(1,14) + range(15,112):    
    #for testD in range(1,2):    
        input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(testD) + ".jpeg"
        image = cv2.imread(input_image)
        image = cv2.resize(image, ( 480, 480 ), 0.48, 0.48, 0)
    
    #    cv2.imshow("image to test", image)
    #    cv2.waitKey(0)
        
        response = gabor_jet_kernel.calculateResponse(image)
        pixel_jet_image_1 = gabor_jet_kernel.getPixelJet((240,240),response)
    
        pixel_jets.append( ['D' + str(testD), pixel_jet_image_1])    
        
    
    import glob
    
    rotated_images = glob.glob('/home/frederik/pcl/images/all_images/*.jpeg')
    rotated_images = glob.glob('/home/frederik/pcl/images/vertical_images/*.jpeg')
    print len(rotated_images)
    
    all_images = []
    
    for image in rotated_images:
        datalist = image.split('/')
    #    print datalist[-1]
    #    print datalist[-1].split('_')
        
        if len(datalist[-1].split('_')) == 3:
    #        print datalist[-1].split('_')[1][5:]
            
    #        print 'transformed', datalist[-1].split('_')[0]
            transform = datalist[-1].split('_')[0]
    #        print "Rotation", datalist[-1].split('_')[1][5: len(datalist[-1].split('_')[1]) - 12 + len(datalist[-1].split('_')[2]) ]
            rotation = datalist[-1].split('_')[1][5: len(datalist[-1].split('_')[1]) - 12 + len(datalist[-1].split('_')[2]) ]
    #        print "Image index", datalist[-1].split('_')[2][:-5]
            image_index = datalist[-1].split('_')[2][:-5] 
            if transform == 'transformed': # and rotation ==  "0.0 0.0 0.0":
                all_images.append( [ transform, rotation, image_index, image ] )        
            
    
    print len(all_images)
    
    number_of_correct = 0    
    
    
    
    
    for transform, rotation, image_index, image_to_test in all_images:    

        image = cv2.imread(image_to_test)
        
        response = gabor_jet_kernel.calculateResponse(image)    
        pixel_jet = gabor_jet_kernel.getPixelJet((320,240), response)
        
    
        best_jet = [0.0 , 0.0]
    
    
    #    cv2.circle(image, (320,240), 2, (255,255,255))
    #    cv2.imshow("from RobWork", image)
    #    cv2.waitKey(0)    
    
        for index_test, comarison_pixel_jet in pixel_jets:
   
    
            jet_value = gabor_jet_kernel.compareJetSpace( comarison_pixel_jet, pixel_jet  )
    
            if jet_value > best_jet[0]:
    
                best_jet[0] = jet_value
                best_jet[1] = index_test
                
        if image_index == best_jet[1]:
            number_of_correct += 1
            result_to_rot[rotation.split(' ')[2]] += 1



    print "Scaling: ", scaling        
    print "Number of correct:", number_of_correct
    
#    import matplotlib.pyplot as plt
#    fig = plt.figure()
#    ax = fig.add_subplot(111)    
#    
#    lines = []
    result = []    
    for index in [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222' ]:
        print result_to_rot[index]
        
        result.append(result_to_rot[index])        


tmp, = plt.plot([ 0.0, 0.1745, 0.3491, 0.5236, 0.6981, 0.8727, 1.047, 1.222 ], result, label='Line 3')  

lines.append(tmp)

print len(lines)

#print len(tmp)

plt.xlabel('Rotation')
plt.ylabel('Recognized')
plt.legend([lines[0], lines[1], lines[2]], ['No correction', 'Correction', 'Gabor Corrected'])
plt.grid()
plt.show()            

#        
#    tmp, = plt.plot([ 0.0, 0.1745, 0.3491, 0.5236, 0.6981, 0.8727, 1.047, 1.222 ], result, label='Line 2')  
#
#    
#    lines.append(tmp)
#
#    plt.xlabel('Rotation')
#    plt.ylabel('Recognized')
#    plt.legend([lines[0]], ["Gabor Correction"])
#    plt.grid()
#    plt.show()                    