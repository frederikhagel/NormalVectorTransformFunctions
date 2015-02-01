# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space import jetSpace

gabor_jet_kernel = jetSpace(101, 11, 2.67*1.3, 1/(0.2*np.pi/2),5,8,1)

pixel_jets = []

for testD in range(1,14) + range(15,111):
    
    input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(testD) + ".jpeg"
    image = cv2.imread(input_image)
    response = gabor_jet_kernel.calculateResponse(image)
    pixel_jet_image_1 = gabor_jet_kernel.getPixelJet((510,510),response)
    
    pixel_jets.append( [testD, pixel_jet_image_1])    
    
number_of_correct = 0    


for index_correct, pixel_jet in pixel_jets:
    
    best_jet = [10.0 , 0.0]

    for index_test, comarison_pixel_jet in pixel_jets:

        jet_value = gabor_jet_kernel.compareJetSpace( pixel_jet.flatten() / np.sum(comarison_pixel_jet.flatten() ) , pixel_jet.flatten() / np.sum(pixel_jet.flatten() )  )
        if jet_value < best_jet[0]:
#            print pixel_jet_image_1.flatten() / np.sum(pixel_jet_image_1.flatten() ),  pixel_jet.flatten() / np.sum(pixel_jet.flatten() )       
            best_jet[0] = jet_value
            best_jet[1] = index_test
    
    

    if index_correct == best_jet[1]:
        number_of_correct += 1
   
print number_of_correct     
print 100.0 * number_of_correct / len(pixel_jets), "%"