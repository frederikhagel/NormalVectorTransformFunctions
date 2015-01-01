# -*- coding: utf-8 -*-
"""
Created on Mon Dec  1 15:47:57 2014

@author: frederik
"""

# encoding: utf-8
# gabor.py
# 2012-3-8
# Eiichiro Momma

__author__ = 'Frederik Hagelskjær'
import numpy as np
import cv2


def mkKernel(ks, sig, th , om, ps, gm):
        """ Check the kernel size"""
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""
        theta = th 
        psi = ps 
        sigma = np.float(sig)
        omega = np.float(om)
        gamma = gm
        
        """Creating the kernel size"""        
#        xs=np.linspace(-1*ks,1*ks/10.,ks)
#        ys=np.linspace(-1*ks/10.,1*ks/10.,ks)
        xs=np.linspace(-1*ks,1*ks,ks)
        ys=np.linspace(-1*ks,1*ks,ks)

        """Creating the kernel"""        
        x,y = np.meshgrid(xs,ys)        

 
        #return np.array( np.exp(-0.5*(x_theta**2+gamma * y_theta**2)/sigma**2)*np.cos(2.*np.pi*x_theta/lmbd + psi),dtype=np.float32)
        gabor_kernel =  np.array( np.exp(-(x**2 + y**2)/(2*sigma**2) )*np.cos(2.*np.pi*(x*np.cos(theta)+y*np.sin(theta) ) * omega), dtype=np.float32)     
        return gabor_kernel
        """  Return the kernel                  The sigma signal                                           The sinus wave                                   """


def mkKernelI(ks, sig, th , om, ps, gm):
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""

#        theta = th * np.pi/180.
        theta = th

        sigma = np.float(sig)        
        omega = np.float(om)
        
        """Creating the kernel size""" 
#        xs=np.linspace(-1*ks/10.,1*ks/10.,ks)
#        ys=np.linspace(-1*ks/10.,1*ks/10.,ks)
        xs=np.linspace(-1*ks,1*ks,ks)
        ys=np.linspace(-1*ks,1*ks,ks)
        """Creating the kernel""" 
        x,y = np.meshgrid(xs,ys)


        gabor_kernel =  np.array( np.exp(-(x**2 + y**2)/(2*sigma**2) )*np.sin(2.*np.pi*(x*np.cos(theta)+y*np.sin(theta) ) * omega), dtype=np.float32)     
        return gabor_kernel

class complexKernel:
    
    def __init__ (self, ks, sig, th, lm, ps, gm):
        self.kernel_real = mkKernel(ks, sig, th, lm, ps, gm )
        self.kernel_imaginary = mkKernelI(ks, sig, th, lm, ps, gm )
    
    def analyze(self, image):
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        src_f = np.array(image, dtype=np.float32)
        src_f /= 255.

        src_fI = np.array(image, dtype=np.float32)
        src_fI /= 255.

        dest = cv2.filter2D(src_f, cv2.CV_32F,self.kernel_real)
        destI = cv2.filter2D(src_fI, cv2.CV_32F,self.kernel_imaginary)                
        
        mag = np.sqrt(dest**2 + destI**2)
        
        return mag
        
    def get_kernel(self):
        #print self.kernel_imaginary.mean()
        kernelimg = self.kernel_real*2.+0.5
        return kernelimg



if __name__ == '__main__':


#        camera = cv2.VideoCapture(0)
        input_image = "test_image_rezise.png"
        kernel_psi = 0 # np.pi/2.
        kernel_gamma = 1
   
        large_kernel_list = []
        for scales in [-1,0,1,2,3] :
            kernel_list = []
            n = 8.
            hidden = [0,22.5,45,67.5,90, 90 + 22.5,  90 + 22.5*2, 90 + 22.5*3]
            for theta in range(int(n)):        
#                print theta/12. * 2*np.pi
                kernel_list.append([ (theta/n) * np.pi, complexKernel(11,2.67, (theta/n) * np.pi , np.pi/2, kernel_psi, kernel_gamma) ] )
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
                     print gabor_image.max()                             
                     analyzed_images.append( gabor_image )
                     kernels.append( kernel.get_kernel() )
                     
                 former_image = cv2.hconcat(  analyzed_images )
                 print former_image.shape

                 large_image_list.append( former_image )
                 
                 former_kernel = cv2.hconcat( kernels )
                 print former_kernel.shape
                 kernel_large_list.append( former_kernel )


             combinened_image = cv2.vconcat( large_image_list )
             combinened_kernels = cv2.vconcat( kernel_large_list )
             
#             combinened_image = np.array( combinened_image, np.uint8)
#             cv2.normalize( combinened_image, combinened_image,0,255, cv2.NORM_MINMAX) 
             gabor_image = np.array(gabor_image, dtype=np.uint8)
             cv2.imshow('gabor_image', combinened_image*2.+0.5)

             cv2.imshow('gabor_kernels', combinened_kernels)
             cv2.imwrite(input_image[:-4] + "_gabor.png", (combinened_image*2.+0.5) *100)
             cv2.imwrite("gabor_kernels.png", np.array(combinened_kernels*255, np.uint8))

             k = cv2.waitKey(0)
             break
        cv2.destroyAllWindows()