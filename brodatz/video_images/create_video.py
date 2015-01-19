# -*- coding: utf-8 -*-
"""
Created on Sun Jan 18 18:21:37 2015

@author: frederik
"""

import cv2
import glob
image_list = glob.glob('*.jpeg')
image_list.sort()

#print image_list
transformed_images = image_list[:len(image_list)/2]
untransformed_images = image_list[len(image_list)/2:]

#print len(transformed_images)
#print len(untransformed_images)

height , width , layers =  (480, 1280, 3)

#video = cv2.VideoWriter('compensation.avi',-1,1,)
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc, 20.0, (width,height))

list_of_angles = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80]

for enumaration, image_name in enumerate(untransformed_images):
    untransformed_image = cv2.imread(image_name)
    transformed_image = cv2.imread(transformed_images[enumaration])
#    cv2.imshow("untransformed_image", untransformed_image)
#    cv2.imshow("transformed_image", transformed_image)
    combined_image = cv2.hconcat( [untransformed_image, transformed_image] )
    cv2.putText(combined_image, "Rotation " + str(list_of_angles[enumaration]) + "", ( 30, 480-20  ), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)
    cv2.imshow("compensation", combined_image)
    for i in range(15):
        out.write(combined_image)
    cv2.waitKey(5)

cv2.destroyAllWindows()
out.release()
print "Finished"