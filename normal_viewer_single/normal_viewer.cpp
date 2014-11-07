#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

// i want to get the normal vector
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>




int user_data;
    
void 
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere (o, 0.25, "sphere", 0);
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

    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
    //pcl::io::loadPCDFile ("my_point_cloud.pcd", *cloud);
    
    pcl::PointCloud<pcl::PointXYZ> cloud;

    pcl::io::loadPCDFile<pcl::PointXYZ> (argv[1], cloud);

    // Create the normal estimation class, and pass the input dataset to it
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;


    //pcl::IntegralImageNormalEstimation<pcl::PointXYZ, pcl::Normal> ne;

    //ne.setInputCloud(cloud);
    //ne.setNormalSmoothingSize(10);
    ne.setRadiusSearch (0.3);
    //ne.setNormalEstimationMethod(ne.COVARIANCE_MATRIX);

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
    ne.setSearchMethod (tree);

    int colIndex = 320;
    int rowIndex = 240;

    pcl::Normal normal;

    Eigen::Vector4f plane_parameters;
    float curvature;	

    std::vector<int> indices(colIndex,rowIndex);


    pcl::PointXYZ _point = cloud.at(50, 50);
    std::cout << "cloud at point: " << _point << std::endl;
    _point = cloud.at(320, 240);
    std::cout << "cloud at point: " << _point << std::endl;


    float nx, ny, nz;
    ne.computePointNormal (cloud, indices, nx, ny, nz, curvature);
    //pcl::computePointNormal (cloud, indices, plane_parameters, curvature);
    //ne.computePointNormal(colIndex, rowIndex, normal); 
    
    std::cout << "cloud_normal at point: " << nx << " , " << ny << " , " << nz << " curvature " << curvature << std::endl;
	/*
    for(int i = 0; i < 639; i += 2)
	{
    	indices[0] = i;
    	ne.computePointNormal (cloud, indices, nx, ny, nz, curvature);
    //pcl::computePointNormal (cloud, indices, plane_parameters, curvature);
    //ne.computePointNormal(colIndex, rowIndex, normal); 
    
    	std::cout << "cloud_normal at point: " << nx << " , " << ny << " , " << nz << " curvature " << curvature << std::endl;
	}
/*
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);
    
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
*/
    return 0;
}
