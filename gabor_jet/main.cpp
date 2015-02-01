//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
    
#include <opencv2/opencv.hpp>
#include <iostream>

//#include "gaborWavelet.hpp"
#include "gaborJet.hpp"

#include <glob.h>
#include <fstream>

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

    // create jet space with kernel size 17, frequency 0.2, sigma 1, 8 rotations and five scales
    gaborJet second_test(17, 0.2, 1, 8, 5);

    // create vector for comparison jets

    std::vector<std::string> compare_names;
    std::vector< std::vector< std::vector<cv::Mat> > > compare_jets;

    std::string file_line;
    std::ifstream file ("/home/frederik/pcl/brodatz/textures/images_to_test.txt");

    if (file.is_open())
    {
      while ( std::getline (file, file_line) )
      {
        std::cout << file_line << std::endl;
        compare_names.push_back(file_line);
        cv::Mat image = cv::imread(file_line);
        std::vector< std::vector<cv::Mat> > response = second_test.computeResponse(image);
        compare_jets.push_back(response);
      }
    }


    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/vertical_images/transformed_image*.jpeg");

    std::cout << images_to_test.size() << std::endl;

    cv::Mat image = cv::imread("/home/frederik/pcl/images/vertical_images/transformed_image0.0 0.0 0.1745datz_D95.jpeg", 1);


//    first_test.showRealKernel(0);

//    std::vector< std::vector<cv::Mat> > response = second_test.computeResponse(image);
//    std::vector< std::vector<cv::Mat> > response2 = second_test.computeResponse(image2);
//    std::vector< std::vector<cv::Mat> > response3 = second_test.computeResponse(image3);
//    std::vector< std::vector<cv::Mat> > response4 = second_test.computeResponse(image4);

//    std::cout << second_test.compareJetSinglePixel(response, response) << std::endl;
//    std::cout << second_test.compareJetSinglePixel(response, response2) << std::endl;
//    std::cout << second_test.compareJetSinglePixel(response, response3) << std::endl;
//    std::cout << second_test.compareJetSinglePixel(response, response4) << std::endl;



//    cv::normalize( response, response ,0, 255 )

}


//int main (int argc, char** argv)
//{

//    cv::Mat image = cv::imread("/home/frederik/pcl/images/vertical_images/transformed_image0.0 0.0 0.1745datz_D95.jpeg", 1);


//    gaborWavelet first_test(17, 0.2, 1, 0, 0);

//    first_test.showRealKernel(0);

//    std::cout << "HE";

//    cv::Mat response = first_test.computeResponse(image);

////    cv::normalize( response, response ,0, 255 );

//    response.convertTo(response, CV_8UC1);

//    cv::imshow("response", response);

//    cv::waitKey(0);

//}