# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space import jetSpace

gabor_jet_kernel = jetSpace(101, 11, 2.67*1.3, 1/(0.2*np.pi/2),6,8,1)
pixel_jets = []

for testD in range(1,14) + range(15,111):    
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
    

    best_jet = [10.0 , 0.0]


#    cv2.circle(image, (320,240), 2, (255,255,255))
#    cv2.imshow("from RobWork", image)
#    cv2.waitKey(0)    

    for index_test, comarison_pixel_jet in pixel_jets:

        jet_value = gabor_jet_kernel.compareJetSpace( comarison_pixel_jet.flatten() / np.sum(comarison_pixel_jet.flatten() ) , pixel_jet.flatten() / np.sum(pixel_jet.flatten() )  )

        if jet_value < best_jet[0]:

            best_jet[0] = jet_value
            best_jet[1] = index_test
            
    if image_index == best_jet[1]:
        number_of_correct += 1
        
print number_of_correct