//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
    
#include <opencv2/opencv.hpp>
#include <iostream>

#include <covis/covis.h>
using namespace covis;

#include <glob.h>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "gaborMatcher.hpp"


inline std::vector<std::string> glob(const std::string& pat){
    using namespace std;
    glob_t glob_result;
    glob(pat.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> ret;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        ret.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return ret;
}


int main (int argc, char** argv)
{

//    float k = std::sqrt(2);
//    float p = 0.5;
//    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
//    int start_scale = 0;
//    int end_scale = 6;



// are we doing sigma correction? yes, yes we are
    float k = atof( argv[1] );
    float p = atof( argv[2] );
    float sigma = (1/M_PI) * (( k +1)/(k-1))* sqrt(-log(p));
    int start_scale = atoi( argv[3] );
    int end_scale = atoi( argv[4] );
    int rotations = atoi( argv[5] );
    float frequency = atof( argv[6] );
    float sigma_corrector = atoi( argv[7] );



    int rows = end_scale - start_scale;
    gaborMatcher matcher(45, frequency, sigma*std::pow(frequency,sigma_corrector), rotations, start_scale, end_scale, k);

//    matcher.showKernel();


    std::string file_line;
    std::ifstream file ("/home/frederik/pcl/brodatz/textures/images_to_test.txt");

    if (file.is_open())
    {
      while ( std::getline (file, file_line) )
      {

        cv::Mat image = cv::imread(file_line, 0);
        cv::resize(image, image, cv::Size( 480, 480 ), 0.48, 0.48, 0);
        matcher.addImage(image, file_line);

      }
    }






//    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/vertical_images/transformed_image0.0 0.0 0.0*.jpeg");
    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/rotated_images/transformed_image0.0*.jpeg");

    std::vector<std::string> rotations_as_string;
    rotations_as_string.push_back("0.0");
    rotations_as_string.push_back("0.1745");
    rotations_as_string.push_back("0.3491");
    rotations_as_string.push_back("0.5236");
    rotations_as_string.push_back("0.6981");
    rotations_as_string.push_back("0.8727");
    rotations_as_string.push_back("1.047");
    rotations_as_string.push_back("1.222");
    rotations_as_string.push_back("1.396");


for(int rotation = 0; rotation < 9; rotation++)
{
    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/rotated_images/transformed_image" + rotations_as_string[rotation] + "*.jpeg");


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

}
