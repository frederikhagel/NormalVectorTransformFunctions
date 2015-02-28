# -*- coding: utf-8 -*-
"""
Created on Fri Oct 24 19:06:24 2014

@author: frederik
"""

import cv2
import numpy as np

img = cv2.imread( "universe.jpeg");

img = cv2.imread( "test_image_perspective.png")

distance = -1



point = (-0.364411,0.499912,-0.342481)
cv2.circle(img, (  int((-480)* point[0]/(point[2] + distance) + 320),  int( (480) * point[1]/(point[2] + distance) + 240) ) , 2, (255,0,255), 3 )

point = (-0.364411,-0.500088,-0.342223)
cv2.circle(img, (  int((-480)* point[0]/(point[2] + distance) + 320),  int( (480) * point[1]/(point[2] + distance) + 240) ) , 2, (255,0,255), 3 )

point = (0.258514,-0.499838, 0.428174)
cv2.circle(img, (  int((-480)* point[0]/(point[2] + distance) + 320),  int( (480) * point[1]/(point[2] + distance) + 240) ) , 2, (0,0,255), 3 )

point = (0.364411,-0.499912, 0.342481)
cv2.circle(img, (  int((-480)* point[0]/(point[2] + distance) + 320),  int( (480) * point[1]/(point[2] + distance) + 240) ) , 2, (0,0,255), 3 )

#point = (0,0,0)
#cv2.circle(img, (  int((-480)* point[0]/(point[2] + distance) + 320),  int( (480) * point[1]/(point[2] + distance) + 240) ) , 2, (0,255,0), 3 )



cv2.imshow("img", img)
cv2.waitKey(0)


start_point_3D = [ (1,1,0) , (1,-1,0) , (-1,-1,0) , (-1,1,0) ]
end_point_3D = [ (1,0.707391,-0.706822) , (0.999999,-0.707391,0.706823) , (-1,-0.707391,0.706822) , (-0.999999,0.707391,-0.706823) ]


start_point_3D = [ (1,1,0) , (1,-1,0) , (-1,-1,0) , (-1,1,0) ]
end_point_3D = [ (0.517351,1,-0.855773) , (0.516703,-1,-0.856165) , (-0.517351,-1,0.855773) , (-0.516703,1,0.856165) ]

end_point_3D = [ (0.728822,1.00018,0.684445) , (0.728822,-0.999823,0.684961) , (-0.728822,-1.00018,-0.684445) , (-0.728822,0.999823,-0.684961) ]





# here we have the weak perspective method
start_point_2D = []
for point in start_point_3D:
    start_point_2D.append ( ( point[0], point[1] ) )
    
end_point_2D = []
for point in end_point_3D:
    end_point_2D.append ( ( point[0], point[1] ) )
    
end_point_2D = np.array(end_point_2D, np.float32)    
start_point_2D = np.array(start_point_2D, np.float32)    
        
print end_point_2D

M = cv2.getPerspectiveTransform(end_point_2D,start_point_2D)
print "M"
print M
print "M"
dst = cv2.warpPerspective(img, M , (img.shape[1]*2,img.shape[0]*2))

cv2.imshow("img1", dst)

cv2.waitKey(0)








start_point_3D = [ (480,0,0) , (480, 480,0) , (0,480,0) , (0,0,0) ]
#end_point_3D = [ (0.517351,1,-0.855773) , (0.516703,-1,-0.856165) , (-0.517351,-1,0.855773) , (-0.516703,1,0.856165) ]
#end_point_3D = [ (1,0.707391,-0.706822) , (0.999999,-0.707391,0.706823) , (-1,-0.707391,0.706822) , (-0.999999,0.707391,-0.706823) ]

start_point_3D = [ (1,1,0) , (1,-1,0) , (-1,-1,0) , (-1,1,0) ]






# here we have the projection perspective method

distance = 1


start_point_2D = []
for point in start_point_3D:
#    start_point_2D.append ( ( point[0], point[1] ) )
     start_point_2D.append ( (  ((-480)* point[0]/(point[2] + distance) + 320),  (480) * point[1]/(point[2] + distance) + 240)  )

print 
print "start_point_2D"
print start_point_2D
    
end_point_2D = [] 
for point in end_point_3D:
#    end_point_2D.append ( ( point[0]/(point[2]), point[1]/(point[2] ) )  )
    end_point_2D.append ( (  ((-480)* point[0]/(point[2] + distance) + 320),  (480) * point[1]/(point[2] + 1) + 240)  )

#int x_pos = 320 -  point.x/point.z * 480;
#int y_pos = 240 +  point.y/point.z * 480;
    
    
print img.shape[1]
    
end_point_2D = np.array(end_point_2D, np.float32)    
start_point_2D = np.array(start_point_2D, np.float32)    
     
print
print end_point_2D

M = cv2.getPerspectiveTransform(end_point_2D,start_point_2D)

#M = cv2.getPerspectiveTransform(start_point_2D, end_point_2D)
 
print "real M"
print M
print "real M"

dst = cv2.warpPerspective(img, M , (img.shape[1],img.shape[0]))

cv2.imshow("img2", dst)
cv2.imwrite("perspective_result.jpeg", dst)


cv2.waitKey(0)