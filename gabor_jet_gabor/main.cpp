//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
    
#include <opencv2/opencv.hpp>
#include <iostream>

#include <fstream>

#define _USE_MATH_DEFINES

#include <math.h>


#include <covis/covis.h>
using namespace covis;

#include "gaborMatcher.hpp"
#include "transform.hpp"


int main (int argc, char** argv)
{

    float k = std::sqrt(2);
    float p = 0.5;
    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
    int start_scale = 0;
    int end_scale = 6;
    int rows = end_scale - start_scale;
    gaborMatcher matcher(45, 0.20, sigma, 12, start_scale, end_scale, k);

    matcher.showKernel();


    transform plane_transform();

    /** Step 1:    **/
    cv::Mat image = cv::imread(images_to_test[image_index]);



    /** Step 2:    **/

    /** Step 3:    **/

    /** Step 4:    **/

        cv::Mat image = cv::imread(file_line, 0);
        cv::resize(image, image, cv::Size( 480, 480 ), 0.48, 0.48, 0);
        matcher.addImage(image, file_line);






//    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/vertical_images/transformed_image0.0 0.0 0.0*.jpeg");
    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/rotated_images/transformed_image*.jpeg");


    std::cout << images_to_test.size() << std::endl;

    int number_of_correct = 0; //sadly

    for(int image_index = 0; (unsigned) image_index < images_to_test.size(); image_index++)
    {
        cv::Mat image = cv::imread(images_to_test[image_index]);

        std::string best_name = matcher.compareImage(image);

//        std::cout << std::endl;
        int pos = images_to_test[image_index].find("D");
        std::string correct_string = images_to_test[image_index].substr(pos,10);
//        std::cout << correct_string << std::endl;

        pos = best_name.find("D");
        best_name = best_name.substr(pos,10);
//        std::cout << best_name << std::endl;

        if( correct_string == best_name)
        {
            number_of_correct += 1;
        }

    }

    std::cout << "Number of correct: " << number_of_correct << std::endl;


}
