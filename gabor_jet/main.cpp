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
    std::vector< std::vector< std::vector<float> > > compare_jets;

    std::string file_line;
    std::ifstream file ("/home/frederik/pcl/brodatz/textures/images_to_test.txt");

    if (file.is_open())
    {
      while ( std::getline (file, file_line) )
      {
//        std::cout << file_line << std::endl;
        compare_names.push_back(file_line);
        cv::Mat image = cv::imread(file_line);
        cv::resize(image, image, cv::Size( 480, 480 ), 0.48, 0.48, 0);
        std::vector< std::vector<float> > response = second_test.computeResponse(image);

        compare_jets.push_back(response);
      }
    }


//    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/vertical_images/transformed_image*.jpeg");
        std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/all_images/transformed_image*.jpeg");
    std::cout << images_to_test.size() << std::endl;

    int number_of_correct = 0; //sadly

    for(int image_index = 0; image_index < images_to_test.size(); image_index++)
    {
        float best_match = 0;
        std::string best_name = "0";
        cv::Mat image = cv::imread(images_to_test[image_index]);
        std::vector< std::vector<float> > response = second_test.computeResponse(image);
        for( int compare_index = 0; compare_index < compare_jets.size(); compare_index++)
        {
            float match = second_test.compareJetSinglePixel(response, compare_jets[compare_index]);
            if( match > best_match)
            {
                best_match = match;
                best_name = compare_names[compare_index];

            }

        }
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
