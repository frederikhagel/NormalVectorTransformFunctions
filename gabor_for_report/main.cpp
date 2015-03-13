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
#include <boost/lexical_cast.hpp>

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

    float k = 2;
    float p = 0.5;
    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
    int start_scale = 0;
    int end_scale = 5;
    int rows = end_scale - start_scale;

    GaborJet matcher(30, 0.20, sigma, 12, start_scale, end_scale, k);

    transform plane_transform;

    /** Step 1:    **/

    std::ofstream outfile ("test_results.txt", std::ios::out);

    std::string file_name = "frosties_vpangle";
//  file_name = "worldmap_vpangle45";


    cv::Mat image = cv::imread("simple_pattern_no_rotation.ppm");
//    cv::Mat depth = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/depth1.pgm", -1);
    cv::Mat mask = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/mask.pgm", -1);


//    cv::imshow("depth image", depth);
    cv::imshow("color image", image);
    cv::imshow("mask image", mask);


    /** Step 2:    **/

    cv::Mat gray_image;

    cv::cvtColor(image, gray_image, 0 );

    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create(0);
//    cv::Ptr<cv::Feature2D> f2d = cv::ORB::create(300);
    std::vector<cv::KeyPoint> keypoints_1;
    f2d->detect( gray_image, keypoints_1 , mask);

    /** Step 5:    **/

//    int image_number = 8;

    for(int image_number = 2; image_number < 3; image_number++){

        std::string jaw = boost::lexical_cast<std::string>(image_number);

        std::string image_name = "simple_pattern_weird_angle.ppm";
//        std::string image_name = "simple_pattern_weird0_angle.ppm";
        cv::Mat image2 = cv::imread(image_name);
//        cv::Mat depth2 = cv::imread("/home/frederik/pcl/create_pcl/" + file_name + "/depth" + jaw + ".pgm", -1);


        cv::waitKey(50);


        /** Step 5-a:    **/


        /** Step 3:    **/

        std::vector<std::vector< std::vector< float> > > gaborJets;
        std::vector<int> xList;
        std::vector<int> yList;

        std::vector<int> xList2;
        std::vector<int> yList2;


        xList.push_back( image.cols/2 );
        yList.push_back( image.rows/2 );
        xList2.push_back( image.cols/2 );
        yList2.push_back( image.rows/2 );

//        std::cout  << image.cols/2 << " " << image.rows/2 << " " << depth.at<int16_t>( image.rows/2, image.cols/2)  <<  std::endl;
//        std::cout  << image.cols/2 << " " << image.rows/2 <<  " " <<  depth2.at<int16_t>(image.cols/2, image.rows/2)  << std::endl << std::endl;


//        xList.push_back( image.cols/2  - 20);
//        yList.push_back( image.rows/2 );
//        xList2.push_back( image.cols/2 - 20);
//        yList2.push_back( image.rows/2 );

//        std::cout  << image.cols/2  + 20 << " " << image.rows/2 << " " << depth.at<int16_t>( image.rows/2, image.cols/2  - 20)  <<  std::endl;
//        std::cout  << image.cols/2 + 20 << " " << image.rows/2 <<  " " <<  depth2.at<int16_t>(image.cols/2, image.rows/2  - 20)  << std::endl << std::endl;

//        xList.push_back( image.cols/2 );
//        yList.push_back( image.rows/2 + 10);
//        xList2.push_back( image.cols/2 );
//        yList2.push_back( image.rows/2 + 10);

//        std::cout  << image.cols/2 << " " << image.rows/2 + 10 << " " << depth.at<int16_t>( image.rows/2 + 10, image.cols/2 )  <<  std::endl;
//        std::cout  << image.cols/2 << " " << image.rows/2 <<  " " <<  depth2.at<int16_t>(image.cols/2, image.rows/2  + 10)  << std::endl << std::endl;


//        xList.push_back( 0 );
//        yList.push_back( 0 );
//        xList2.push_back( 0 );
//        yList2.push_back( 0 );

//        std::cout  << 0 << " " << 0 << " " << depth.at<int16_t>( 0, 0 )  <<  std::endl;
//        std::cout  << 0 << " " << 0 <<  " " <<  depth2.at<int16_t>(0, 0)  << std::endl << std::endl;


    //


        /** Step 4:    **/

        for (int i=0; i<xList.size(); i++){

            cv::Mat gaborResponse = matcher.filter(image, xList[i], yList[i] );
    //        std::cout << gaborResponse << std::endl;
            gaborJets.push_back( getPixelJet( gaborResponse, rows ) );
    //        cv::circle(transformed_images[i], cv::Point( xList[i], yList[i] )  , cvRound(10), cv::Scalar(255,255,0), -1, 8, 0);
    //        cv::imshow("transformed", transformed_images[i]);
    //        cv::waitKey(20);

         }



        /** Step 5-b:    **/

        std::vector<std::vector< std::vector< float> > > gaborJets2;
    //              cv::Mat onePixelSourceROI(transformed_image, cv::Rect( cv::Point(x,y), cv::Size(1, 1) ));

    //
        for (int i=0; i < xList2.size(); i++){

            cv::Mat gaborResponse = matcher.filter(image2, xList2[i], yList2[i] );
    //        std::cout << gaborResponse << std::endl;
            gaborJets2.push_back( getPixelJet( gaborResponse, rows ) );

    //        std::cout << xList[i] << " " << yList[i] << std::endl;
//            cv::circle(transformed_images2[i], cv::Point( image.cols/2, image.rows/2 )  , cvRound(10), cv::Scalar(255,255,0), -1, 8, 0);
//            cv::imshow("transformed2", transformed_images2[i]);
//            cv::waitKey(20);

//            cv::circle(transformed_images[i], cv::Point(  image.cols/2, image.rows/2 )  , cvRound(10), cv::Scalar(255,255,0), -1, 8, 0);
//            cv::imshow("transformed", transformed_images[i]);
//            cv::waitKey(0);

        }





        /** Step 5-c:    **/

        int correct = 0;

        for( int index_1 = 0; index_1 < gaborJets.size(); index_1++)
        {
            float bestMatch = 0;
            float bestIndex = 0;


            cv::Mat test( rows, 12 ,cv::DataType<float>::type);


            for(int i=0; (unsigned)i < gaborJets[index_1].size(); i++){
                for(int j=0; (unsigned)j < gaborJets[index_1][i].size(); j++)
                {

                    std::cout << gaborJets[index_1][i][j] << " ";
                }

                std::cout << std::endl;
            }
            std::cout << std::endl;




            for(int i=0; (unsigned)i < gaborJets2[index_1].size(); i++){
                for(int j=0; (unsigned)j < gaborJets2[index_1][i].size(); j++)
                {
                    std::cout << gaborJets2[index_1][i][j] << " ";
                    test.at<float>(i,j) = gaborJets2[index_1][i][j]/6000;
                }

                std::cout << std::endl;
            }


            cv::pyrUp(test, test);
            cv::pyrUp(test, test);
            cv::pyrUp(test, test);

            cv::imshow(" H ", test);
            cv::waitKey(0);


            for( int index_2 = 0; index_2 < gaborJets2.size(); index_2++)
            {


                float match_found = compareSinglePixelShift( gaborJets[index_1], gaborJets2[index_2] );
                if( match_found > bestMatch)
                {
                    bestMatch = match_found;
                    bestIndex = index_2;

                }


            }

            if( bestIndex == index_1 )
            {   correct++;
                outfile << 1 << " " << bestMatch << std::endl;
                /** add the result positive **/
            }
            else
                outfile << 0 << " " << bestMatch << std::endl;
                /** add the result negative **/
        }

        std::cout << "number of corect matches " << correct << " all in all " << gaborJets.size() << std::endl;

    }
        return 0;

}
