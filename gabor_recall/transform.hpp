#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <iostream>
#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

class transform
{

public:

transform();

~transform();

std::vector<cv::Mat> transform_image(cv::Mat image_color, cv::Mat image_depth, std::vector<int> xList, std::vector<int> yList);

private:

};

#endif /*TRANSFORM_HPP*/
