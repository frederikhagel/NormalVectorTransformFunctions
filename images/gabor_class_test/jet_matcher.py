# -*- coding: utf-8 -*-
"""
Created on Fri Jan 23 12:21:49 2015

@author: frederik
"""

import cv2
import numpy as np
from jet_space_new import jetSpace

class texture:
    def __init__(self, image, name, pixelJet = None):
        self.image = image
        self.name = name
        self.pixelJet = pixelJet

    def getImage(self):
        return self.image
        
    def getName(self):
        return self.name
    
    def setPixelJet(self, pixelJet):
        self.pixelJet = pixelJet        
        
    def getPixelJet(self):
        return self.pixelJet
        
        

class jetMatcher:
    def __init__(self, ks = 15, p = 0.9, k = 2, lm = 0.25 ,textures = []):
        
        self.gabor_jet_kernel = jetSpace(ks, p, k, lm )                
        self.textures = []
#        self.gabor_jet_kernel.inspect_kernel(0)
        for texture in textures:
            self.addTexture(texture)

    def addTexture(self, texture):
        image = texture.getImage()
        response = self.gabor_jet_kernel.calculateResponse(image)    
        pixel_jet = self.gabor_jet_kernel.getPixelJet((240,240), response)
        texture.setPixelJet( pixel_jet )
        self.textures.append( texture  )
        
    def addImage(self, image, name):
        response = self.gabor_jet_kernel.calculateResponse(image)    
        pixel_jet = self.gabor_jet_kernel.getPixelJet((240,240), response)
        new_texture = texture(image, name, pixel_jet )
        self.textures.append( new_texture  )

    def findMatch(self,image):
        response = self.gabor_jet_kernel.calculateResponse(image)    
        pixel_jet = self.gabor_jet_kernel.getPixelJet((240,320), response)        
        best_jet = [0.0 , 0.0]
    
        for texture in self.textures:    
#            print texture.getName()
            jet_value = self.gabor_jet_kernel.compareJetSpace( texture.getPixelJet() , pixel_jet  )
    
            if jet_value > best_jet[0]:
                best_jet[0] = jet_value
                best_jet[1] = texture.getName()

        return best_jet
            
    def calculateResponseRotationShift(self, image):   
        gabor_response = []    
        for kernel_listn in self.gabor_jet:                                  
            analyzed_images = []
            for kernel in kernel_listn:
                gabor_image = kernel.analyze(image)        
                analyzed_images.append(gabor_image)
            gabor_response.append(analyzed_images)
        return gabor_response           
           
           
import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)

lines = []



histogram_list = []
result_file = '../../brodatz/complete_comparison_results_vertical.txt'

for correction in [1, 2]:
    f = open(result_file, 'r')
    
    result_to_rot = {'0.0':0, '0.1745':0, 
       '0.3491':0, '0.5236':0, 
        '0.6981':0, '0.8727':0, 
        '1.047':0, '1.222':0, '1.396':0}   
    
    result_list = []    
    new = False
    
    index = 1
    best_index = 0
    best_result = np.inf
    actual_index = 2
    
    number_of_image = 0
    number_of_true = 0

    
    rotations = []
    

    
    for line in f:
        datalist = line.split(' ')
    #    print datalist
    
        if len(datalist) > 3 and new == False:
            new = True
#            print datalist[0]

            number_of_image += 1

            tmp = datalist[0].split('.')
            tmp = tmp[0].split('D')
            actual_index = int(tmp[-1])

            actual_rotation = datalist[1:]
            if datalist[1:] not in rotations:
                rotations.append(datalist[1:])

            print actual_rotation[2][:-2]

        elif len(datalist) > 3 and new == True:
    #        print best_index
    #        print actual_index        
            if best_index == actual_index:
    #            print True
                number_of_true += 1
                result_to_rot[ actual_rotation[2][:-2] ] = result_to_rot[ actual_rotation[2][:-2] ] + 1
    #            print best_result
            new =True
    #        print datalist[0]
            number_of_image += 1
            index = 1
            best_index = 0
            best_result = np.inf

            tmp = datalist[0].split('.')
            tmp = tmp[0].split('D')
            actual_index = int(tmp[-1])
            
#            if actual_rotation != datalist[1:]:
#                print "not the same"
            
            actual_rotation = datalist[1:]
            if datalist[1:] not in rotations:
                rotations.append(datalist[1:])


        else:
    #        print datalist[0]
            number = datalist[ correction ]#[1:-1]
#            print actual_index
            #1.047 and 0.5236 and 1.222
            if actual_index == 99 and actual_rotation[1] == '1.222' and correction == 2:
                histogram_list.append(number)
    #        print number
    #        number = datalist[2][:-2]
            tmp = datalist[0].split('.')
    #        print tmp[0]
            tmp = tmp[0].split('D')
    #        print tmp[-1]
            index = int(tmp[-1])
    #        print number
            if number[-4:-2] == "e+":
                number = float(number[:-4]) * (10 ** float(number[-1]))
            else:
                number = float(number)
    #        print number
            if number < best_result:
                best_index = index
                best_result = number
            #print datalist[1]
    #        index = index + 1
            #for data in datalist:
            #print data
    
    print 
    print "number_of_true", number_of_true
    
    print "number_of_image", number_of_image

    result = []    
            
    for index in [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222', '1.396' ]:
        print "rotation " + index + "\t" + str(result_to_rot[index]) + "\t" + str(result_to_rot[index]/110.)
        result.append(result_to_rot[index])        
        
    tmp, = plt.plot([ 0.0, 0.1745, 0.3491, 0.5236, 0.6981, 0.8727, 1.047, 1.222, 1.396 ], result, label='Line 2')  

    
    lines.append(tmp)

    print len(lines)            
            

for scaling in [ 0.2]: #0.5, 0.25,

    gabor_texture_matcher = jetMatcher(17, 0.9, 2, 0.2 )

    result_to_rot = {'0.0':0, '0.1745':0, 
    '0.3491':0, '0.5236':0, 
    '0.6981':0, '0.8727':0, 
    '1.047':0, '1.222':0, '1.396':0}    
    
    for testD in range(1,14) + range(15,112):

        input_image = "/home/frederik/pcl/brodatz/textures/brodatz_D" + str(testD) + ".jpeg"
        image = cv2.imread(input_image)
        image = cv2.resize(image, ( 480, 480 ), 0.48, 0.48, 0)
        
        gabor_texture_matcher.addImage(image, 'D' + str(testD) )
        
    
    import glob
    
#    rotated_images = glob.glob('/home/frederik/pcl/images/all_images/*.jpeg')
    rotated_images = glob.glob('/home/frederik/pcl/images/vertical_images/*.jpeg')
    print len(rotated_images)
    
    all_images = []
    
    for image in rotated_images:
        datalist = image.split('/')
        
        if len(datalist[-1].split('_')) == 3:

            transform = datalist[-1].split('_')[0]
            rotation = datalist[-1].split('_')[1][5: len(datalist[-1].split('_')[1]) - 12 + len(datalist[-1].split('_')[2]) ]
            image_index = datalist[-1].split('_')[2][:-5] 
            if transform == 'transformed':
                all_images.append( [ transform, rotation, image_index, image ] )        
            
    
    print len(all_images)
    
    number_of_correct = 0    
    
    
    import time
    
    timestamp = time.time()


    good_mathes = []
    bad_matches = []

    
    for transform, rotation, image_index, image_to_test in all_images:    

        image = cv2.imread(image_to_test)

        match = gabor_texture_matcher.findMatch(image)        

        if image_index == match[1]:
            number_of_correct += 1
            result_to_rot[rotation.split(' ')[2]] += 1
            good_mathes.append(match[0])
        else:
#            print match, image_index             
            bad_matches.append(match[0])


    run_time = time.time() - timestamp 

    print run_time
    print float(run_time)/len(all_images)

    print "Scaling: ", scaling        
    print "Number of correct:", number_of_correct
    print "mean", np.mean(good_mathes), np.mean(bad_matches)
    
#    import matplotlib.pyplot as plt
#    fig = plt.figure()
#    ax = fig.add_subplot(111)    
    
#    lines = []
    result = []    
    for index in [ '0.0', '0.1745', '0.3491', '0.5236', '0.6981', '0.8727', '1.047', '1.222', '1.396' ]:
        print result_to_rot[index]
        result.append(result_to_rot[index])        
        
    tmp, = plt.plot([ 0.0, 0.1745, 0.3491, 0.5236, 0.6981, 0.8727, 1.047, 1.222, 1.396 ], result, label='Line 2')  

    
    lines.append(tmp)

    plt.xlabel('Rotation')
    plt.ylabel('Recognized')
    plt.legend([lines[0], lines[1], lines[2]], ['No correction', 'Correction', 'Gabor Corrected'])
    plt.grid()
    plt.show()                    