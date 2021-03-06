//include cv2
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
    
#include <opencv2/opencv.hpp>

#include <iostream>

int 
main (int argc, char** argv)
{

    if( argc != 3)
    {
     std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
     return -1;
    }

    cv::Mat original_image;
    original_image = cv::imread(argv[1]);   // Read the file

    cv::Mat test_image;
    test_image = cv::imread(argv[2]);   // Read the file


    if(! (test_image.data and original_image.data) )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    cv::Mat croppedImage_o = original_image(cv::Rect(190,190,100,100));
    cv::Mat croppedImage_t = test_image(cv::Rect(270,190,100,100));


    cv::namedWindow( "original_image", cv::WINDOW_AUTOSIZE );	      // Create a window for display.
    cv::imshow( "original_image", croppedImage_o );                   // Show our image inside it.

    cv::namedWindow( "test_image", cv::WINDOW_AUTOSIZE );	  // Create a window for display.
    cv::imshow( "test_image", croppedImage_t );                   // Show our image inside it.

    cv::Mat res_o;
    cv::Mat res_t;

    cv::GaussianBlur(croppedImage_o,res_o, cv::Size(15,15),0,0,0);
    cv::GaussianBlur(croppedImage_t,res_t, cv::Size(15,15),0,0,0);

    cv::namedWindow( "origi_image", cv::WINDOW_AUTOSIZE );			// Create a window for display.
    cv::imshow( "origi_image", res_o - res_t );               // Show our image inside it.

    int match_method = 0;
    cv::Mat result;
    cv::matchTemplate( croppedImage_o, croppedImage_t, result, match_method );


    //cv::namedWindow( "result", cv::WINDOW_AUTOSIZE );// Create a window for display.
    //cv::imshow( "result", result );                   // Show our image inside it.
    std::cout << " result " << result << std::endl;
    cv::waitKey(0);                                          // Wait for a keystroke in the window

    std::cout << " saving resized image " << std::endl;
    cv::imwrite( "test_image_rezise.png", croppedImage_o );	

    return 0;
}
