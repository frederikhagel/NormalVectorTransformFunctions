#include <pcl/visualization/cloud_viewer.h>
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
#include <pcl/filters/normal_refinement.h>
#include <pcl/registration/correspondence_rejection.h>




#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/registration/ia_ransac.h>


//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include "transform.hpp"

transform::transform(){}

transform::~transform(){}

cv::Mat transform::transform_image(cv::Mat image_color, cv::Mat image_depth, int x, int y)
{

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>(image_color.cols, image_color.rows));

    std::cout << image_color.cols << " " << image_color.rows << std::endl;

    for (int h=0; h<image_color.cols; h++) {
        for (int w=0; w<image_color.rows; w++) {

            int hc = image_color.cols -h - 1;

            cloud->at(hc,w).b = image_color.at<cv::Vec3b>(w,h)[0];
            cloud->at(hc,w).g = image_color.at<cv::Vec3b>(w,h)[1];
            cloud->at(hc,w).r = image_color.at<cv::Vec3b>(w,h)[2];
            cloud->at(hc,w).a = 1;

            cloud->at(hc,w).x = float( (h - image_color.cols/2)/1000.0 );
            cloud->at(hc,w).y = float( (-w + image_color.rows/2)/1000.0 );
            cloud->at(hc,w).z = - float(  image_depth.at<int16_t>(w,h) ) /1000;

        }
    }

    pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> ne;
    ne.setInputCloud (cloud);

    cv::Mat input_cloud; 
    input_cloud = cv::Mat(cloud->height,cloud->width,CV_8UC3);

    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    // Use all neighbors in a sphere of radius 4cm formerly 3
    ne.setRadiusSearch (0.02);


    //pcl::Normal normal_point = cloud_normals->at(320, 240);
    pcl::PointXYZRGBA _point = cloud->at( x, y );

    //std::cout << "cloud_normal at point: " << normal_point << std::endl;
    std::cout << "z of cloud at point : " << _point.x << " , " << _point.y << " , " << _point.z << std::endl;

    pcl::Normal normal;
    boost::shared_ptr<std::vector<int> >indices (new std::vector<int> (1,y * image_color.rows + x));

    ne.setIndices(indices);

    ne.compute (*cloud_normals);

    pcl::flipNormalTowardsViewpoint ( cloud->at(x, y), cloud->sensor_origin_[0], cloud->sensor_origin_[1], cloud->sensor_origin_[2], normal.normal_x, normal.normal_y, normal.normal_z);

    std::cout << "cloud_normal at point: " << cloud_normals->at( 0 ) << std::endl;

    Eigen::Vector3f z_axis(cloud_normals->at( 0 ).normal_x,cloud_normals->at( 0 ).normal_y,cloud_normals->at( 0 ).normal_z);

    std::cout << "cloud_normal at point: " << z_axis.normalized() << std::endl;

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


    transformation(0,0)=tmp0[0]; transformation(0,1)=tmp1[0]; transformation(0,2)=tmp2[0]; transformation(0,3)=0.0f;
    transformation(1,0)=tmp0[1]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp2[1]; transformation(1,3)=0.0f;
    transformation(2,0)=tmp0[2]; transformation(2,1)=tmp1[2]; transformation(2,2)=tmp2[2]; transformation(2,3)=0.0f;
    transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;

    pcl::PointCloud<pcl::PointXYZ> P_0;

    P_0.push_back (pcl::PointXYZ (1 , 1 , 0));
    P_0.push_back (pcl::PointXYZ (1 , -1 , 0));
    P_0.push_back (pcl::PointXYZ (-1 , -1 , 0));
    P_0.push_back (pcl::PointXYZ (-1 , 1 , 0));

    float xProj;
    float yProj;
    float distance = 1;
    std::vector<cv::Point2f> vector_end;
    for(int i = 0; i < 4; i++)
    {
        xProj = (-580)* P_0[i].x/(P_0[i].z + distance) + input_cloud.cols/2;
        yProj =  (580) * P_0[i].y/(P_0[i].z + distance) + input_cloud.rows/2;
        vector_end.push_back (cv::Point2f(xProj,yProj));
    }

    pcl::PointCloud<pcl::PointXYZ> P_T;

    // You can either apply transform_1 or transform_2; they are the same
    pcl::transformPointCloud (P_0, P_T, transformation);

    std::cout << "[ " << P_0[0] << " , " << P_0[1] << " , " << P_0[2] << " , " << P_0[3] << " ]" <<    std::endl;
    std::cout << "[ " << P_T[0] << " , " << P_T[1] << " , " << P_T[2] << " , " << P_T[3] << " ]" <<    std::endl;

    std::vector<cv::Point2f> vector_start;
    for(int i = 0; i < 4; i++)
    {
        xProj = (-580)* P_T[i].x/(P_T[i].z + distance) + input_cloud.cols/2;
        yProj =  (580) * P_T[i].y/(P_T[i].z + distance) + input_cloud.rows/2;
        vector_start.push_back (cv::Point2f(xProj,yProj));
    }

    cv::Mat transform2D = cv::getPerspectiveTransform(vector_start, vector_end);
    std::cout << transform2D.shape << std::endl;
    cv::Mat output_image;
    cv::warpPerspective(image_color, output_image, transform2D, input_cloud.size() );

    return output_image;
}
