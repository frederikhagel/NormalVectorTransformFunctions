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




int user_data;
    
void 
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);

    std::cout << "i only run once" << std::endl;
    
}
    
void 
viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);
    
    //FIXME: possible race condition here:
    user_data++;
}
    
int 
main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile (argv[1], *cloud);
    
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
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
            input_cloud.at<cv::Vec3b>(y_pos,640 - x_pos)[0] = rgb[2];
            input_cloud.at<cv::Vec3b>(y_pos,640 - x_pos)[1] = rgb[1];
            input_cloud.at<cv::Vec3b>(y_pos,640 - x_pos)[2] = rgb[0];

			}

	    }
	}
    }
    std::cout << " showing input image " << std::endl;
    cv::imshow( "test_image_perspective.png", input_cloud );
    //cv::waitKey(0);
 




    // Create an empty kdtree representation, and pass it to the normal estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    pcl::search::KdTree<pcl::PointXYZRGBA>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGBA> ());
    ne.setSearchMethod (tree);

    // Output datasets
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    // Use all neighbors in a sphere of radius 4cm formerly 3
    ne.setRadiusSearch (0.06);

    std::cout << " starting computation " << std::endl;

    // Compute the features
    //ne.compute (*cloud_normals);

    //std::cout << "cloud_normals->points.size (): " << cloud_normals->points.size () << std::endl;


    //pcl::Normal normal_point = cloud_normals->at(320, 240);
    pcl::PointXYZRGBA _point = cloud->at(320, 240);

    //std::cout << "cloud_normal at point: " << normal_point << std::endl;
    //std::cout << "z of cloud at point : " << _point.z << std::endl;

    int colIndex = 320;
    int rowIndex = 240;
    //pcl::Normal normal;
    Eigen::Vector4f plane_parameters;
    float curvature;
//    std::vector<int> indices(colIndex,rowIndex);




    //std::vector<std::vector<int> > k_indices;

    float nx, ny, nz;
    //ne.computePointNormal (*cloud, indices, nx, ny, nz, curvature);
    //ne.computePointNormal (*cloud, indices, plane_parameters, curvature);
    //ne.computePointNormal (320, 240, normal);
    //pcl::flipNormalTowardsViewpoint ( 	_point, 0, 0, 0, plane_parameters);



    pcl::Normal normal;
    for(int i = 0; i < 640; i++){
    std::vector<int> indices(i,rowIndex);
    ne.computePointNormal (*cloud, indices, normal.normal_x, normal.normal_y, normal.normal_z, normal.curvature);
    pcl::flipNormalTowardsViewpoint ( cloud->at(320, 240), cloud->sensor_origin_[0], cloud->sensor_origin_[1], cloud->sensor_origin_[2], normal.normal_x, normal.normal_y, normal.normal_z);


    //std::cout << "cloud_normal at point: " << nx << " , " << ny << " , " << nz << " curvature " << curvature << std::endl;
    std::cout << "cloud_normal at point: " << normal << std::endl;
    }
/*
  Eigen::Vector3f z_axis(normal_point.normal_x,normal_point.normal_y,normal_point.normal_z);

  Eigen::Vector3f y_direction(0,1,0);

  Eigen::Affine3f transform_3;

  pcl::getTransFromUnitVectorsZY (z_axis, y_direction , transform_3);
  transform_3 (0,3) = 0;

  Eigen::Affine3f transformation;

  Eigen::Vector3f tmp0 = (y_direction.cross(z_axis)).normalized();
  Eigen::Vector3f tmp1 = (z_axis.cross(tmp0)).normalized();
  Eigen::Vector3f tmp2 = z_axis.normalized();
  transformation(0,0)=tmp0[0]; transformation(0,1)=tmp0[1]; transformation(0,2)=tmp0[2]; transformation(0,3)=0.0f;
  transformation(1,0)=tmp1[0]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp1[2]; transformation(1,3)=0.0f;
  transformation(2,0)=tmp2[0]; transformation(2,1)=tmp2[1]; transformation(2,2)=tmp2[2]; transformation(2,3)=0.0f;
  transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;
*/
/*



  Eigen::Vector3f z_axis(normal_point.normal_x,normal_point.normal_y,normal_point.normal_z);

  std::cout << "cloud_normal at point: " << z_axis.normalized() << std::endl;

  Eigen::Vector3f x_axis_standard(1,0,0);

  Eigen::Vector3f x_proj = x_axis_standard - x_axis_standard.dot(z_axis)*z_axis; 

  Eigen::Affine3f translate_z;
  Eigen::Affine3f transformation;

  Eigen::Vector3f tmp0 = x_proj.normalized();
  Eigen::Vector3f tmp1 = (z_axis.normalized().cross(x_proj.normalized())).normalized();
  Eigen::Vector3f tmp2 = z_axis.normalized();

  */

/*  translate_z(0,0)=1; translate_z(0,1)=0; translate_z(0,2)=0; translate_z(0,3)=0.0f;
  translate_z(1,0)=0; translate_z(1,1)=1; translate_z(1,2)=0; translate_z(1,3)=0.0f;
  translate_z(2,0)=0; translate_z(2,1)=0; translate_z(2,2)=1; translate_z(2,3)=-_point.z;
  translate_z(3,0)=0.0f; translate_z(3,1)=0.0f; translate_z(3,2)=0.0f; translate_z(3,3)=1.0f;
*/

/*
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
  P_0.push_back (pcl::PointXYZ (-0.5 , 0.5 , 0));
  P_0.push_back (pcl::PointXYZ (-0.5 , -0.5 , 0));
  P_0.push_back (pcl::PointXYZ (0.5 , 0.5 , 0));
  P_0.push_back (pcl::PointXYZ (0.5 , -0.5 , 0));

  float x;
  float y;
  float distance = 1;
  std::vector<cv::Point2f> vector_end;
  for(int i = 0; i < 4; i++)
    {
        x = (-480)* P_0[i].x/(P_0[i].z + distance) + 320;
        y =  (480) * P_0[i].y/(P_0[i].z + distance) + 240;
        vector_end.push_back (cv::Point2f(x,y));
    }

  pcl::PointCloud<pcl::PointXYZ> P_T;


  // You can either apply transform_1 or transform_2; they are the same
  pcl::transformPointCloud (P_0, P_T, transformation);
 
  std::cout << "point 1: x " << P_T[0].x << " y " << P_T[0].y << " z " << P_T[0].z << std::endl;
  std::cout << "point 2: " << P_T[1] << std::endl;
  std::cout << "point 3: " << P_T[2] << std::endl;
  std::cout << "point 4: " << P_T[3] << std::endl;
  std::cout << "point 5: " << P_T[4] << std::endl;
  std::cout << "point 6: " << P_T[5] << std::endl;
  std::cout << "point 7: " << P_T[6] << std::endl;
  std::cout << "point 8: " << P_T[7] << std::endl;
  std::cout << "[ " << P_0[0] << " , " << P_0[1] << " , " << P_0[2] << " , " << P_0[3] << " ]" <<    std::endl;
  std::cout << "[ " << P_T[0] << " , " << P_T[1] << " , " << P_T[2] << " , " << P_T[3] << " ]" <<    std::endl;


  std::vector<cv::Point2f> vector_start;
  for(int i = 0; i < 4; i++)
    {
        x = (-480)* P_T[i].x/(P_T[i].z + distance) + 320;
        y =  (480) * P_T[i].y/(P_T[i].z + distance) + 240;
        vector_start.push_back (cv::Point2f(x,y));
    }

   cv::Mat transform2D = cv::getPerspectiveTransform(vector_start, vector_end);

   cv::Mat output_image;

   cv::warpPerspective(input_cloud, output_image, transform2D, input_cloud.size() );


   cv::imshow("image transformed", output_image);

   cv::waitKey(0);
*/
    return 0;
}
