# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 18:56:33 2015

@author: frederik
"""


import cv2

import glob
import numpy as np
from jet_space import jetSpace

gabor_jet_kernel = jetSpace(101, 11, 2.67*1.3, 1/(0.2*np.pi/2),5,12,1)



fie_name = "/home/frederik/pcl/brodatz/textures/lena_1000.jpeg"
fie_name = "/home/frederik/pcl/brodatz/video_images/lena_images/transformed_image0.0 0.0 0.0.jpeg"

image = cv2.imread(fie_name)
   
#cv2.imshow("original_image", image)
#cv2.waitKey(0)

new_image = cv2.resize(image, (1000,1000), 1/0.48, 1/0.48, 0)

cv2.imshow("original_image", new_image)
cv2.waitKey(0)



response = gabor_jet_kernel.calculateResponse(new_image)
pixel_jet_image_1 = gabor_jet_kernel.getPixelJet((500,500),response)


best_jet = [10.0 , 0.0]

files = glob.glob('/home/frederik/pcl/brodatz/video_images/lena_images/transformed_image*.jpeg')
files.sort()

#files = []

brodatz_names = []
for postD in range(1,14) + range(15,111):
    brodatz_names.append( "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(postD) + ".jpeg")


brodatz_names = []


for fie_name in files + brodatz_names:
    image = cv2.imread(fie_name)
    if image.shape[0] < 1000:
        image = cv2.resize(image, (1000,1000), 1/0.48, 1/0.48, 0)

    response = gabor_jet_kernel.calculateResponse(image)
    
    pixel_jet = gabor_jet_kernel.getPixelJet((500,500),response)

#    print pixel_jet.shape
#    print pixel_jet_image_1.shape

    jet_value = gabor_jet_kernel.compareJetSpace( pixel_jet_image_1.flatten() / np.sum(pixel_jet_image_1.flatten() ) , pixel_jet.flatten() / np.sum(pixel_jet.flatten() )  )
#    print pixel_jet_image_1.flatten(), pixel_jet.flatten()  

    if jet_value < best_jet[0]:
#        print pixel_jet_image_1.flatten() / np.sum(pixel_jet_image_1.flatten() ),  pixel_jet.flatten() / np.sum(pixel_jet.flatten() )       
        best_jet[0] = jet_value
        best_jet[1] = fie_name
        
    
    print "D", fie_name, jet_value 

    

    pixel_jet = cv2.pyrUp(cv2.pyrUp(cv2.pyrUp(cv2.pyrUp(pixel_jet))))    

    cv2.imshow("pixel jet", pixel_jet)
            
    response_image = gabor_jet_kernel.createImage(response)
    #cv2.imwrite("../test_response.jpeg", response_image)
    
    show_image = cv2.resize(response_image, dsize = (800,500) )
    cv2.imshow("image", image)
    cv2.imshow("../test_response.jpeg", show_image)
    cv2.waitKey(1)

print best_jet


