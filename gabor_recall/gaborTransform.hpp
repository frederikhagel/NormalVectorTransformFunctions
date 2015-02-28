#ifndef GABORTRANSFORM_HPP
#define GABORTRANSFORM_HPP

#include <iostream>
#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <covis/covis.h>
using namespace covis;


class gaborTransform
{

public:

gaborTransform(int kernel_size, float f0, float sigma, int n_of_theta, int start_scale, int end_scale, float k);

~gaborTransform();

std::vector< std::vector< std::vector<float> > >  getTransformedPixelJet( cv::Mat image, cv::Mat depth, int x, int y );

void showKernel();

private:

int _rows;

filter::GaborJet _jet;

};

#endif /*GABORTRANSFORM_HPP*/
