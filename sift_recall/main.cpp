//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>     // std::string, std::stof

#include <fstream>

#define _USE_MATH_DEFINES

#include <math.h>


//#include <covis/covis.h>
//using namespace covis;


#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

//#include "gaborTransform.hpp"

#include "opencv2/xfeatures2d.hpp"

int main (int argc, char** argv)
{

    /** Step 1:    **/

    std::ofstream outfile ("test_results.txt", std::ios::out);

    std::string file_name = "frosties_vpangle";
//  file_name = "worldmap_vpangle45";


    cv::Mat image = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/img1.ppm");
    cv::Mat depth = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/depth1.pgm", -1);
    cv::Mat mask = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/mask.pgm", -1);

    cv::imshow("depth image", depth);
    cv::imshow("color image", image);
    cv::imshow("mask image", mask);

    /** Step 2:    **/

    cv::Mat gray_image;

    cv::cvtColor(image, gray_image, 0 );

    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create(500);
//    cv::Ptr<cv::Feature2D> f2d = cv::ORB::create(300);
    std::vector<cv::KeyPoint> keypoints_1;
    f2d->detect( gray_image, keypoints_1 , mask);

    /** Step 5:    **/

//    int image_number = 8;

    for(int image_number = 8; image_number < 9; image_number++){


      std::string jaw = boost::lexical_cast<std::string>(image_number);
        /** Step 5-a:    **/

        cv::Mat M(3,3, CV_32FC1);

        std::string file_line;
        std::string homography_name = "/home/frederik/pcl/create_pcl/" + file_name + "/H1to" + jaw + "p";

        std::ifstream file (homography_name.c_str());

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

        /**       *********************************************            **/


        std::string image_name = "/home/frederik/pcl/create_pcl/" + file_name + "/img" + jaw + ".ppm";
        cv::Mat image2 = cv::imread(image_name);
        cv::Mat depth2 = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/depth" + jaw + ".pgm", -1);

        cv::waitKey(50);

        cv::Mat gray_image2;

        cv::cvtColor(image2, gray_image2, 0 );


        std::vector<cv::Point2f> worldPoints;
        std::vector<cv::Point2f> cameraPoints;

        for (int i=0; i<keypoints_1.size(); i++){
          cv::KeyPoint kp = keypoints_1[i];
          worldPoints.push_back( kp.pt );
        }

        cv::perspectiveTransform( worldPoints, cameraPoints, M);

        std::vector<cv::KeyPoint> keypoints_2;

        for( int key_index = 0; key_index < keypoints_1.size(); key_index++ )
        {
            cv::KeyPoint key = keypoints_1[key_index];
            key.pt = cameraPoints[key_index];
            keypoints_2.push_back( key );

        }



//        f2d->detect( gray_image, keypoints_2 , mask);





//        /** Step 5-a:    **/

        cv::Mat descriptors_1, descriptors_2;
        f2d->compute( gray_image, keypoints_1, descriptors_1 );

        f2d->compute( gray_image2, keypoints_2, descriptors_2 );

        //-- Step 3: Matching descriptor vectors using BFMatcher :
        cv::BFMatcher matcher;
        std::vector< cv::DMatch > matches;
        matcher.match( descriptors_1, descriptors_2, matches );

        int correct = 0;

        for( int match_index = 0; match_index < matches.size(); match_index ++)
        {
            std::cout << matches[match_index].queryIdx << " , " << matches[match_index].trainIdx << std::endl;
            if( matches[match_index].queryIdx == matches[match_index].trainIdx )
                {   correct++;
                    outfile << 1 << " " << matches[match_index].distance << std::endl;
                }
                else
                    outfile << 0 << " " << matches[match_index].distance << std::endl;
        }

        std::cout << "correct: " << correct << " vs " << keypoints_1.size() << std::endl;


//        /** Step 5-c:    **/

//        int correct = 0;

//        for( int index_1 = 0; index_1 < gaborJets.size(); index_1++)
//        {
//            float bestMatch = 0;
//            float bestIndex = 0;

//            for(int i=0; (unsigned)i < gaborJets[index_1].size(); i++){
//                for(int j=0; (unsigned)j < gaborJets[index_1][i].size(); j++)
//                    std::cout << gaborJets[index_1][i][j] << " ";
//                std::cout << std::endl;
//            }
//            std::cout << std::endl;

//            for( int index_2 = 0; index_2 < gaborJets2.size(); index_2++)
//            {

//                float match_found = compareSinglePixelShift( gaborJets[index_1], gaborJets2[index_2] );
//                if( match_found > bestMatch)
//                {
//                    bestMatch = match_found;
//                    bestIndex = index_2;

//                }


//            }

//            if( bestIndex == index_1 )
//            {   correct++;
//                outfile << 1 << " " << bestMatch << std::endl;
//                /** add the result positive **/
//            }
//            else
//                outfile << 0 << " " << bestMatch << std::endl;
//                /** add the result negative **/
//        }

//        std::cout << "number of corect matches " << correct << " all in all " << gaborJets.size() << std::endl;

    }
        return 0;

}
