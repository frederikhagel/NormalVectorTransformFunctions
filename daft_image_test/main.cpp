//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>

#include <fstream>

#define _USE_MATH_DEFINES

#include <math.h>


#include <covis/covis.h>
using namespace covis;

//#include "gaborMatcher.hpp"
#include "transform.hpp"

#include "opencv2/xfeatures2d.hpp"


inline std::vector< std::vector< std::vector< float> > > getPixelJet( cv::Mat jet, int rows, std::vector<cv::KeyPoint> keypoints_1){

    std::vector< std::vector< std::vector<float> > > response;



    std::vector<cv::Mat> jet_vector( jet.channels() );

    cv::split( jet, jet_vector );

    int rotations = jet.channels() / rows;

    for (int k=0; k<keypoints_1.size(); k++){
        cv::KeyPoint kp = keypoints_1[k];

        int x_used = kp.pt.x;
        int y_used = kp.pt.y;

        std::vector< std::vector<float> > pixelResponse;

        for(int i=0; i < rows; i++){
            std::vector<float> theta_result;
            for(int j=0; j < rotations ; j++){
//                cv::Mat wavelet_blured;
//                cv::blur(jet_vector[i * rotations + j], wavelet_blured,cv::Size(13,13));

                theta_result.push_back( jet_vector[i * rotations + j].at<float>( y_used, x_used )  );
            }
            pixelResponse.push_back( theta_result );
        }
        response.push_back(pixelResponse);

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

    float k = std::sqrt(2);
    float p = 0.5;
    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
    int start_scale = 0;
    int end_scale = 6;
    int rows = end_scale - start_scale;

    filter::GaborJet matcher(45, 0.20, sigma, 12, start_scale, end_scale, k);

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


    cv::Mat transformed_image = plane_transform.transform_image(image, depth, image.cols/2, image.rows/2);

    cv::imshow("transformed", transformed_image);

//    cv::waitKey();

    /** Step 3:    **/

    cv::Mat gray_image;

    cv::cvtColor(transformed_image, gray_image, 0 );

    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create(300);
    std::vector<cv::KeyPoint> keypoints_1;
    f2d->detect( gray_image, keypoints_1 , mask);

    for (int i=0; i<keypoints_1.size(); i++){
      cv::KeyPoint kp = keypoints_1[i];
      cv::circle(transformed_image, kp.pt, cvRound(kp.size*0.25), cv::Scalar(255,255,0), 1, 8, 0);
    }

    cv::imshow("mywindow", transformed_image);
//    cv::waitKey();


    /** Step 4:    **/

    cv::Mat gaborResponse = matcher.filter(transformed_image);


    std::vector<std::vector< std::vector< float> > > gaborJets;

    gaborJets = getPixelJet( gaborResponse, rows, keypoints_1 );

//    for(int shift = 0; (unsigned)shift < gaborJets.size(); shift++ ){
//        for(int i=0; (unsigned)i < gaborJets[shift].size(); i++){
//            for(int j=0; (unsigned)j < gaborJets[shift][i].size(); j++){
//                std::cout << gaborJets[shift][i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    }

    /** Step 5:    **/

    cv::Mat image2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/img2.ppm");
    cv::Mat depth2 = cv::imread("/home/frederik/pcl/create_pcl/frosties_vpangle/depth2.pgm", -1);

    /** Step 5-a:    **/

    cv::Mat transformed_image2 = plane_transform.transform_image(image2, depth2, image2.cols/2, image2.rows/2);
    cv::imshow("transformed", transformed_image);

    /** Step 5-b:    **/

    cv::cvtColor(transformed_image2, gray_image, 0 );

    f2d = cv::xfeatures2d::SIFT::create();
    std::vector<cv::KeyPoint> keypoints_2;
    f2d->detect( gray_image, keypoints_2);

    for (int i=0; i<keypoints_2.size(); i++){
      cv::KeyPoint kp = keypoints_2[i];
      cv::circle(transformed_image2, kp.pt, cvRound(kp.size*0.25), cv::Scalar(255,255,0), 1, 8, 0);
    }

    cv::imshow("mywindow", transformed_image2);

    /** Step 5-c:    **/

    cv::Mat gaborResponse2 = matcher.filter(transformed_image2);

    std::vector<std::vector< std::vector< float> > > gaborJets2;

    gaborJets2 = getPixelJet( gaborResponse2, rows, keypoints_2 );

    /** Step 5-d:    **/

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

//        std::cout << keypoints_1[index_1].pt.x << " , " << keypoints_1[index_1].pt.y << std::endl;
//        std::cout << keypoints_2[bestIndex].pt.x << " , " << keypoints_2[bestIndex].pt.y << std::endl;
        float distance = std::sqrt( (keypoints_1[index_1].pt.x - keypoints_2[bestIndex].pt.x) * (keypoints_1[index_1].pt.x - keypoints_2[bestIndex].pt.x) + (keypoints_1[index_1].pt.y - keypoints_2[bestIndex].pt.y) * (keypoints_1[index_1].pt.y - keypoints_2[bestIndex].pt.y) );

//        std::cout << "Distance: " << distance << std::endl;
//        std::cout << std::endl;

        if(distance < 15)
            numberUnder15++;
        if(distance < 30)
            numberUnder30++;
        if(distance < 50)
            numberUnder50++;


    }


    std::cout << numberUnder15 << std::endl;
    std::cout << numberUnder30 << std::endl;
    std::cout << numberUnder50 << std::endl;

    cv::waitKey(0);

    return 0;

}
