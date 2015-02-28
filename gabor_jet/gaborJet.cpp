#include "gaborWavelet.hpp"
#include "gaborJet.hpp"


// Standard library includes
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;




gaborJet::gaborJet(int ks, float f0, float sigma, int n_of_theta, int n_of_scales){

//    float lambda = 1/f0;
//    float kernel_sigma = sigma/f0;

    for( int scale_index = 0; scale_index < n_of_scales; scale_index++){
        std::vector<gaborWavelet> theta_jet;
        for( int theta_index = 0; theta_index < n_of_theta; theta_index++){
            float theta = (theta_index * M_PIl)/n_of_theta;
            gaborWavelet wavelet(ks, f0, sigma, theta, scale_index);
//            wavelet.showRealKernel(0);
            theta_jet.push_back(  wavelet );
//            jetSpace[scale_index].push_back(  wavelet );
        }
        _jetSpace.push_back( theta_jet );
    }
}

gaborJet::~gaborJet() {}


std::vector< std::vector<cv::Mat> > gaborJet::computeResponse(cv::Mat image) {

    std::vector< std::vector<cv::Mat> > result;

//    std::cout <<jetSpace.size() << std::endl;

    for(int i=0; i < _jetSpace.size(); i++){
        std::vector<cv::Mat> theta_result;
        for(int j=0; j < _jetSpace[i].size(); j++){
            cv::Mat wavelet_result = _jetSpace[i][j].computeResponse(image);
            theta_result.push_back( wavelet_result );
        }
        result.push_back( theta_result );
    }

    return result;

}

float gaborJet::compareJetSinglePixel(std::vector< std::vector<float> > jetSpace1, std::vector< std::vector<float> > jetSpace2){
    float dot = 0;
    float norm1 = 0;
    float norm2 = 0;

    for(int i=0; i < jetSpace1.size(); i++){
        for(int j=0; j < jetSpace1[i].size(); j++){
            dot += jetSpace1[i][j] *  jetSpace2[i][j];
            norm1 += pow(jetSpace1[i][j],2);
            norm2 += pow(jetSpace2[i][j],2);
//            std::cout << jetSpace1[i][j].at<float>(y, x) << std::endl;

        }
    }

    norm1 = sqrt( norm1);
    norm2 = sqrt( norm2);

    dot = dot /(norm1*norm2);

    return dot;
}



cv::Mat gaborJet::showRealJet(int time) {

    std::vector<cv::Mat> thetaResponces;

//    float largest_scale = _jetSpace[0].size() -1;
//    int original_shape_x = _jetSpace[0][0].showRealKernel(1).cols;
//    int original_shape_y = _jetSpace[0][0].showRealKernel(1).rows;


    for(int i=0; i < _jetSpace.size(); i++){
        std::vector<cv::Mat> responces;
        for(int j=0; j < _jetSpace[i].size(); j++){
            cv::Mat current_image =_jetSpace[i][j].showRealKernel(1);
//            cv::Mat larger_image;
//            cv::resize(current_image, larger_image, cv::Size( original_shape_x * pow(2, largest_scale), original_shape_y * pow(2, largest_scale) ) );

            responces.push_back( current_image );
            }
        cv::Mat theta_image;
        cv::hconcat(responces, theta_image);
        thetaResponces.push_back( theta_image );
    }
    cv::Mat combinedImage;
    cv::vconcat(thetaResponces, combinedImage );
//    image_to_show = cv2.normalize( image_to_show,0,255 )
    cv::imshow("Gabor Kernels", combinedImage);
    cv::waitKey(time);
    return combinedImage;
}
