# encoding: utf-8
# gabor.py
# 2012-3-8
# Eiichiro Momma

__author__ = 'Frederik Hagelskjær'
import numpy as np
import cv2


def mkKernel(ks, sig, th , lm, ps, gm):
        """ Check the kernel size"""
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""
        theta = th 
        psi = ps 
        sigma = np.float(sig)
        lmbd = np.float(lm)
        gamma = gm
        
        """Creating the kernel size"""        
        xs=np.linspace(-1*ks/10.,1*ks/10.,ks)
        ys=np.linspace(-1*ks/10.,1*ks/10.,ks)
#        xs=np.linspace(-1*ks,1*ks,ks)
#        ys=np.linspace(-1*ks,1*ks,ks)

        """Creating the kernel"""        
        x,y = np.meshgrid(xs,ys)        

        """ Angle of the signal """
        x_theta = x*np.cos(theta)+y*np.sin(theta)
        y_theta = -x*np.sin(theta)+y*np.cos(theta)
 
        #return np.array( np.exp(-0.5*(x_theta**2+gamma * y_theta**2)/sigma**2)*np.cos(2.*np.pi*x_theta/lmbd + psi),dtype=np.float32)
        gabor_kernel =  np.array( np.exp(-(x_theta**2 + y_theta**2)/(2*sigma**2) )*np.cos(2.*np.pi*x_theta/lmbd + psi), dtype=np.float32)
        gabor_kernel = cv2.resize(gabor_kernel, dsize = (21,21) )        
        return gabor_kernel
        """  Return the kernel                  The sigma signal                                           The sinus wave                                   """
        return np.array( (1/(sigma))*np.exp(-0.5*(x_theta**2+gamma * y_theta**2)/(sigma)**2)*np.cos(2.*np.pi*x_theta/lmbd + psi), dtype=np.float32)
	#  - np.exp( sigma / 2)


def mkKernelI(ks, sig, th , lm, ps, gm):
        if not ks%2:
            exit(1)

        """ Definition of the varibles"""
        gamma = gm
#        theta = th * np.pi/180.
        theta = th
        psi = ps
        sigma = np.float(sig)        
        lmbd = np.float(lm)
        
        """Creating the kernel size""" 
#        xs=np.linspace(-1*ks/10.,1*ks/10.,ks)
#        ys=np.linspace(-1*ks/10.,1*ks/10.,ks)
        xs=np.linspace(-1*ks,1*ks,ks)
        ys=np.linspace(-1*ks,1*ks,ks)
        """Creating the kernel""" 
        x,y = np.meshgrid(xs,ys)

        """ Angle of the signal """
        x_theta = x*np.cos(theta)+y*np.sin(theta)
        y_theta = -x*np.sin(theta)+y*np.cos(theta)

        gabor_kernel =  np.array( np.exp(-(x_theta**2 + y_theta**2)/(2*sigma**2) )*np.sin(2.*np.pi*x_theta/lmbd + psi), dtype=np.float32)
        gabor_kernel = cv2.resize(gabor_kernel, dsize = (21,21) )        
        return gabor_kernel

        return np.array( np.exp(-(x_theta**2 + y_theta**2)/(2*sigma**2) ) * np.sin(2.*np.pi*x_theta/lmbd + psi), dtype=np.float32)

        """  Return the kernel                  The sigma signal                                           The sinus wave                                   """      
        return np.array( (1/(sigma))*np.exp(-0.5*(x_theta**2+gamma * y_theta**2)/(sigma)**2) * np.sin(2.*np.pi*x_theta/lmbd + psi),dtype=np.float32)

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


        camera = cv2.VideoCapture(1)

        kernel_size = 60*2+1
        kernel_sigma = 6
        kernel_theta = 0
        kernel_psi = 90
        kernel_gamma = 10
        
        kernel_lambda = 2    



        ret,image = camera.read()
        cv2.imshow('input_image',image)

        gabor_kernel1 = complexKernel(kernel_size, kernel_sigma, kernel_theta, kernel_lambda, kernel_psi, kernel_gamma)
        kernel_theta = 90
        gabor_kernel2 = complexKernel(kernel_size, kernel_sigma, kernel_theta, kernel_lambda, kernel_psi, kernel_gamma)
        
    
        k = 0
        try:
            while(k%100 != 27):
                 _,image = camera.read()
                 cv2.imshow('input_image',image)
                 gabor_image1 = gabor_kernel1.analyze(image)
                 gabor_image2 = gabor_kernel2.analyze(image)
                 mag_combined = gabor_image1*gabor_image2  
                 cv2.imshow('gabor_image',mag_combined)
                 cv2.imshow('kernel',cv2.pyrUp(gabor_kernel1.get_kernel() ) )
                 k = cv2.waitKey(5)
        except(KeyError):
            pass
            
        del(camera)
        cv2.destroyAllWindows()