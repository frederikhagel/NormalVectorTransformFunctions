# -*- coding: utf-8 -*-
"""
Created on Tue Oct 28 17:50:26 2014

@author: frederik
"""

import cv2
from gabor_complex_13 import complexKernel

import numpy as np

if __name__ == '__main__':


    for postD in range(11,14) + range(15,110):
#        camera = cv2.VideoCapture(0)
        print postD
        input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(postD) + ".jpeg"
        kernel_psi = 0 # np.pi/2.
        kernel_gamma = 1
   
        large_kernel_list = []
        for scales in [0,1,2,3,4,5] :
            kernel_list = []
            n = 8.

            for theta in range(int(n)):        
#                print theta/12. * 2*np.pi
                kernel_list.append([ (theta/n) * np.pi, complexKernel(101,2.67*1.3, (theta/n) * np.pi , 1/(0.2*np.pi/2), kernel_psi, kernel_gamma) ] )
            large_kernel_list.append([scales, kernel_list])


        print postD
        input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(postD) + ".jpeg"
        kernel_psi = 0 # np.pi/2.
        kernel_gamma = 1
   
        large_kernel_list = []
        for scales in [0,1,2,3,4,5] :
            kernel_list = []
            n = 8.

            for theta in range(int(n)):        
#                print theta/12. * 2*np.pi
                kernel_list.append([ (theta/n) * np.pi, complexKernel(10*2**scales + 1,2.67*1.3*2**scales, (theta/n) * np.pi , 1/(0.2*np.pi/2) * 2**scales, kernel_psi, kernel_gamma) ] )
            large_kernel_list.append([0, kernel_list])
        
    
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
#                 while scale != 0:
#                     if scale > 0:                          
#                         image = cv2.pyrDown(image)
#                         scale -= 1
#                     else:
#                         image = cv2.pyrUp(image)
#                         scale += 1                            
                            
                         
                 analyzed_images = []
                 kernels = []
                 print 
                 for kernel_number, kernel in kernel_listn:
                     original_scale = pre_scale
#                     print "original_scale", original_scale

                     gabor_image = kernel.analyze(image) 
                     
#                     cv2.normalize( gabor_image, gabor_image,0,255,cv2.NORM_MINMAX) 
#                     gabor_image = np.array(gabor_image, dtype=np.uint8)
#                     print gabor_image.shape
#                     while original_scale != 0:
#                         if original_scale > 0:                          
#                             gabor_image = cv2.pyrUp(gabor_image)
#                             original_scale -= 1
#                         else:
#                             gabor_image = cv2.pyrDown(gabor_image)
#                             original_scale += 1     
                     
#                     gabor_image = cv2.pyrUp( gabor_image, dstsize = (100,100 ) )
#                     gabor_image = gabor_image[gabor_image.shape[0]/2:gabor_image.shape[0]/2 + 1,gabor_image.shape[1]/2:gabor_image.shape[1]/2 + 1]
#                     print "shape", gabor_image.shape                     
                     gabor_image = cv2.resize(gabor_image, dsize = (100,100) )       
                     gabor_image = cv2.blur(gabor_image,(5,5))
                     print gabor_image.max()      
                     
                     mean_value = str(gabor_image[50,50])                    
                     
                     cv2.putText(gabor_image, str(mean_value), (0,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,0),3)
                     cv2.putText(gabor_image,str(mean_value), (0,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,0),2)
                     
                     analyzed_images.append( gabor_image )
#                     kernels.append( kernel.get_kernel() )
                                          
                     kernels.append( np.ones( (11,11), np.float)*float(mean_value)  )   
                     
                 former_image = cv2.hconcat(  analyzed_images )
                 print former_image.shape

                 large_image_list.append( former_image )
                 
                 former_kernel = cv2.hconcat( kernels )
                 print former_kernel.shape
                 kernel_large_list.append( former_kernel )


             combinened_image = cv2.vconcat( large_image_list )
             combinened_kernels = cv2.vconcat( kernel_large_list )
             
#             combinened_image = np.array( combinened_image, np.uint8)
#             cv2.normalize( combinened_image, combinened_image,0,1, cv2.NORM_MINMAX) 
             gabor_image = np.array(gabor_image, dtype=np.uint8)
             cv2.imshow('gabor_image', combinened_image*2.+0.5)

             cv2.imshow('gabor_kernels', combinened_kernels)
#             cv2.imwrite(input_image[:-4] + "_gabor.png", (combinened_image*2.+0.5) *100)
#             cv2.imwrite("gabor_kernels.png", np.array(combinened_kernels*255, np.uint8))

             k = cv2.waitKey(0)
             break
    cv2.destroyAllWindows()