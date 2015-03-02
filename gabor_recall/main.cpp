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
#include "gabor_jet.h"


#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


//#include "gaborTransform.hpp"
#include "transform.hpp"

#include "opencv2/xfeatures2d.hpp"


std::vector< std::vector< float> > getPixelJet( cv::Mat jet, int rows){

    std::vector< std::vector<float> > response;

    std::vector<cv::Mat> jet_vector( jet.channels() );

    cv::split( jet, jet_vector );

    int rotations = jet.channels() / rows;

    for(int i=0; i < rows; i++){
        std::vector<float> theta_result;
        for(int j=0; j < rotations ; j++){
//                cv::Mat wavelet_blured;
//                cv::blur(jet_vector[i * rotations + j], wavelet_blured,cv::Size(13,13));

            theta_result.push_back( jet_vector[i * rotations + j].at<float>( 0, 0 )  );
        }
        response.push_back( theta_result );

    }

    return response;
}


inline float compareSinglePixel(std::vector<std::vector<float> > pixelJet1, std::vector<std::vector<float> > pixelJet2 ){
    float dot = 0;
    float norm1 = 0;
    float norm2 = 0;

    float best_rotation_response = 0;

    int rotations = pixelJet1[0].size();

        for(int i=0; (unsigned)i < pixelJet1.size(); i++){
            for(int j=0; (unsigned)j < pixelJet1[i].size(); j++){
                dot += pixelJet1[i][j] *  pixelJet2[i][j];
                norm1 += pixelJet1[i][j] * pixelJet1[i][j];
                norm2 += pixelJet2[i][j] * pixelJet2[i][j];
            }
        }

        norm1 = sqrt(norm1);
        norm2 = sqrt(norm2);

        dot /= norm1 * norm2;
        if(dot > best_rotation_response){
            best_rotation_response = dot;
        }


    return best_rotation_response;
}



inline float compareSinglePixelShift(std::vector<std::vector<float> > pixelJet1, std::vector<std::vector<float> > pixelJet2 ){
    float dot = 0;
    float norm1 = 0;
    float norm2 = 0;

    float best_rotation_response = 0;

    int rotations = pixelJet1[0].size();

    for(int shift = 0; (unsigned)shift < rotations; shift++ ){
        for(int i=0; (unsigned)i < pixelJet1.size(); i++){
            for(int j=0; (unsigned)j < pixelJet1[i].size(); j++){
                dot += pixelJet1[i][j] *  pixelJet2[i][(j + shift)%pixelJet2[i].size()];
                norm1 += pixelJet1[i][j] * pixelJet1[i][j];
                norm2 += pixelJet2[i][(j + shift)%pixelJet2[i].size()] * pixelJet2[i][(j + shift)%pixelJet2[i].size()];
            }
        }

        norm1 = sqrt(norm1);
        norm2 = sqrt(norm2);

        dot /= norm1 * norm2;
        if(dot > best_rotation_response){
            best_rotation_response = dot;
        }

    }

    return best_rotation_response;
}




int main (int argc, char** argv)
{

    float k = 2; // std::sqrt(2);
    float p = 0.5;
    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
    int start_scale = 0;
    int end_scale = 3;
    int rows = end_scale - start_scale;

    GaborJet matcher(20, 0.20, sigma, 12, start_scale, end_scale, k);

    transform plane_transform;

    /** Step 1:    **/

    cv::Mat image = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/img1.ppm");
    cv::Mat depth = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/depth1.pgm", -1);
    cv::Mat mask = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/mask.pgm", -1);


    cv::imshow("depth image", depth);
    cv::imshow("color image", image);
    cv::imshow("mask image", mask);

//    cv::waitKey();


    /** Step 2:    **/

    cv::Mat gray_image;

    cv::cvtColor(image, gray_image, 0 );

    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create(300);
    std::vector<cv::KeyPoint> keypoints_1;
    f2d->detect( gray_image, keypoints_1 , mask);

    /** Step 3:    **/

    std::vector<std::vector< std::vector< float> > > gaborJets;
    std::vector<int> xList;
    std::vector<int> yList;

    for (int i=0; i<keypoints_1.size(); i++){
        cv::KeyPoint kp = keypoints_1[i];
        int x = kp.pt.x;
        int y = kp.pt.y;
        std::cout << depth.at<int16_t>(x,y) << " " << x << " " << y << std::endl;

//        if( depth.at<int16_t>(x,y) > 100 and depth.at<int16_t>(x,y) < 2000)
//        {
            xList.push_back( x );
            yList.push_back( y );

//        }

    }
    std::vector<cv::Mat> transformed_images = plane_transform.transform_image(image, depth, xList, yList);
    std::cout << "came through" << std::endl;
//              cv::Mat onePixelSourceROI(transformed_image, cv::Rect( cv::Point(x,y), cv::Size(1, 1) ));

//

    /** Step 5-a:    **/

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


    /** Step 4:    **/

    for (int i=0; i<transformed_images.size(); i++){

        cv::Mat gaborResponse = matcher.filter(transformed_images[i], xList[i], yList[i]  );
//        std::cout << gaborResponse << std::endl;
        gaborJets.push_back( getPixelJet( gaborResponse, rows ) );
//        cv::circle(transformed_images[i], cv::Point( xList[i], yList[i] )  , cvRound(10), cv::Scalar(255,255,0), -1, 8, 0);
//        cv::imshow("transformed", transformed_images[i]);
//        cv::waitKey(20);

     }


    /** Step 5:    **/

    cv::Mat image2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/img2.ppm");
    cv::Mat depth2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/depth2.pgm", -1);

    /** Step 5-b:    **/

    std::vector<std::vector< std::vector< float> > > gaborJets2;
    std::vector<int> xList2;
    std::vector<int> yList2;

    for (int i=0; i< cameraPoints.size(); i++){
        cv::Point2f kp = cameraPoints[i];
        int x = kp.x;
        int y = kp.y;
//        std::cout << depth2.at<int16_t>(x,y) << " " << x << " " << y << std::endl;

//        if( depth.at<int16_t>(x,y) > 100 and depth.at<int16_t>(x,y) < 2000)
//        {
            xList2.push_back( x );
            yList2.push_back( y );

//        }

    }
    std::vector<cv::Mat> transformed_images2 = plane_transform.transform_image(image2, depth2, xList2, yList2);
    std::cout << "came through" << std::endl;
//              cv::Mat onePixelSourceROI(transformed_image, cv::Rect( cv::Point(x,y), cv::Size(1, 1) ));

//
    for (int i=0; i<transformed_images2.size(); i++){

        cv::Mat gaborResponse = matcher.filter(transformed_images2[i], xList2[i], yList2[i]  );
//        std::cout << gaborResponse << std::endl;
        gaborJets2.push_back( getPixelJet( gaborResponse, rows ) );
//        cv::circle(transformed_images2[i], cv::Point( xList2[i], yList2[i] )  , cvRound(10), cv::Scalar(255,255,0), -1, 8, 0);
//        cv::imshow("transformed", transformed_images2[i]);
//        cv::waitKey(20);

    }



    /** Step 5-c:    **/


    int numberUnder15 = 0;
    int numberUnder30 = 0;
    int numberUnder50 = 0;

    for( int index_1 = 0; index_1 < gaborJets.size(); index_1++)
    {
        float bestMatch = 0;
        float bestIndex = 0;

        for( int index_2 = 0; index_2 < gaborJets2.size(); index_2++)
        {
            float match_found = compareSinglePixelShift( gaborJets[index_1], gaborJets2[index_2] );
            if( match_found > bestMatch)
            {
                bestMatch = match_found;
                bestIndex = index_2;

            }


        }

        if( bestIndex == index_1 ){
            numberUnder15++;
        }
    }

////        std::cout << keypoints_1[index_1].pt.x << " , " << keypoints_1[index_1].pt.y << std::endl;
////        std::cout << keypoints_2[bestIndex].pt.x << " , " << keypoints_2[bestIndex].pt.y << std::endl;
//        float distance = std::sqrt( (keypoints_1[index_1].pt.x - keypoints_2[bestIndex].pt.x) * (keypoints_1[index_1].pt.x - keypoints_2[bestIndex].pt.x) + (keypoints_1[index_1].pt.y - keypoints_2[bestIndex].pt.y) * (keypoints_1[index_1].pt.y - keypoints_2[bestIndex].pt.y) );

////        std::cout << "Distance: " << distance << std::endl;
////        std::cout << std::endl;

//        if(distance < 15)
//            numberUnder15++;
//        if(distance < 30)
//            numberUnder30++;
//        if(distance < 50)
//            numberUnder50++;


//    }

    std::cout <<  gaborJets.size() << std::endl;
    std::cout << numberUnder15 << std::endl;
//    std::cout << numberUnder30 << std::endl;
//    std::cout << numberUnder50 << std::endl;

//    cv::waitKey(0);

//    /** Step 5-d:    **/


    return 0;

}
