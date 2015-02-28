#ifndef GABORMATCHER_HPP
#define GABORMATCHER_HPP

#include <iostream>
#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <covis/covis.h>
using namespace covis;


class gaborMatcher
{

public:

gaborMatcher(int kernel_size, float f0, float sigma, int n_of_theta, int start_scale, int end_scale, float k);

~gaborMatcher();

void addImage(cv::Mat image, std::string fileName);

std::string compareImage( cv::Mat image );

void showKernel();

private:

int _rows;

std::vector< filter::GaborJet> _jet;

std::vector< std::vector< std::vector< std::vector<float> > > > _compareJets;

std::vector< std::string > _nameList;

};

#endif /*GABORMATCHER_HPP*/
