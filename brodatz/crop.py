# -*- coding: utf-8 -*-
"""
Created on Tue Nov  4 12:15:26 2014

@author: frederik
"""

import cv2

name = "1.3.05"

img = cv2.imread(name + ".tiff")
img2 = cv2.imread("universe1.jpeg")

x  = 15
y = 15
h = 1000
w = 1000

print img.shape
print img2.shape
print img.dtype
print img2.dtype


crop = img[y:y+h,x:x+w]

crop[0,0] = [255, 0, 0]

print crop.shape

cv2.imshow("texture", img )
cv2.imshow("crop", crop )
cv2.waitKey(0)
cv2.imwrite(name + '.png',crop)

cv2.imwrite("universe.jpeg", crop, (cv2.IMWRITE_JPEG_QUALITY, 100))