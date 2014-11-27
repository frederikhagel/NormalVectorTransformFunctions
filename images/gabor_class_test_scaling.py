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
        input_image = "orig_image_rezise.png"
        kernel_psi = 90
        kernel_gamma = 10
   
        large_kernel_list = []
        for scales in [-2,-1,0,1,2] :
            kernel_list = []
            for theta in [0,22.5,45,67.5,90, 90 + 22.5,  90 + 22.5*2, 90 + 22.5*3]:        
                kernel_list.append([ theta, complexKernel(51, 36*3+1, theta, 0.5+(36*2+1)/40., kernel_psi, kernel_gamma) ] )
            large_kernel_list.append([scales, kernel_list])
        
    
        k = 0
        while(k != 27):
#             _ = camera.get()
#             _,image = camera.read()
             image = cv2.imread(input_image)
             cv2.imshow('input_image',image)
             large_image_list = []
             kernel_large_list = []             

             for scale, kernel_listn in large_kernel_list:
                 image = cv2.imread(input_image)                 
                 pre_scale = scale
#                 print scale
                 while scale != 0:
                     if scale > 0:                          
                         image = cv2.pyrDown(image)
                         scale -= 1
                     else:
                         image = cv2.pyrUp(image)
                         scale += 1                            
                            
                         
                 analyzed_images = []
                 kernels = []
                 print 
                 for kernel_number, kernel in kernel_listn:
                     original_scale = pre_scale
#                     print "original_scale", original_scale
                     gabor_image = kernel.analyze(image) 
                     cv2.normalize( gabor_image, gabor_image,0,255,cv2.NORM_MINMAX) 
                     gabor_image = np.array(gabor_image, dtype=np.uint8)
#                     print gabor_image.shape
                     while original_scale != 0:
                         if original_scale > 0:                          
                             gabor_image = cv2.pyrUp(gabor_image)
                             original_scale -= 1
                         else:
                             gabor_image = cv2.pyrDown(gabor_image)
                             original_scale += 1     
                             
                     print gabor_image.max()                             
                     analyzed_images.append( gabor_image )
                     kernels.append( kernel.get_kernel() )
                     
                 former_image = cv2.hconcat( analyzed_images )
                 large_image_list.append( former_image )
                 
                 former_kernel = cv2.hconcat( kernels )
                 kernel_large_list.append( former_kernel )


             combinened_image = cv2.vconcat( large_image_list )
             combinened_kernels = cv2.vconcat( kernel_large_list )
             cv2.imshow('gabor_image', combinened_image)
             cv2.imshow('gabor_kernels', combinened_kernels)
             cv2.imwrite(input_image[:-4] + "_gabor.png", combinened_image)

             k = cv2.waitKey(0)

        cv2.destroyAllWindows()