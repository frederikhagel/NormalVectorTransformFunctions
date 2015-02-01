# encoding: utf-8
# gabor.py
# 2012-3-8
# Eiichiro Momma

__author__ = 'Frederik Hagelskjær'
import numpy as np
import cv2


def mkKernel(ks, sig, th , f0):
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""
        theta = th
        sigma = np.float(sig)        
        f0 = np.float(f0)
        
        """Creating the kernel size"""        
        xs=np.linspace(-(ks-1)/2,(ks-1)/2,ks)
        ys=np.linspace(-(ks-1)/2,(ks-1)/2,ks)
        """Creating the kernel""" 
        x,y = np.meshgrid(xs,ys)

        """ Angle of the signal """
        x_theta = x*np.cos(theta)+y*np.sin(theta)
        y_theta = -x*np.sin(theta)+y*np.cos(theta)


        return f0**2/(np.pi * sigma**2) * np.exp(-( (x_theta**2)*f0**2/(sigma**2) + (y_theta**2)*f0**2/(sigma**2) ))*np.cos(2*np.pi*f0*x_theta)
        
def mkKernelI(ks, sig, th , f0):
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""
        theta = th
        sigma = np.float(sig)        
        f0 = np.float(f0)
        
        """Creating the kernel size""" 
#        xs=np.linspace(-1*ks/10.,1*ks/10.,ks)
#        ys=np.linspace(-1*ks/10.,1*ks/10.,ks)
        xs=np.linspace(-(ks-1)/2,(ks-1)/2,ks)
        ys=np.linspace(-(ks-1)/2,(ks-1)/2,ks)
        """Creating the kernel""" 
        x,y = np.meshgrid(xs,ys)

        """ Angle of the signal """
        x_theta = x*np.cos(theta)+y*np.sin(theta)
        y_theta = -x*np.sin(theta)+y*np.cos(theta)


        return f0**2/(np.pi * sigma**2) * np.exp(-( (x_theta**2)*(f0**2)/(sigma**2) + (y_theta**2)*(f0**2)/(sigma**2) ))*np.sin(2*np.pi*f0*x_theta)

#        gabor_kernel =  np.array( np.exp(-(x_theta**2 + y_theta**2)/(sigma**2) )*np.sin(2.*np.pi*x_theta/lmbd + psi), dtype=np.float32)
#        gabor_kernel = cv2.resize(gabor_kernel, dsize = (cks,cks) )        
#        return gabor_kernel

class complexKernel:

    def __init__ (self, ks, sig, th, lm, scale):
        self.kernel_real = mkKernel(ks, sig, th, lm)
        self.kernel_imaginary = mkKernelI(ks, sig, th, lm )
        self.scale = scale
    
    def analyze(self, image):
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        original_shape = image.shape
        image = cv2.resize(image, dsize = ( int( image.shape[1]/(2**( self.scale )) ), int( image.shape[0]/(2**( self.scale )) )  ))

#        cv2.imshow("downscaled", image)
#        cv2.waitKey(0)

        src_f = np.array(image, dtype=np.float32)
        src_f /= 255.

        src_fI = np.array(image, dtype=np.float32)
        src_fI /= 255.

        dest = cv2.filter2D(src_f, cv2.CV_32F,self.kernel_real)
        destI = cv2.filter2D(src_fI, cv2.CV_32F,self.kernel_imaginary)                
        
        mag = np.sqrt(dest**2 + destI**2)
        mag = cv2.resize(mag, dsize = (original_shape[1], original_shape[0]))        

        return mag
        
    def get_kernel(self):
        #print self.kernel_imaginary.mean()
        kernelimg = self.kernel_real
        return kernelimg


if __name__ == '__main__':


#        camera = cv2.VideoCapture(0)

    import glob
    import random as rand

    k = 0
#                 _,image = camera.read()
    rotated_images = glob.glob('/home/frederik/pcl/images/vertical_images/*.jpeg')
    rand.shuffle( rotated_images )

    rotations = 8
    for scale in range(0,5):
        for rotation in range(0,rotations,1):
    
            kernel_size = 17
            k = 2
            p = 0.9
    
            kernel_sigma =  (( k +1)/(k-1))*np.sqrt(-np.log(p))
            kernel_theta = rotation*np.pi/rotations
            kernel_psi = 0
            kernel_gamma = 1
            k = 2
    
            kernel_lambda = 0.2
    
    #
    #
    #        ret,image = camera.read()
    #        cv2.imshow('input_image',image)
    
            gabor_kernel1 = complexKernel(kernel_size, kernel_sigma, kernel_theta, kernel_lambda, 0)
            kernel_theta = 90
            gabor_kernel2 = complexKernel(kernel_size, kernel_sigma, kernel_theta, kernel_lambda, 0)
             
            image = cv2.imread(rotated_images[3])
            cv2.imshow('input_image',image)
            gabor_image1 = gabor_kernel1.analyze(image)
            #                 gabor_image2 = gabor_kernel2.analyze(image)
            #                 mag_combined = gabor_image1*gabor_image2 
            gabor_image1 = cv2.normalize(gabor_image1, 0, 255 )
            cv2.imshow('gabor_image', gabor_image1  )
            
            gabor = cv2.normalize( gabor_kernel1.get_kernel(),0,255 )
            cv2.imshow('kernel', gabor )
            k = cv2.waitKey(0)
                
    #        del(camera)
    #        cv2.destroyAllWindows()