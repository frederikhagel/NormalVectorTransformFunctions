#ifndef GABORJET_HPP
#define GABORJET_HPP

#include <iostream>
#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


// Wavelet
#include "gaborWavelet.hpp"

class gaborJet
{

public:

gaborJet(int kernel_size, float f0, float sigma, int n_of_theta, int n_of_scales);
~gaborJet();

std::vector< std::vector<cv::Mat> > computeResponse(cv::Mat image);

cv::Mat showRealJet(int time);

float compareJetSinglePixel(std::vector< std::vector<cv::Mat> > jetSpace1, std::vector< std::vector<cv::Mat> > jetSpace2);

private:

float scaling;

std::vector< std::vector<gaborWavelet> > jetSpace;

};

#endif /*GABORJET_HPP*/
