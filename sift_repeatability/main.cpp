//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>     // std::string, std::stof


#include <fstream>

#define _USE_MATH_DEFINES

#include <math.h>


#include <covis/covis.h>
using namespace covis;

//#include "gaborMatcher.hpp"
//#include "transform.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


#include "opencv2/xfeatures2d.hpp"

int main (int argc, char** argv)
{

//    float k = std::sqrt(2);
//    float p = 0.5;
//    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
//    int start_scale = 0;
//    int end_scale = 6;
//    int rows = end_scale - start_scale;

//    filter::GaborJet matcher(45, 0.20, sigma, 12, start_scale, end_scale, k);

//    transform plane_transform;

    /** Step 1:    **/

    cv::Mat image = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/img1.ppm");
    cv::Mat depth = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/depth1.pgm", -1);
    cv::Mat mask = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/mask.pgm", -1);

    cv::imshow("depth image", depth);
    cv::imshow("color image", image);
    cv::imshow("mask image", mask);

//    cv::waitKey();

    /** Step 2:    **/


//    cv::Mat transformed_image = plane_transform.transform_image(image, depth, image.cols/2, image.rows/2);

//    cv::imshow("transformed", transformed_image);

//    cv::waitKey();

    /** Step 3:    **/

    cv::Mat gray_image;

    cv::cvtColor(image, gray_image, 0 );

    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create(300);
    std::vector<cv::KeyPoint> keypoints_1;
    f2d->detect( gray_image, keypoints_1 , mask);

    for (int i=0; i<keypoints_1.size(); i++){
      cv::KeyPoint kp = keypoints_1[i];
      cv::circle(image, kp.pt, cvRound(kp.size*0.25), cv::Scalar(255,255,0), 1, 8, 0);
    }
    cv::imshow("mywindow", image);
//    cv::waitKey();


    /** Step 4:    **/


    cv::Mat M(3,3, CV_32FC1);

    std::string file_line;
    std::ifstream file ("/home/frederik/pcl/create_pcl/frosties_vpangle/H1to2p");

    using namespace boost::algorithm;

    int j = 0;
    if (file.is_open())
    {
      while ( std::getline (file, file_line) )
      {

          std::vector<std::string> tokens;

          split(tokens, file_line, is_any_of("	")); // here it is

          for(int i = 0; i < 3; i++)//(std::string s: tokens)
          {
//                std::cout << '"' << atof( tokens[i].c_str() ) << '"' << '\n';
                double trouble = atof( tokens[i].c_str() );
                M.at<float>(j, i) = trouble;

          }

          j++;

      }

    }


    std::vector<cv::Point2f> worldPoints;
    std::vector<cv::Point2f> cameraPoints;

    for (int i=0; i<keypoints_1.size(); i++){
      cv::KeyPoint kp = keypoints_1[i];
      worldPoints.push_back( kp.pt );
    }

    std::cout << M <<  std::endl;
    cv::perspectiveTransform( worldPoints, cameraPoints, M);

    /** Step 5:    **/

    cv::Mat image2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/img2.ppm");
    cv::Mat depth2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/depth2.pgm", -1);

    /** Step 5-a:    **/


    /** Step 5-b:    **/

    cv::cvtColor(image2, gray_image, 0 );

    f2d = cv::xfeatures2d::SIFT::create();
    std::vector<cv::KeyPoint> keypoints_2;
    f2d->detect( gray_image, keypoints_2);

    for (int i=0; i<keypoints_2.size(); i++){
      cv::KeyPoint kp = keypoints_2[i];
      cv::circle(image2, kp.pt, cvRound(kp.size*0.25), cv::Scalar(255,255,0), 1, 8, 0);
    }


    /** Step 5-c:    **/

    for (int i=0; i<cameraPoints.size(); i++){
      cv::KeyPoint kp = keypoints_1[i];
      cv::circle(image2, cameraPoints[i],  cvRound(kp.size*0.25), cv::Scalar(0,0,255), 1, 8, 0);
    }

    cv::imshow("mywindow2", image2);
    /** Step 5-d:  find distance between points  **/

    int numberUnder15 = 0;
    int numberUnder30 = 0;
    int numberUnder50 = 0;

    for( int index_1 = 0; index_1 < cameraPoints.size(); index_1++)
    {
        float bestMatch = 100000;
        float bestIndex = 0;

        for( int index_2 = 0; index_2 < keypoints_2.size(); index_2++)
        {

            float distance = std::sqrt( (cameraPoints[index_1].x - keypoints_2[index_2].pt.x) * (cameraPoints[index_1].x - keypoints_2[index_2].pt.x) + (cameraPoints[index_1].y - keypoints_2[index_2].pt.y) * (cameraPoints[index_1].y - keypoints_2[index_2].pt.y) );

            if( bestMatch > distance)
            {
                bestMatch = distance;
                bestIndex = index_2;

            }


        }


        std::cout << "Distance: " << bestMatch << std::endl;

        if(bestMatch < 1.5)
            numberUnder15++;
        if(bestMatch < 1.5 * keypoints_2[bestIndex].size)
            numberUnder30++;
        if(bestMatch < 5)
            numberUnder50++;

        }

    std::cout << numberUnder15 << std::endl;
    std::cout << numberUnder30 << std::endl;
    std::cout << numberUnder50 << std::endl;


//        std::cout << keypoints_1[index_1].pt.x << " , " << keypoints_1[index_1].pt.y << std::endl;
//        std::cout << keypoints_2[bestIndex].pt.x << " , " << keypoints_2[bestIndex].pt.y << std::endl;

//        std::cout << "Distance: " << distance << std::endl;
//        std::cout << std::endl;


    cv::waitKey(0);

    return 0;

}
