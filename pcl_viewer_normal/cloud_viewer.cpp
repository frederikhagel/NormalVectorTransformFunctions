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



#include <pcl/filters/extract_indices.h>

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




pcl::visualization::PCLVisualizer rgbVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{
  // --------------------------------------------
  // -----Open 3D viewer and add point cloud-----
  // --------------------------------------------
  pcl::visualization::PCLVisualizer viewer ("3D Viewer");
//  viewer.setBackgroundColor (0, 0, 0);

  int v1(0);
//  viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);
//  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
//  viewer.addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
//  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
//  viewer.addCoordinateSystem (1.0);
//  viewer.initCameraParameters ();
  return (viewer);
}

int 
main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);

    pcl::io::loadPCDFile (argv[1], *cloud);

    pcl::io::loadPCDFile (argv[1], *point_cloud_ptr);

//    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
    pcl::visualization::PCLVisualizer viewer("cloud viewer");

//    viewer = rgbVis(point_cloud_ptr);
//  pcl::visualization::PCLVisualizer viewer ("3D Viewer");

        std::cout << "ready1" << std::endl;

//    viewer.spinOnce (100);

    std::cout << "ready" << std::endl;

    pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> ne;
    ne.setInputCloud (cloud);


    std::cout << "set" << std::endl;

pcl::PointCloud<pcl::Normal>::Ptr output(new pcl::PointCloud<pcl::Normal>);


     pcl::search::KdTree<pcl::PointXYZRGBA>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGBA>);
//     pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> ne;

     ne.setInputCloud(cloud->makeShared());
     ne.setSearchMethod(tree);

     ne.setRadiusSearch(0.02);
     ne.setViewPoint(0.0, 0.0, 0.0);


     boost::shared_ptr<std::vector<int> >indices (new std::vector<int> ());

     for( int i = 0; i < 600 - 1; i++)
        indices->push_back( 640*479/2 + i ); //   y * image_color.cols + x

//     indices->push_back( 640*479/2  ); //   y * image_color.cols + x

//     indices->push_back( 640*479/2 + 20 ); //   y * image_color.cols + x

//     indices->push_back( 640*479/2 - 20 ); //   y * image_color.cols + x

//     indices->push_back( 640*479/2 + 40 ); //   y * image_color.cols + x


     ne.setIndices(indices);
     ne.compute(*output);

         pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZRGBA>);

     pcl::ExtractIndices<pcl::PointXYZRGBA> eifilter (true); // Initializing with true will allow us to extract the removed indices
     eifilter.setInputCloud (cloud);
     eifilter.setIndices (indices);
     eifilter.filter (*cloud_out);



     int v1(0);
//     viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);
//     viewer.setBackgroundColor (0, 0, 0, v1);
//     viewer.addText("Radius: 0.01", 10, 10, "v1 text", v1);
//     pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(*const cloud);


//     viewer.addPointCloud<pcl::PointXYZRGB> (hej, "sample cloud1", v1);

       pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(point_cloud_ptr);
       viewer.addPointCloud<pcl::PointXYZRGB> (point_cloud_ptr, rgb, "sample cloud");
//       viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");

     viewer.addPointCloudNormals<pcl::PointXYZRGBA, pcl::Normal>(cloud_out, output, 10, 0.1, "normals");

//    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_COLOR, 1.0, 1.0, 0.5, "normals");


    //blocks until the cloud is actually rendered
//    viewer.showCloud(cloud);
    
//    //use the following functions to get access to the underlying more advanced/powerful
//    //PCLVisualizer
    
//    //This will only get called once
//    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
//    //This will get called once per visualization iteration
//    viewer.runOnVisualizationThread (viewerPsycho);
//    while (!viewer.wasStopped ())
//    {
//    //you can also do cool processing here
//    //FIXME: Note that this is running in a separate thread from viewerPsycho
//    //and you should guard against race conditions yourself...
//    user_data++;
//    }

    std::cout << "Finished" << std::endl;


    while (!viewer.wasStopped ())
    {
      viewer.spinOnce (10000);
      boost::this_thread::sleep (boost::posix_time::microseconds (1000));
    }

    return 0;
}
