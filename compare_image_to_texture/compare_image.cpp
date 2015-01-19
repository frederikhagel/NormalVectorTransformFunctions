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


    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Display window", original_image );                   // Show our image inside it.

    cv::waitKey(0);                                          // Wait for a keystroke in the window

    cv::Mat resized_image; 
    resized_image = cv::Mat(480, 640, CV_8UC3); 

    cv::resize(original_image, resized_image, cv::Size(0,0), 0.48, 0.48, 0); //resized_image.size()

    cv::namedWindow( "resized image window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "resized image window", resized_image );    

    std::cout << resized_image.size() << std::endl;

    std::cout << " saving resized image " << std::endl;
    cv::imwrite( "test_image_rezise.png", resized_image );	

    /* Change from resizing to cropping */

    float min_result = 1;
    int x = 0;
    int y = 0;


    //for(int translation_y = -5; translation_y < 10; translation_y++){
    //for(int translation_x = -5; translation_x < 10; translation_x++){

    cv::Mat croppedImage_o = resized_image(cv::Rect(180 ,180 ,120,120));
    cv::Mat croppedImage_t = test_image(cv::Rect(270,190,100,100));

    cv::namedWindow( "resized_image", cv::WINDOW_AUTOSIZE );	      // Create a window for display.
    cv::imshow( "resized_image", croppedImage_o );                   // Show our image inside it.

    cv::namedWindow( "test_image", cv::WINDOW_AUTOSIZE );	  // Create a window for display.
    cv::imshow( "test_image", croppedImage_t );                   // Show our image inside it.

    cv::Mat res_o;
    cv::Mat res_t;

    cv::GaussianBlur(croppedImage_o,res_o, cv::Size(15,15),0,0,0);
    cv::GaussianBlur(croppedImage_t,res_t, cv::Size(15,15),0,0,0);

    //cv::namedWindow( "origi_image", cv::WINDOW_AUTOSIZE );			// Create a window for display.
    //cv::imshow( "origi_image", res_o - res_t );               // Show our image inside it.

    int match_method = cv::TM_SQDIFF_NORMED;
    cv::Mat result;
    std::cout << " testing 1" << std::endl;
    cv::matchTemplate( croppedImage_o, croppedImage_t, result, match_method );

    std::cout << " testing 2" << std::endl;
    //cv::namedWindow( "result", cv::WINDOW_AUTOSIZE );// Create a window for display.
    //cv::imshow( "result", result );                   // Show our image inside it.
    std::cout << " result " << result.at<float>(0,0) << std::endl;
    cv::waitKey(0);                                          // Wait for a keystroke in the window

    if( min_result > result.at<float>(0,0)){
    min_result = result.at<float>(0,0);
//	x = translation_x;
//        y = translation_y;
	}

    //}
    //}

    std::cout << x << " " << y << " " << min_result << std::endl;
    //cv::imwrite( "test_image_rezise.png", croppedImage_o );

    return 0;
}
