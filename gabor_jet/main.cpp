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

inline




std::vector< std::vector< float> > getMiddlePixel( std::vector< std::vector<cv::Mat> > wavelet_result){

    std::vector< std::vector<float> > response;

    for(int i=0; i < wavelet_result.size(); i++){
        std::vector<float> theta_result;
        for(int j=0; j < wavelet_result[i].size(); j++){
            cv::Mat wavelet_blured;
            cv::blur(wavelet_result[i][j], wavelet_blured,cv::Size(21,21));
            int y = wavelet_blured.rows/2;
            int x = wavelet_blured.cols/2;
            theta_result.push_back( wavelet_blured.at<float>( y, x )  );
        }
        response.push_back( theta_result );

    }
    return response;
}

inline cv::Mat showJetSpace( std::vector< std::vector<cv::Mat> > wavelet_result ){

    std::vector<cv::Mat> thetaResponces;
    for(int i=0; i < wavelet_result.size(); i++){
        std::vector<cv::Mat> responces;
        for(int j=0; j < wavelet_result[i].size(); j++){
            cv::Mat current_image = wavelet_result[i][j];
            cv::Mat smaller_image;
            int original_shape_x = current_image.cols;
            int original_shape_y = current_image.rows;
            cv::resize(current_image, smaller_image, cv::Size( original_shape_x / pow(2, 2), original_shape_y / pow(2, 2) ) );

            responces.push_back( smaller_image );
            }
        cv::Mat theta_image;
        cv::hconcat(responces, theta_image);
        thetaResponces.push_back( theta_image );
    }
    cv::Mat combinedImage;
    cv::vconcat(thetaResponces, combinedImage );
    cv::imshow("Jet Space", combinedImage);
    cv::waitKey(0);

    return combinedImage;
}


int main (int argc, char** argv)
{


    cv::Mat test_i = cv::Mat( 500, 500, CV_32SC( 4 * 8 ) );
    std::vector< cv::Mat > test( 4 * 8 );
    cv::split(test_i, test);
    cv::imshow("test", test[ 0 ]);
    cv::waitKey(0);

    // create jet space with kernel size 17, frequency 0.2, sigma 1, 8 rotations and five scales
    float k = 2;
    float p = 0.9;
    float sigma = (( k +1)/(k-1))* sqrt(-log(p));
    std::cout << sigma << std::endl;
    gaborJet second_test(17, 0.2, sigma, 8, 4);
    second_test.showRealJet(0);

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

        std::vector< std::vector<cv::Mat> > wavelet_result = second_test.computeResponse(image);
        std::vector< std::vector<float> > result = getMiddlePixel(wavelet_result);


// show jet image
        showJetSpace( wavelet_result );
// show jet image

        compare_jets.push_back( result );
      }
    }


    std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/vertical_images/transformed_image*.jpeg");
//        std::vector<std::string> images_to_test = glob("/home/frederik/pcl/images/all_images/transformed_image*.jpeg");
    std::cout << images_to_test.size() << std::endl;

    int number_of_correct = 0; //sadly

    for(int image_index = 0; image_index < images_to_test.size(); image_index++)
    {
        float best_match = 0;
        std::string best_name = "0";
        cv::Mat image = cv::imread(images_to_test[image_index]);

        std::vector< std::vector<cv::Mat> > wavelet_result = second_test.computeResponse(image);

        std::vector< std::vector<float> > response = getMiddlePixel(wavelet_result);


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


}
