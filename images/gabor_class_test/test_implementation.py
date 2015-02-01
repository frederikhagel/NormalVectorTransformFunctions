# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space import jetSpace

gabor_jet_kernel = jetSpace(101, 11, 2.67*1.3, 1/(0.2*np.pi/2),5,8,1)


input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D11.jpeg"
image = cv2.imread(input_image)
response = gabor_jet_kernel.calculateResponse(image)
pixel_jet_image_1 = gabor_jet_kernel.getPixelJet((503,498),response)

best_jet = [10.0 , 0.0]

for postD in range(1,14) + range(15,111):

    input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(postD) + ".jpeg"

    image = cv2.imread(input_image)
    
    response = gabor_jet_kernel.calculateResponse(image)
    
    pixel_jet = gabor_jet_kernel.getPixelJet((500,500),response)

    print pixel_jet.shape
    print pixel_jet_image_1.shape

    jet_value = gabor_jet_kernel.compareJetSpace( pixel_jet_image_1.flatten() / np.sum(pixel_jet_image_1.flatten() ) , pixel_jet.flatten() / np.sum(pixel_jet.flatten() )  )
#    print pixel_jet_image_1.flatten(), pixel_jet.flatten()  

    if jet_value < best_jet[0]:
        print pixel_jet_image_1.flatten() / np.sum(pixel_jet_image_1.flatten() ),  pixel_jet.flatten() / np.sum(pixel_jet.flatten() )       
        best_jet[0] = jet_value
        best_jet[1] = postD
        
    
    print "D", postD, jet_value 

    

    pixel_jet = cv2.pyrUp(cv2.pyrUp(cv2.pyrUp(cv2.pyrUp(pixel_jet))))    

    cv2.imshow("pixel jet", pixel_jet)
            
    response_image = gabor_jet_kernel.createImage(response)
    #cv2.imwrite("../test_response.jpeg", response_image)
    
    show_image = cv2.resize(response_image, dsize = (800,500) )
    cv2.imshow("original_image", image)
    cv2.imshow("../test_response.jpeg", show_image)
    cv2.waitKey(1)

print best_jet