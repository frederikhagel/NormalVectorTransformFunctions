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
    scaling = scale;
    float lambda = 1/f0;

    float kernel_sigma = sigma/f0;

    real_kernel = cv::getGaborKernel(cv::Size(ks, ks), kernel_sigma, theta, lambda, 1,  0);
    imaginary_kernel = cv::getGaborKernel(cv::Size(ks, ks), kernel_sigma, theta, lambda, 1,  3.14159265359/2);


}

gaborWavelet::~gaborWavelet() {}


cv::Mat gaborWavelet::computeResponse(cv::Mat image) {

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    int original_shape_x = image.cols;
    int original_shape_y = image.rows;

    cv::resize(gray_image, gray_image, cv::Size( original_shape_x / pow(2, scaling), original_shape_y / pow(2, scaling) ) );

    cv::Mat src_fR, src_fI, result_real, result_imaginary;


    gray_image.convertTo(src_fR, CV_32FC1);
    gray_image.convertTo(src_fI, CV_32FC1);

    src_fR *= 1./255;
    src_fI *= 1./255;


    cv::filter2D(src_fR, result_real, CV_32FC1, real_kernel);
    cv::filter2D(src_fI, result_imaginary,  CV_32FC1, imaginary_kernel);

    cv::Mat magnitude_result;

    cv::magnitude(result_real, result_imaginary, magnitude_result);

    cv::resize(magnitude_result, magnitude_result,  cv::Size(original_shape_x, original_shape_y));

    return magnitude_result;

}

cv::Mat gaborWavelet::showRealKernel(int time) {

    cv::imshow("Real Kernel", real_kernel);
    cv::waitKey(time);
    return real_kernel;
}
