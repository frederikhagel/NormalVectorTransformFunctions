#include "gaborWavelet.hpp"


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




gaborWavelet::gaborWavelet(int ks, float f0, float sigma, float theta, float scale){
    _scaling = scale;
    float lambda = 1/f0;

    float kernel_sigma = sigma/f0;

    _realKernel = cv::getGaborKernel(cv::Size(ks, ks), kernel_sigma, theta, lambda, 1,  0);
    _imaginaryKernel = cv::getGaborKernel(cv::Size(ks, ks), kernel_sigma, theta, lambda, 1,  3.14159265359/2);


}

gaborWavelet::~gaborWavelet() {}


cv::Mat gaborWavelet::computeResponse(cv::Mat image) {

    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    int original_shape_x = image.cols;
    int original_shape_y = image.rows;

    cv::resize(grayImage, grayImage, cv::Size( original_shape_x / pow(2, _scaling), original_shape_y / pow(2, _scaling) ) );

    cv::Mat src_fR, src_fI, resultReal, resultImaginary;


    grayImage.convertTo(src_fR, CV_32FC1);
    grayImage.convertTo(src_fI, CV_32FC1);

    src_fR *= 1./255;
    src_fI *= 1./255;


    cv::filter2D(src_fR, resultReal, CV_32FC1, _realKernel);
    cv::filter2D(src_fI, resultImaginary,  CV_32FC1, _imaginaryKernel);

    cv::Mat magnitudeResult;

    cv::magnitude( resultReal, resultImaginary, magnitudeResult);

    cv::resize(magnitudeResult, magnitudeResult,  cv::Size(original_shape_x, original_shape_y));

    return magnitudeResult;

}

cv::Mat gaborWavelet::showRealKernel(int time) {

    cv::imshow("Real Kernel", _realKernel);
    cv::waitKey(time);
    return _realKernel;
}
