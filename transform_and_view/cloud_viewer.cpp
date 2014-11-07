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
    std::cout << "cloud at point: " << _point << std::endl;


  Eigen::Vector3f z_axis(normal_point.normal_x,normal_point.normal_y,normal_point.normal_z);

  Eigen::Vector3f y_direction(1,1,1);

  Eigen::Affine3f transform_3;

  pcl::getTransFromUnitVectorsZY (z_axis, y_direction , transform_3);

  transform_3 (0,3) = 0;

  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
  // You can either apply transform_1 or transform_2; they are the same
  pcl::transformPointCloud (*cloud, *transformed_cloud, transform_3);


    //blocks until the cloud is actually rendered
    viewer.showCloud(transformed_cloud);
    
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
