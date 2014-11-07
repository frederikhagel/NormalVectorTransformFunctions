import cv2 
import numpy as np 
 
#srcTri = cv2.Point2f[3];
#Point2f dstTri[3];
#
#Mat rot_mat( 2, 3, CV_32FC1 );
#warp_mat( 2, 3, CV_32FC1 );
#Mat src, warp_dst, warp_rotate_dst;

# Load the image

src = cv2.imread( "test_image.png", 1 );

# Set the dst image the same type and size as src
#warp_dst = np.zeros( src.rows, src.cols, src.type() );

# Set your 3 points to calculate the  Affine Transform

srcTri = [0,0,0]
dstTri = [0,0,0]

cols = src.shape[1]
rows = src.shape[0]

srcTri[0] = ( 0,0 );
srcTri[1] = ( src.shape[1] - 1, 0 );
srcTri[2] = ( 0, src.shape[0] - 1 );

dstTri[0] = ( cols*0.0, rows*0.33 );
dstTri[1] = ( cols*0.85, rows*0.25 );
dstTri[2] = ( cols*0.15, rows*0.7 );

print type(src)

srcTri = np.array(srcTri)
dstTri = np.array(dstTri)

print srcTri

#Get the Affine Transform
warp_mat = cv2.getAffineTransform( srcTri, dstTri );

print warp_mat

#/// Apply the Affine Transform just found to the src image
warp_dst = cv2.warpAffine( src,  warp_mat);



#/** Rotating the image after Warp */

#/// Compute a rotation matrix with respect to the center of the image
center = cv2.Point( warp_dst.cols/2, warp_dst.rows/2 );
angle = -50.0
scale = 0.6

#/// Get the rotation matrix with the specifications above
rot_mat = cv2.getRotationMatrix2D( center, angle, scale );

#/// Rotate the warped image
cv2.warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

#/// Show what you got
namedWindow( source_window, CV_WINDOW_AUTOSIZE );
imshow( source_window, src );

namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
imshow( warp_window, warp_dst );

namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
imshow( warp_rotate_window, warp_rotate_dst );

#/// Wait until user exits the program
waitKey(0);
