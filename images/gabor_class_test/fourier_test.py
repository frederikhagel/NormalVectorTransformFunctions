# -*- coding: utf-8 -*-
"""
Created on Tue Oct  8 22:54:37 2013

@author: frederik
"""

# -*- coding: utf-8 -*-
"""
Created on Tue Sep 24 23:29:03 2013

@author: frederik
"""
import numpy as np

import cv2

from gabor_complex_opencv import complexKernel

for scale in [1, 2, 4, 8]:    
    for theta in range(0,12):
        
        theta_corrected = theta /12.0 * np.pi
        
        p = 0.5
        
        k = 2.0
                        
        kernel_sigma = ((k+1)/(k-1))*np.sqrt(-np.log(p))
        print theta_corrected, scale
        
        
        sigma = kernel_sigma
        
        jet = complexKernel(19, kernel_sigma, theta_corrected, 0.2, 0)
     
        image_large = np.zeros((480,640),np.float32)      
     
     
        image = jet.get_kernel()
        cv2.imshow("original", image)    
    
        if scale != 1:
            image = cv2.resize(image, dsize = ( int( image.shape[0]*scale + 1 ), int( image.shape[1]*scale + 1 ) ) )
     
        image_large[ image_large.shape[0]/2 - (image.shape[0] -1 ) /2 - 1 : image_large.shape[0]/2 + (image.shape[0] - 1) /2 , image_large.shape[1]/2 - (image.shape[1] - 1) /2 - 1 : image_large.shape[1]/2 + (image.shape[1] - 1) /2 ] = image
        
    
        image = cv2.pyrUp(image)    
        image = cv2.pyrUp(image)   
        
        image_gray = image_large
    
      
    #    image_gray = cv2.pyrUp(image_gray)  
        
        #image = cv2.imread("../perspective_result.jpeg")
        
        cv2.imshow("large original", image_large)
        
        #image_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        
        
        
        dftl = cv2.dft(np.float32(image_gray),flags = cv2.DFT_COMPLEX_OUTPUT)
        d, f = cv2.split(dftl)
        m, p = cv2.cartToPolar(d, f)
        m = np.fft.fftshift(m)
            
        cv2.imshow("Magnitude Kernel", np.log(1+ m) )
        
        
        image_to_analyze = cv2.imread('/home/frederik/pcl/images/perspective_result.jpeg', 0)        

        
        
        src_f = np.array(image_to_analyze, dtype=np.float32)
        src_f /= 255.
        
        dftl = cv2.dft(src_f,flags = cv2.DFT_COMPLEX_OUTPUT)
        da, fa = cv2.split(dftl)
        ma, pa = cv2.cartToPolar(da, fa)
        ma = np.fft.fftshift(ma)
 
        result = m * ma
                       
        ma = np.fft.fftshift(result)
        d2, f2 = cv2.polarToCart(ma, pa)

        test = np.zeros( (d.shape[0] , d.shape[1] , 2), dtype=np.float)         
        test[:,:,0] = d2
        test[:,:,1] = f2
        
        img_f = cv2.dft(test,flags = cv2.DFT_INVERSE + cv2.DFT_SCALE + cv2.DFT_REAL_OUTPUT)   

                
        cv2.imshow("Filter ", img_f )        

        
        #m = m * im
        #cv2.imshow("Magnitude_after", np.uint8( 20*np.log(m) ) )
        #cv2.imshow("Filter", np.uint8(im*255))
        
        
        m = np.fft.fftshift(m)
        d2, f2 = cv2.polarToCart(m, p)
        
        test = np.zeros( (d.shape[0] , d.shape[1] , 2), dtype=np.float) 
        test[:,:,0] = d2
        test[:,:,1] = f2
        
        img_f = cv2.dft(test,flags = cv2.DFT_INVERSE + cv2.DFT_SCALE + cv2.DFT_REAL_OUTPUT)
        
    #    cv2.imshow("Filtered Image",  img_f ) 
        cv2.waitKey(0)
#        cv2.destroyAllWindows()
