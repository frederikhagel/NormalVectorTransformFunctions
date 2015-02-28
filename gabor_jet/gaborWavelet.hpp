#ifndef GABORWAVELET_HPP
#define GABORWAVELET_HPP

#include <iostream>
#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

class gaborWavelet
{

public:

gaborWavelet(int kernel_size, float f0, float sigma, float theta, float scale);
~gaborWavelet();

cv::Mat computeResponse(cv::Mat image);

cv::Mat showRealKernel(int time);

private:

float _scaling;

cv::Mat _realKernel;
cv::Mat _imaginaryKernel;

};

#endif /*GABORWAVELET_HPP*/
