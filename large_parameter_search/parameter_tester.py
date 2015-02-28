# -*- coding: utf-8 -*-
"""
Created on Fri Feb 20 11:05:53 2015

@author: frederik
"""

import os
import numpy as np

#os.system('./build/gabor_jet 2 0.4 0 4 12 0.2 0')

os.system('./build/gabor_jet ' + str(np.sqrt(np.sqrt(2))) + ' 0.5 0 12 12 0.2 1')


#testing size of p
#for _p in range(0,19):
#    p = 0.05 + _p/20.0
#    print p
#    os.system('./build/gabor_jet 2 ' + str(p) + ' 0 4 12 0.2')


#import numpy as np
#
##testing the sigma size, along with nr. of kernels
#for _ns in [6,8,12]:
#    os.system('./build/gabor_jet ' + str(np.sqrt(np.sqrt(2))) + ' 0.5 0 ' + str(_ns) + ' 12 0.2 1')
#
#
#for _ns in range(4,8):
#    os.system('./build/gabor_jet ' + str(np.sqrt(2)) + ' 0.4 0 ' + str(_ns) + ' 12 0.2 1')


#for _ns in range(4,12):
#    p = 0.05 + _p/20.0
#    print p
#    os.system('./build/gabor_jet 2 0.4 0 ' + str(ns) + ' 12 0.2')


#os.system('./build/gabor_jet 2 0.5 0 4 12 0.2')
#
