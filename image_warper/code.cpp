#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h> 

using namespace cv;
using namespace std;

#include <limits.h>

/// Global variables
char* source_window = "Source image";
char* warp_window = "Warp";
char* warp_rotate_window = "Warp + Rotate";

/** @function main */
 int main( int argc, char** argv )
 {

   if (sizeof(float) * CHAR_BIT != 32)
	cout << "shit" << endl;

   Point2f srcTri[3];
   Point2f dstTri[3];

   Mat rot_mat( 2, 3, CV_32FC1 );
   Mat warp_mat( 2, 3, CV_32FC1 );
   Mat src, warp_dst, warp_rotate_dst;



   /// Load the image
   src = imread( argv[1], 1 );

   /// Set the dst image the same type and size as src
   warp_dst = Mat::zeros( src.rows*5, src.cols*5, src.type() );


   /// Set your 3 points to calculate the  Affine Transform
   srcTri[0] = Point2f( 0,0 );
   srcTri[1] = Point2f( src.cols - 1, 0 );
   srcTri[2] = Point2f( 0, src.rows - 1 );

   dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
   dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
   dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );


   dstTri[0] = Point2f( 0,0 );
   dstTri[1] = Point2f( src.cols/2, src.rows/2 );
   dstTri[2] = Point2f( src.cols - 1, 0);

   srcTri[0] = Point2f( 0, src.rows* 0.20 );
   srcTri[1] = Point2f( src.cols/2, src.rows/2 );
   srcTri[2] = Point2f( src.cols - 1, src.rows*0.20 );


   /// Get the Affine Transform
   warp_mat = getAffineTransform( srcTri, dstTri );

   //warp_mat.at<Point2f>(0,1) = 2;

/*

   double a = -0.607514;
   double b = 0.152352;

   double alpha = atan(-b/a);
   double s = sqrt( pow(b,2) + pow(a,2) );

   cout << alpha << endl;
   cout << s << endl;

   cout <<  cos(alpha) << endl;

   warp_mat.at<float>(0,0) = s * cos(alpha);
   warp_mat.at<float>(0,1) = s * sin(alpha);
   warp_mat.at<float>(0,2) = 300;
   warp_mat.at<float>(1,0) = s * (-sin(alpha));
   warp_mat.at<float>(1,1) = s * cos(alpha);
   warp_mat.at<float>(1,2) = 300;

*/
   //warp_mat[0][0] = 2;

   cout << warp_mat << endl;

   /// Apply the Affine Transform just found to the src image
   warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

   /** Rotating the image after Warp */

   /// Compute a rotation matrix with respect to the center of the image
   Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
   double angle = -50.0;
   double scale = 0.6;

   /// Get the rotation matrix with the specifications above
   rot_mat = getRotationMatrix2D( center, angle, scale );

   /// Rotate the warped image
   warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

   /// Show what you got
   namedWindow( source_window );
   imshow( source_window, src );

   namedWindow( warp_window);
   imshow( warp_window, warp_dst );

   //namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
   //imshow( warp_rotate_window, warp_rotate_dst );

   /// Wait until user exits the program
   waitKey(0);

   return 0;
  }
