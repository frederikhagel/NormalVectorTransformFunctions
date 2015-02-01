# -*- coding: utf-8 -*-
"""
Created on Thu Jan 22 13:58:26 2015

@author: frederik
"""

import cv2
import numpy as np

ksize = 31

original_image = cv2.imread("/home/frederik/pcl/brodatz/textures/brodatz_D43.jpeg")
cv2.imshow("image", original_image)



for scale in [1, 2, 3, 4]:
    for theta in np.arange(0, np.pi, np.pi / 8):
        kern = cv2.getGaborKernel((ksize, ksize), 4.0, theta, 10.0, 0.5, 0, ktype=cv2.CV_32F)

        print np.max(kern)   
        
        kern = cv2.resize(kern, (ksize*scale,ksize*scale) )
        filtered_image_real = cv2.filter2D(original_image, cv2.CV_32F, kern)
        print np.min(filtered_image_real)
#        filtered_image_real /= np.max(filtered_image_real)


        print np.max(filtered_image_real)        
        
        kern = cv2.getGaborKernel((ksize, ksize), 4.0, theta, 10.0, 0.5, np.pi/2, ktype=cv2.CV_32F)
        kern = cv2.resize(kern, (ksize*scale,ksize*scale) )
        filtered_image_imaginary = cv2.filter2D(original_image, cv2.CV_32F, kern)
        filtered_image_real /= np.max(filtered_image_imaginary)        
        
        magnitude =  np.sqrt( filtered_image_real**2 + filtered_image_imaginary**2  ) #cv2.CV_8UC3)
        
        
        cv2.imshow("result", magnitude)
        cv2.imshow("kernel", kern)
        cv2.waitKey(5)
    
    
#cv.resize(np.uint8( (m) ), (kernel_size*20,kernel_size*20)))