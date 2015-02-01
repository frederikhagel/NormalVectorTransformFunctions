# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space_new import jetSpace

for scaling in [ 0.2]: #0.5, 0.25,
    gabor_jet_kernel = jetSpace(15, 0.9, 2, 0.25 )

    result_to_rot = {'0.0':0, '0.1745':0, 
    '0.3491':0, '0.5236':0, 
    '0.6981':0, '0.8727':0, 
    '1.047':0, '1.222':0}    

    pixel_jets = []

    gabor_jet_kernel.inspect_kernel(50)
    
    for testD in range(1,14) + range(15,112):

        input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(testD) + ".jpeg"
        image = cv2.imread(input_image)
        image = cv2.resize(image, ( 480, 480 ), 0.48, 0.48, 0)
    
        
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
        
        if len(datalist[-1].split('_')) == 3:

            transform = datalist[-1].split('_')[0]
            rotation = datalist[-1].split('_')[1][5: len(datalist[-1].split('_')[1]) - 12 + len(datalist[-1].split('_')[2]) ]
            image_index = datalist[-1].split('_')[2][:-5] 
            if transform == 'transformed':
                all_images.append( [ transform, rotation, image_index, image ] )        
            
    
    print len(all_images)
    
    number_of_correct = 0    
    
    
    import time
    
    timestamp = time.time()
    
    for transform, rotation, image_index, image_to_test in all_images:    

        image = cv2.imread(image_to_test)
        
        response = gabor_jet_kernel.calculateResponse(image)    
        pixel_jet = gabor_jet_kernel.getPixelJet((320,240), response)
        
    
        best_jet = [0.0 , 0.0]
    
        for index_test, comarison_pixel_jet in pixel_jets:
   
    
            jet_value = gabor_jet_kernel.compareJetSpace( comarison_pixel_jet , pixel_jet  )
    
            if jet_value > best_jet[0]:
    
                best_jet[0] = jet_value
                best_jet[1] = index_test
                
        if image_index == best_jet[1]:
            number_of_correct += 1
            result_to_rot[rotation.split(' ')[2]] += 1

    run_time = timestamp - time.time()

    print run_time
    print float(run_time)/len(all_images)

    print "Scaling: ", scaling        
    print "Number of correct:", number_of_correct
    
    
#    import matplotlib.pyplot as plt
#    fig = plt.figure()
#    ax = fig.add_subplot(111)    
#    
#    lines = []
#    result = []    
    for index in [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222' ]:
        print result_to_rot[index]
#        result.append(result_to_rot[index])        
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