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

#include "gabor_jet.h"

//#include "../core/macros.h"
//#include "../covis_config.h"

#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//using namespace covis::filter;

GaborJet::GaborJet(int ksize, float f0, float sigma, int ntheta, int startscales, int endscales, float k) {

    for(int scaleIndex = startscales; scaleIndex < endscales; scaleIndex++) {

        std::vector< GaborFilter > thetaJet;

        for(int thetaIndex = 0; thetaIndex < ntheta; thetaIndex++) {
            float theta = (thetaIndex * M_PI) / ntheta;
            thetaJet.push_back(GaborFilter(ksize, f0, sigma, theta, scaleIndex, k));
        }
        
        _jetSpace.push_back(thetaJet);
    }
}

GaborJet::~GaborJet() {}

cv::Mat GaborJet::filter(const cv::Mat& image, int x, int y) {
    //convert to grayscale
    cv::Mat grayImage;
    if(image.channels() == 1)
        grayImage = image;
    else
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat srcfR;
    grayImage.convertTo(srcfR, CV_32FC1, 1, 0);
    //    grayImage.convertTo(srcfI, CV_32FC1, 1, 0);

    std::vector<cv::Mat> resultVector( _jetSpace.size() * _jetSpace[0].size());
    for(size_t i = 0; i < _jetSpace.size(); i++)
        for(size_t j = 0; j < _jetSpace[i].size(); j++)
            resultVector[ i * _jetSpace[0].size() + j ] = _jetSpace[i][j].filter(srcfR, x, y);
            //resultVector[i * _jetSpace[0].size() + j] = image;
    
    cv::Mat result;
    cv::merge(resultVector, result);
    
    return result;
}


float GaborJet::compareSinglePixel(std::vector<std::vector<float> > pixelJet1, std::vector<std::vector<float> > pixelJet2 ){
    float dot = 0;
    float norm1 = 0;
    float norm2 = 0;

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

    return dot;
}

cv::Mat GaborJet::getRealJet() {
    std::vector<cv::Mat> thetaResponses;
    
    for(size_t i = 0; i < _jetSpace.size(); i++) {
        std::vector<cv::Mat> responses;
        for(int j=0; (unsigned)j < _jetSpace[i].size() ; j++)
            responses.push_back(_jetSpace[i][j].getRealKernel());

        cv::Mat thetaImage;
        cv::hconcat(responses, thetaImage);
        thetaResponses.push_back(thetaImage);
    }

    cv::Mat combinedImage;
    cv::vconcat(thetaResponses, combinedImage );

    return combinedImage;

}

cv::Mat GaborJet::getImaginaryJet() {
    std::vector<cv::Mat> thetaResponses;
    
    for(size_t i = 0; i < _jetSpace.size(); i++) {
        std::vector<cv::Mat> responses;
        for(int j=0; (unsigned)j < _jetSpace[i].size() ; j++)
            responses.push_back(_jetSpace[i][j].getImaginaryKernel());

        cv::Mat thetaImage;
        cv::hconcat(responses, thetaImage);
        thetaResponses.push_back(thetaImage);
    }

    cv::Mat combinedImage;
    cv::vconcat(thetaResponses, combinedImage );

    return combinedImage;

}
