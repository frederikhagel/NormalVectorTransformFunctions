// Copyright (c) 2013, University of Southern Denmark
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the University of Southern Denmark nor the names of
//    its contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OF SOUTHERN DENMARK BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "gabor_filter.h"
//#include "../core/macros.h"
//#include "../covis_config.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//using namespace covis::filter;

GaborFilter::GaborFilter(int ksize, float f0, float sigma, float theta, float scale, float scaling) {
//    COVIS_ASSERT(ksize > 0 && f0 > 0);
//    COVIS_ASSERT(theta >= 0 && theta <= M_PI);
    
    //save the scaling for filtering
    _scaling = scale;
    _scaleSize = scaling;
    //convert frequency to wavelength
    float lambda = 1/f0;
    //add frequency to sigma, according to "Fast Extraction of multi-resolution Gabor features"
    float ksigma = sigma/f0;
    //create real and imaginary kernel
    _realKernel = cv::getGaborKernel(cv::Size(ksize, ksize), ksigma, theta, lambda, 1,  0);
    cv::resize(_realKernel, _realKernel, cv::Size( _realKernel.cols * pow(_scaleSize,_scaling), _realKernel.rows * pow(_scaleSize,_scaling) ) );
    _realKernel = _realKernel/ ( pow(2 * _scaleSize,_scaling) );
    _imaginaryKernel = cv::getGaborKernel(cv::Size(ksize, ksize), ksigma, theta, lambda, 1,  M_PI_2);
    cv::resize(_imaginaryKernel, _imaginaryKernel, cv::Size( _imaginaryKernel.cols * pow(_scaleSize,_scaling) + 1, _imaginaryKernel.rows * pow(_scaleSize,_scaling)  + 1) );
    _imaginaryKernel = _imaginaryKernel/ ( pow(2 * _scaleSize,_scaling) );
}

GaborFilter::~GaborFilter() {}

cv::Mat GaborFilter::filter(const cv::Mat& srcfR, int x, int y) {
    //convert to grayscale
//    cv::Mat grayImage;
//    if(image.channels() == 1)
//        grayImage = image;
//    else
//        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    //resize according to scale

    //create images for conversion and results as floating point, normalized
    cv::Mat resultReal, resultImaginary;
//    grayImage.convertTo(srcfR, CV_32FC1, 1, 0);
//    grayImage.convertTo(srcfI, CV_32FC1, 1, 0);

    cv::Mat onePixelSourceROIR(srcfR, cv::Rect( cv::Point(x ,y), cv::Size(1, 1) ));
    cv::Mat onePixelSourceROII(srcfR, cv::Rect( cv::Point(x ,y), cv::Size(1, 1) ));

    cv::filter2D(onePixelSourceROIR, resultReal, CV_32FC1, _realKernel);
    cv::filter2D(onePixelSourceROII, resultImaginary,  CV_32FC1, _imaginaryKernel);

    cv::Mat magnitudeResult;

    //get magnitude of signal
    cv::magnitude( resultReal, resultImaginary, magnitudeResult);

    //return image to original signal
    //cv::resize(magnitudeResult, magnitudeResult,  cv::Size(image.cols, image.rows));

    return magnitudeResult;
}
