# -*- coding: utf-8 -*-
"""
Created on Sat Dec 13 17:27:19 2014

@author: frederik
"""

# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 01:32:46 2013

@author: Administrator
"""
import urllib
import urllib2
import os
import shutil

import cv2
import numpy as np

newpath = 'songs' 
try: 
    if os.path.exists(newpath): shutil.rmtree(newpath)
    os.makedirs(newpath)
except:
    pass

req = urllib2.Request('http://www.ux.uis.no/~tranden/brodatz.html')

response = urllib2.urlopen(req)
the_page = response.read()

print the_page

big_list = []

for n, lines in enumerate(the_page):
    if the_page[n-4:n] == ".gif":
        list_ = ""
        i = n - 1 
        while the_page[i] != 'D':
            
            list_ = the_page[i] + list_
            i = i - 1
#        if list_[0:4] == 'http':
#            big_list.append(list_ + ".gif")
        print the_page[i] + list_       
        big_list.append(the_page[i] + list_)                 
                 
image = urllib.URLopener()

for song in big_list:
    print song

    
import Image
import sys

f = open('images.txt', 'w')

for n, big in enumerate(big_list[:-2]):
    print big
#    urllib.urlretrieve( "http://www.ux.uis.no/~tranden/brodatz/" + big, "web_brodatz_" + big[1:])
    urllib.urlretrieve( "http://www.ux.uis.no/~tranden/brodatz/" + big, "web_brodatz_" + big[:])
    print  "web_brodatz_" + big[:]
    
    
    im = Image.open("web_brodatz_" + big[:])
    mypalette = im.getpalette()

#    im.putpalette(mypalette)
    new_im = Image.new("RGBA", im.size)
    new_im.paste(im)
    new_im.save('foo'+ big[:-4]+'.png')


#    i += 1
#            im.seek(im.tell() + 1)
#
#    except EOFError:
#        pass # end of sequence
#
#processImage('gif_example.gif')
#    
    
    image_original = cv2.imread('foo'+ big[:-4]+'.png')
    cv2.imshow("image_original", image_original)
    cv2.waitKey(5)

    large_image = np.zeros((1000,1000,3), np.uint8)

    print image_original.shape

    large_image[500 - 640/2:500 - 640/2 + 640 ,500 - 640/2: 500 - 640/2 + 640] = image_original[0:640,0:640]

    large_image[0,0] = [255, 0, 0]
    
    cv2.imshow("1000x1000", large_image)    
    cv2.waitKey(5)
    cv2.imwrite("brodatz_" + big[:-4] + '.jpeg', large_image )
    f.writelines( "/home/frederik/pcl/brodatz/textures/" + "brodatz_" + big[:-4] + '.jpeg' + '\n')
    print large_image.shape
    
    print "write image to list"


print "finished"