#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
    
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>

//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

int user_data;
        
int 
main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile (argv[1], *cloud);
    
    pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> ne;
    ne.setInputCloud (cloud);

    cv::Mat input_cloud; 
    input_cloud = cv::Mat(480, 640, CV_8UC3); 

    if (!cloud->empty()) {

	for (int h=0; h<cloud->height; h++) {
	    for (int w=0; w<cloud->width; w++) {
	        pcl::PointXYZRGBA point = cloud->at(w, h);

	        Eigen::Vector3i rgb = point.getRGBVector3i();

		int x_pos = 320 +  point.x/point.z  *480;
		int y_pos = 240 +  point.y/point.z * 480;

		//std::cout << "x pos" << x_pos << "y pos" << y_pos << std::endl;

		if( x_pos > 0 and x_pos < 640 and y_pos > 0 and y_pos < 480){	
			input_cloud.at<cv::Vec3b>(y_pos,x_pos)[0] = rgb[2];
			input_cloud.at<cv::Vec3b>(y_pos,x_pos)[1] = rgb[1];
			input_cloud.at<cv::Vec3b>(y_pos,x_pos)[2] = rgb[0];

			}

	    }
	}
    }

    std::cout << " saving input image " << std::endl;
    cv::imwrite( "image_no_pespective_correction.png", input_cloud );

    // Create an empty kdtree representation, and pass it to the normal estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    pcl::search::KdTree<pcl::PointXYZRGBA>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGBA> ());
    ne.setSearchMethod (tree);

    // Output datasets
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    // Use all neighbors in a sphere of radius 3cm
    ne.setRadiusSearch (0.03);

    std::cout << " starting computation " << std::endl;

    // Compute the features
    ne.compute (*cloud_normals);

    std::cout << "cloud_normals->points.size (): " << cloud_normals->points.size () << std::endl;


    pcl::Normal normal_point = cloud_normals->at(320, 240);
    pcl::PointXYZRGBA _point = cloud->at(320, 240);

    std::cout << "cloud_normal at point: " << normal_point << std::endl;
    std::cout << "z of cloud at point : " << _point.z << std::endl;


    Eigen::Vector3f z_axis(normal_point.normal_x,normal_point.normal_y,normal_point.normal_z);

    Eigen::Vector3f x_axis_standard(1,0,0);

    Eigen::Vector3f x_proj = x_axis_standard - x_axis_standard.dot(z_axis)*z_axis;

    Eigen::Affine3f translate_z;
    Eigen::Affine3f transformation;

    Eigen::Vector3f tmp0 = x_proj.normalized();
    Eigen::Vector3f tmp1 = (z_axis.normalized().cross(x_proj.normalized())).normalized();
    Eigen::Vector3f tmp2 = z_axis.normalized();

    translate_z(0,0)=1; translate_z(0,1)=0; translate_z(0,2)=0; translate_z(0,3)=0.0f;
    translate_z(1,0)=0; translate_z(1,1)=1; translate_z(1,2)=0; translate_z(1,3)=0.0f;
    translate_z(2,0)=0; translate_z(2,1)=0; translate_z(2,2)=1; translate_z(2,3)=-_point.z;
    translate_z(3,0)=0.0f; translate_z(3,1)=0.0f; translate_z(3,2)=0.0f; translate_z(3,3)=1.0f;


    transformation(0,0)=tmp0[0]; transformation(0,1)=tmp0[1]; transformation(0,2)=tmp0[2]; transformation(0,3)=0.0f;
    transformation(1,0)=tmp1[0]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp1[2]; transformation(1,3)=0.0f;
    transformation(2,0)=tmp2[0]; transformation(2,1)=tmp2[1]; transformation(2,2)=tmp2[2]; transformation(2,3)=0.0f;
    transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;


    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transformed_cloud1 (new pcl::PointCloud<pcl::PointXYZRGBA>);
    // You can either apply transform_1 or transform_2; they are the same
    pcl::transformPointCloud (*cloud, *transformed_cloud1, translate_z);


    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transformed_cloud2 (new pcl::PointCloud<pcl::PointXYZRGBA>);
    // You can either apply transform_1 or transform_2; they are the same
    pcl::transformPointCloud (*transformed_cloud1, *transformed_cloud2, transformation);


    translate_z(2,3)=_point.z;

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transformed_cloud3 (new pcl::PointCloud<pcl::PointXYZRGBA>);
    // You can either apply transform_1 or transform_2; they are the same
    pcl::transformPointCloud (*transformed_cloud2, *transformed_cloud3, translate_z);

    _point = transformed_cloud3->at(320, 240);

    std::cout << "cloud at point: " << _point << std::endl;


    cv::Mat output_cloud; 
    output_cloud = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0,0,255) ); 

    cv::Mat distance;
    distance = cv::Mat(480, 640, CV_32FC1, -1.2); //::zeros
    
    std::cout << "depth " << distance.at<float>(0,0) << std::endl;


    if (!transformed_cloud3->empty())
        {
        for (int h=0; h<transformed_cloud3->height; h++)
            {
             for (int w=0; w<transformed_cloud3->width; w++)
               {
                    pcl::PointXYZRGBA point = transformed_cloud3->at(w, h);

                    Eigen::Vector3i rgb = point.getRGBVector3i();

                    int x_pos = 320 -  point.x/point.z * 480;
                    int y_pos = 240 +  point.y/point.z * 480;

                    if( x_pos > 0 and x_pos < 640 and y_pos > 0 and y_pos < 480)
                     {

                       if( point.z > distance.at<float>(y_pos,x_pos) and point.z < -0.8 )
                        {


                        output_cloud.at<cv::Vec3b>(y_pos,x_pos)[0] = rgb[2];
                        output_cloud.at<cv::Vec3b>(y_pos,x_pos)[1] = rgb[1];
                        output_cloud.at<cv::Vec3b>(y_pos,x_pos)[2] = rgb[0];

                        distance.at<float>(y_pos,x_pos) = point.z;
                        }
                     }
                 }
             }
        }




    std::cout << " saving output image " << std::endl;
    cv::imwrite( "transformed_image_no_interpolation.png", output_cloud );

    //cv::Mat input_cloud;
    input_cloud = cv::Mat(480, 640, CV_8UC3);

    for (int h=0; h< output_cloud.rows ; h++)
       {
        for (int w=0; w<  output_cloud.cols ; w++)
            {

            cv::Vec3b color = output_cloud.at<cv::Vec3b>(cv::Point(w,h));

            if( !( (int)output_cloud.at<cv::Vec3b>(h, w)[0] == 0 and (int)output_cloud.at<cv::Vec3b>(h, w)[1] == 0 and (int)output_cloud.at<cv::Vec3b>(h, w)[2] == 255)  )
                {
                input_cloud.at<cv::Vec3b>(h, w)[0] = output_cloud.at<cv::Vec3b>(h, w)[0];
                input_cloud.at<cv::Vec3b>(h, w)[1] = output_cloud.at<cv::Vec3b>(h, w)[1];
                input_cloud.at<cv::Vec3b>(h, w)[2] = output_cloud.at<cv::Vec3b>(h, w)[2];

                }
            else
                {
            //	std::cout << " oh god" << std::endl;
                int left_pos = - 1;
                int right_pos =  1;

                while( left_pos + w > 0
                and ( (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[0] == 0 and (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[1] == 0 and (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[2] == 255) )
                    {
                    //std::cout << "ha" << std::endl;
                    left_pos--;
                    }

                while( right_pos + w < 640 -1
                and ( (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[0] == 0 and (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[1] == 0 and (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[2] == 255) )
                    {
                    //std::cout << "ha" << std::endl;
                    right_pos++;
                    }



                if( left_pos  + w >= 0 and right_pos  + w < 640)
                    {
                    if( !( (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[0] == 0 and (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[1] == 0 and (int)output_cloud.at<cv::Vec3b>(h, left_pos + w)[2] == 255)
                    and  !( (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[0] == 0 and (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[1] == 0 and (int)output_cloud.at<cv::Vec3b>(h, right_pos + w)[2] == 255) )
                        {
                        float left_right_weight = -left_pos/right_pos;
                        int pixel_color = (int) output_cloud.at<cv::Vec3b>(h, left_pos + w)[0]/2 + output_cloud.at<cv::Vec3b>(h, right_pos + w)[0]/2 ;

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


    std::cout << " saving output image " << std::endl;
    cv::imwrite( "transformed_image_perspective.png", input_cloud );

    return 0;
}
