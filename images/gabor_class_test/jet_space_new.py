# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:29:16 2015

@author: frederik
"""

import cv2
import numpy as np

#from gabor_complex_new import complexKernel
from gabor_complex_opencv import complexKernel

class jetSpace:
    
    def __init__ (self, ks = 15, p = 0.9, k = 2, lm = 0.25):

#        print  ks, cks, sig, lm, nofscales, noftheta, gm

        self.gabor_jet = []
        
        for scale in range(0,5):
            kernel_list = []
            
            rotations = 8
            for thetaadjustment in range(rotations):        
                theta = float(thetaadjustment)/rotations * np.pi 
                
                kernel_sigma = (( k +1)/(k-1))*np.sqrt(-np.log(p))
                kernel_sigma = kernel_sigma/ (lm**2)

                kernel_list.append( complexKernel(ks, kernel_sigma, theta, lm, scale ) )
            self.gabor_jet.append( kernel_list )
    
    def calculateResponse(self, image):   
        gabor_response = []    
        for kernel_listn in self.gabor_jet:                                  
            analyzed_images = []
            for kernel in kernel_listn:
                gabor_image = kernel.analyze(image)        
                analyzed_images.append(gabor_image)
            gabor_response.append(analyzed_images)
        return gabor_response
            
    def inspect_kernel(self, time):
        gabor_large_list = []
        for kernel_listn in self.gabor_jet:                
            analyzed_images = []
            for kernel in kernel_listn:
                gabor_image = kernel.get_kernel()
                analyzed_images.append(gabor_image)
                gabor_images = cv2.hconcat(analyzed_images)
            gabor_large_list.append(gabor_images)
        image_to_show = cv2.vconcat(gabor_large_list)
        image_to_show = cv2.normalize( image_to_show,0,255 )
        cv2.imshow("Gabor Kernels", image_to_show)
        cv2.waitKey(time)
        return image_to_show
        
    def createImage(self, gabor_response):
        large_image_list = []
        for image_list in gabor_response:
            large_image_list.append(cv2.hconcat( image_list ))
#            print cv2.hconcat( image_list ).shape
        combinened_image = cv2.vconcat( large_image_list )
        return combinened_image                                 
                          
    def getPixelJet(self,pos, gabor_list):
        colums = len(gabor_list)
        rows = len(gabor_list[0])
        pixel_jet = np.zeros((colums,rows), np.float )
        for line_index, line in enumerate( gabor_list ):
            for gabor_index, gabor in enumerate(line):
#                print line_index, gabor_index, gabor.shape
                gabor = cv2.blur(gabor,(5,5))
                pixel_jet[line_index,gabor_index] = gabor[ pos[0],pos[1] ]
        
        return pixel_jet

    def compareJetSpace(self, jet1, jet2):
         return np.dot(jet1.flatten(),jet2.flatten())/(  np.linalg.norm( jet1.flatten() ) *  np.linalg.norm( jet2.flatten() )  )

if __name__ == '__main__':

    jet = jetSpace(15, 0.9, 2)
    jet.inspect_kernel(0)