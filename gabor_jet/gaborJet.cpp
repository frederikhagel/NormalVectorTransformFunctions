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

    float lambda = 1/f0;
    float kernel_sigma = 2/pow(f0, 2);

    for( int scale_index = 0; scale_index < n_of_scales; scale_index++){
        std::vector<gaborWavelet> theta_jet;
        for( int theta_index = 0; theta_index < n_of_theta; theta_index++){
            float theta = (theta_index * M_PIl)/n_of_theta;
            gaborWavelet wavelet(ks, f0, sigma, theta, scale_index);
//            wavelet.showRealKernel(0);
            theta_jet.push_back(  wavelet );
//            jetSpace[scale_index].push_back(  wavelet );
        }
        jetSpace.push_back( theta_jet );
    }
}

gaborJet::~gaborJet() {}


std::vector< std::vector<float> > gaborJet::computeResponse(cv::Mat image) {

    std::vector< std::vector<float> > result;

//    std::cout <<jetSpace.size() << std::endl;

    for(int i=0; i < jetSpace.size(); i++){
        std::vector<float> theta_result;
        for(int j=0; j < jetSpace[i].size(); j++){
            cv::Mat wavelet_result = jetSpace[i][j].computeResponse(image);
            int y = wavelet_result.rows/2;
            int x = wavelet_result.cols/2;
            theta_result.push_back( wavelet_result.at<float>( y, x ) );
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



//cv::Mat gaborJet::showRealJet(int time) {

//    cv::imshow("Real Kernel", real_kernel);
//    cv::waitKey(time);
//    return real_kernel;
//}
