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


    //blocks until the cloud is actually rendered
    viewer.showCloud(transformed_cloud3);
    
    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer
    
    //This will only get called once
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread (viewerPsycho);
    while (!viewer.wasStopped ())
    {
    //you can also do cool processing here
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...
    user_data++;
    }
    return 0;
}
