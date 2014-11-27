# -*- coding: utf-8 -*-
"""
Created on Tue Oct 28 17:50:26 2014

@author: frederik
"""

import cv2
from gabor_complex import complexKernel

import numpy as np

if __name__ == '__main__':


#        camera = cv2.VideoCapture(0)

        kernel_psi = 90
        kernel_gamma = 10
   
        large_kernel_list = []
        for size, sigma in [[40*0.5+1,36*0.5+1],[40*1+1,36*1+1],[40*2+1,36*2+1],[40*4+1,36*4+1],[40*8+1,36*8+1] ]:
            kernel_list = []
            for theta in [0,22.5,45,67.5,90, 90 + 22.5,  90 + 22.5*2, 90 + 22.5*3]:        
                kernel_list.append([ theta, complexKernel(51, sigma, theta, 0.5+sigma/40., kernel_psi, kernel_gamma) ] )
            large_kernel_list.append([sigma, kernel_list])
        
    
        k = 0
        while(k != 27):
#             _ = camera.get()
#             _,image = camera.read()
             image = cv2.imread("test_image_rezise_u.png")
             cv2.imshow('input_image',image)
             large_image_list = []
             kernel_large_list = []             
             
             for sigma, kernel_listn in large_kernel_list:
                 analyzed_images = []
                 kernels = []
                 for kernel_number, kernel in kernel_listn:
                     
                     gabor_image = kernel.analyze(image) 
                     cv2.normalize( gabor_image, gabor_image,0,255,cv2.NORM_MINMAX) 
                     gabor_image = np.array(gabor_image, dtype=np.uint8)
                     analyzed_images.append(   gabor_image )
                     kernels.append( kernel.get_kernel() )
                    
                 former_image = cv2.hconcat( analyzed_images )
                 large_image_list.append( former_image )
                 
                 former_kernel = cv2.hconcat( kernels )
                 kernel_large_list.append( former_kernel )

             combinened_image = cv2.vconcat( large_image_list )
             combinened_kernels = cv2.vconcat( kernel_large_list )
             cv2.imshow('gabor_image', combinened_image)
             cv2.imshow('gabor_kernels', combinened_kernels)

             k = cv2.waitKey(5)

        cv2.destroyAllWindows()