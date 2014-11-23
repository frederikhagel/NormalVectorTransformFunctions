//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
    
#include <iostream>

int 
main (int argc, char** argv)
{

    if( argc != 2)
    {
     std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
     return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1]);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Display window", image );                   // Show our image inside it.

    cv::waitKey(0);                                          // Wait for a keystroke in the window

    cv::Mat input_cloud; 
    input_cloud = cv::Mat(480, 640, CV_8UC3); 

	for (int h=0; h< image.rows ; h++) {
	    for (int w=0; w<  image.cols ; w++) {

		cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(w,h));

		//std::cout << "x pos " << w << " y pos " << h << std::endl;
		//std::cout << "color " << (int)image.at<cv::Vec3b>(h, w)[0] << std::endl;

		if( !( (int)image.at<cv::Vec3b>(h, w)[0] == 0 and (int)image.at<cv::Vec3b>(h, w)[1] == 0 and (int)image.at<cv::Vec3b>(h, w)[2] == 255)  ){
		//	std::cout << " oh god" << std::endl;
			input_cloud.at<cv::Vec3b>(h, w)[0] = image.at<cv::Vec3b>(h, w)[0];
			input_cloud.at<cv::Vec3b>(h, w)[1] = image.at<cv::Vec3b>(h, w)[1];
			input_cloud.at<cv::Vec3b>(h, w)[2] = image.at<cv::Vec3b>(h, w)[2];

			}
		else{
		//	std::cout << " oh god" << std::endl;
			int left_pos = - 1;
			int right_pos =  1;
			
			while( left_pos + w > 0 
			and ( (int)image.at<cv::Vec3b>(h, left_pos + w)[0] == 0 and (int)image.at<cv::Vec3b>(h, left_pos + w)[1] == 0 and (int)image.at<cv::Vec3b>(h, left_pos + w)[2] == 255) )			
				{
				//std::cout << "ha" << std::endl;
			   	left_pos--;
				}

			while( right_pos + w < 640 -1 
			and ( (int)image.at<cv::Vec3b>(h, right_pos + w)[0] == 0 and (int)image.at<cv::Vec3b>(h, right_pos + w)[1] == 0 and (int)image.at<cv::Vec3b>(h, right_pos + w)[2] == 255) )			
				{
				//std::cout << "ha" << std::endl;
			   	right_pos++;
				}


			
			if( left_pos  + w >= 0 and right_pos  + w < 640)
				{
				if( !( (int)image.at<cv::Vec3b>(h, left_pos + w)[0] == 0 and (int)image.at<cv::Vec3b>(h, left_pos + w)[1] == 0 and (int)image.at<cv::Vec3b>(h, left_pos + w)[2] == 255) 
				and  !( (int)image.at<cv::Vec3b>(h, right_pos + w)[0] == 0 and (int)image.at<cv::Vec3b>(h, right_pos + w)[1] == 0 and (int)image.at<cv::Vec3b>(h, right_pos + w)[2] == 255) )
					{
					float left_right_weight = -left_pos/right_pos;
					int pixel_color = (int) image.at<cv::Vec3b>(h, left_pos + w)[0]/2 + image.at<cv::Vec3b>(h, right_pos + w)[0]/2 ;

					input_cloud.at<cv::Vec3b>(h, w)[0] = pixel_color;
					input_cloud.at<cv::Vec3b>(h, w)[1] = pixel_color;
					input_cloud.at<cv::Vec3b>(h, w)[2] = pixel_color;
					}
				else
					{
					input_cloud.at<cv::Vec3b>(h, w)[0] = 255;
					input_cloud.at<cv::Vec3b>(h, w)[1] = 0;
					input_cloud.at<cv::Vec3b>(h, w)[2] = 0;
					 }
				}
		}

	    }
	}

    cv::namedWindow( "corrected image window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "corrected image window", input_cloud );    

    cv::waitKey(0);  

    std::cout << " saving interpolated image " << std::endl;
    cv::imwrite( "test_image_interpolation.png", input_cloud );	

    return 0;
}
