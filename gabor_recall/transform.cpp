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

#include <pcl/filters/extract_indices.h>


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

std::vector<cv::Mat> transform::transform_image(cv::Mat image_color, cv::Mat image_depth,  std::vector<int> xList, std::vector<int> yList) //int x, int y) //
{

    // blur depth image

    cv::medianBlur(image_depth, image_depth, 5);


    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>(image_color.cols, image_color.rows));



//    std::cout << "Image size " << image_color.cols << " " << image_color.rows << std::endl;

    float focal_lenght = 1050;

    for (int h=0; h<image_color.cols; h++) {
        for (int w=0; w<image_color.rows; w++) {

//            int hc = image_color.cols -h - 1;

            cloud->at(h,w).b = image_color.at<cv::Vec3b>(w,h)[0];
            cloud->at(h,w).g = image_color.at<cv::Vec3b>(w,h)[1];
            cloud->at(h,w).r = image_color.at<cv::Vec3b>(w,h)[2];
//            cloud->at(h,w).a = 1;

            cloud->at(h,w).z = - float(  image_depth.at<int16_t>(w,h) ) /1000;

            float z_focal = - 1000 * cloud->at(h,w).z / focal_lenght;

            cloud->at(h,w).x = float( (h - image_color.cols/2)/1000.0 ) * z_focal;
            cloud->at(h,w).y = float( (-w + image_color.rows/2)/1000.0 ) * z_focal;


        }
    }


    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
    ne.setInputCloud (cloud);

    cv::Mat input_cloud; 
    input_cloud = cv::Mat(cloud->height,cloud->width,CV_8UC3);

    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    // Use all neighbors in a sphere of radius 4cm formerly 3
    ne.setRadiusSearch (0.04);



//    boost::shared_ptr<std::vector<int> >indices (new std::vector<int> (1, y * image_color.cols + x ));


    boost::shared_ptr<std::vector<int> >indices (new std::vector<int> ());

    for(int i = 0; i < xList.size(); i++)
    {
        int x = xList[i];
        int y = yList[i];

        indices->push_back( ( y * image_color.cols + x ) ); //   y * image_color.cols + x
        //        indices->push_back( ( image_color.rows/2 * image_color.cols + image_color.cols/2 + 10 ) ); //   y * image_color.cols + x
//                indices->push_back( y * image_color.cols + x  ); //


    }


//        std::cout << "Indices " << indices->size() << std::endl;

//        pcl::visualization::PCLVisualizer viewer("Reconstructed Pointcloud");

//    //    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr = cloud;

//        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZRGB>);

//        pcl::ExtractIndices<pcl::PointXYZRGB> eifilter (true); // Initializing with true will allow us to extract the removed indices
//        eifilter.setInputCloud (cloud);
//        eifilter.setIndices (indices);
//        eifilter.filter (*cloud_out);

//        pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
//        viewer.addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");


        ne.setIndices(indices);
        ne.compute (*cloud_normals);
//        viewer.addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal>(cloud_out, cloud_normals, 1, 0.1, "normals");

//        viewer.spinOnce (10000);



//    pcl::flipNormalTowardsViewpoint ( cloud->at( y * image_color.cols + x ), cloud->sensor_origin_[0], cloud->sensor_origin_[1], cloud->sensor_origin_[2], normal.normal_x, normal.normal_y, normal.normal_z);

  //  std::cout << "cloud_normal at point: " << cloud_normals->at( 0 ) << std::endl;

    std::vector<cv::Mat> transformed_images;

    for( int i = 0; i < cloud_normals->size(); i++ )
    {
        int x = xList[i];
        int y = yList[i];




        //pcl::Normal normal_point = cloud_normals->at(320, 240);
        pcl::PointXYZRGB _point = cloud->at( ( y * image_color.cols + x )   ); //




        Eigen::Vector3f z_axis(cloud_normals->at( i ).normal_x,cloud_normals->at( i ).normal_y,cloud_normals->at( i ).normal_z);
        pcl::flipNormalTowardsViewpoint ( _point , cloud->sensor_origin_[0], cloud->sensor_origin_[1], cloud->sensor_origin_[2], z_axis[0], z_axis[1], z_axis[2]); // cloud->at( y * image_color.cols + x )


        Eigen::Vector3f x_axis_standard(1,0,0);
        Eigen::Vector3f x_proj = x_axis_standard - x_axis_standard.dot(z_axis)*z_axis;

        Eigen::Vector3f y_axis_standard(0,1,0);
        Eigen::Vector3f y_proj = y_axis_standard - y_axis_standard.dot(z_axis)*z_axis;

        Eigen::Affine3f translate_z;
        Eigen::Affine3f transformation;


        Eigen::Vector3f z_axis_standard(0,0,1);



        Eigen::Vector3f tmp0 = x_proj.normalized();
        Eigen::Vector3f tmp1 = (z_axis.normalized().cross(x_proj.normalized())).normalized();
//        Eigen::Vector3f tmp1 = y_proj.normalized();
        Eigen::Vector3f tmp2 = z_axis.normalized();



        /**  **/

//        translate_z(0,0)=1; translate_z(0,1)=0; translate_z(0,2)=0; translate_z(0,3)=0.0f;
//        translate_z(1,0)=0; translate_z(1,1)=1; translate_z(1,2)=0; translate_z(1,3)=0.0f;
//        translate_z(2,0)=0; translate_z(2,1)=0; translate_z(2,2)=1; translate_z(2,3)=-_point.z;
//        translate_z(3,0)=0.0f; translate_z(3,1)=0.0f; translate_z(3,2)=0.0f; translate_z(3,3)=1.0f;

//        transformation(0,0)=tmp0[0]; transformation(0,1)=tmp0[1]; transformation(0,2)=tmp0[2]; transformation(0,3)=0.0f;
//        transformation(1,0)=tmp1[0]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp1[2]; transformation(1,3)=0.0f;
//        transformation(2,0)=tmp2[0]; transformation(2,1)=tmp2[1]; transformation(2,2)=tmp2[2]; transformation(2,3)=-0.5;
//        transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;


//        pcl::visualization::PCLVisualizer viewer("Reconstructed Pointcloud");
//        viewer.addCoordinateSystem (1.0);

//        pcl::PointCloud<pcl::PointXYZRGB>::Ptr warp_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

//        pcl::transformPointCloud (*cloud, *warp_cloud, translate_z);
//        pcl::transformPointCloud (*warp_cloud, *warp_cloud, transformation);

//        pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(warp_cloud);
//        viewer.addPointCloud<pcl::PointXYZRGB> (warp_cloud, rgb, "sample cloud");

//        viewer.spinOnce (5000);







        /** **/
        //        transformation(0,0)=tmp0[0]; transformation(0,1)=tmp0[1]; transformation(0,2)=tmp0[2]; transformation(0,3)=0.0f;
        //        transformation(1,0)=tmp1[0]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp1[2]; transformation(1,3)=0.0f;
        //        transformation(2,0)=tmp2[0]; transformation(2,1)=tmp2[1]; transformation(2,2)=tmp2[2]; transformation(2,3)=-0.5;
        //        transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;

        transformation(0,0)=tmp0[0]; transformation(0,1)=tmp1[0]; transformation(0,2)=tmp2[0]; transformation(0,3)=0.0f;
        transformation(1,0)=tmp0[1]; transformation(1,1)=tmp1[1]; transformation(1,2)=tmp2[1]; transformation(1,3)=0.0f;
        transformation(2,0)=tmp0[2]; transformation(2,1)=tmp1[2]; transformation(2,2)=tmp2[2]; transformation(2,3)=0.0f;
        transformation(3,0)=0.0f; transformation(3,1)=0.0f; transformation(3,2)=0.0f; transformation(3,3)=1.0f;


        pcl::PointCloud<pcl::PointXYZ> P_0;

//        P_0.push_back (pcl::PointXYZ (0.2 - _point.x , 0.2 - _point.y , 0));
//        P_0.push_back (pcl::PointXYZ (0.2 - _point.x , -0.2 - _point.y , 0));
//        P_0.push_back (pcl::PointXYZ (-0.2 - _point.x, -0.2 - _point.y , 0));
//        P_0.push_back (pcl::PointXYZ (-0.2 - _point.x, 0.2 - _point.y, 0));
        P_0.push_back (pcl::PointXYZ (0.2 , 0.2 , 0));
        P_0.push_back (pcl::PointXYZ (0.2 , -0.2  , 0));
        P_0.push_back (pcl::PointXYZ (-0.2 , -0.2  , 0));
        P_0.push_back (pcl::PointXYZ (-0.2 , 0.2 , 0));




        float distance = 0.8;

//        float distance = -_point.z;


        std::vector<cv::Point2f> vector_end;
        for(int i = 0; i < 4; i++)
        {

            float z_focal = distance / focal_lenght;

            float xProj = P_0[i].x/( z_focal ) + input_cloud.cols/2;
            float yProj = - P_0[i].y/( z_focal ) +  input_cloud.rows/2;
            vector_end.push_back (cv::Point2f(xProj,yProj));

            std::cout << P_0[i].x << " " << P_0[i].y << " " << xProj << " " << yProj << std::endl;

        }

        pcl::PointCloud<pcl::PointXYZ> P_T;


        pcl::transformPointCloud (P_0, P_T, transformation);

        //
//        std::cout << "[ " << P_0[0] << " , " << P_0[1] << " , " << P_0[2] << " , " << P_0[3] << " ]" <<    std::endl;
//        std::cout << "[ " << P_T[0] << " , " << P_T[1] << " , " << P_T[2] << " , " << P_T[3] << " ]" <<    std::endl;


//        distance = -_point.z;

        // Use the points position.


        std::vector<cv::Point2f> vector_start;

        for(int i = 0; i < 4; i++)
        {

            float z_focal = ( -P_T[i].z - _point.z ) / focal_lenght;

            float xProj =  ( _point.x + P_T[i].x)/(  z_focal)   +  input_cloud.cols/2; // x
            float yProj = - ( _point.y + P_T[i].y)/( z_focal)  +  input_cloud.rows/2; // y
            vector_start.push_back (cv::Point2f(xProj,yProj));

            std::cout << P_T[i].x << " " << P_T[i].y << " " << P_T[i].z << " " << xProj << " " << yProj << std::endl;

        }

//        for(int i = 0; i < 4; i++)
//        {

//            float z_focal = ( -P_T[i].z + distance ) / focal_lenght;

//            float xProj =  P_T[i].x/(  z_focal)   +  input_cloud.cols/2; // x
//            float yProj = -  P_T[i].y/( z_focal)  +  input_cloud.rows/2; // y
//            vector_start.push_back (cv::Point2f(xProj,yProj));

//            std::cout << P_T[i].x << " " << P_T[i].y << " " << P_T[i].z << " " << xProj << " " << yProj << std::endl;

//        }

        cv::Mat transform2D = cv::getPerspectiveTransform(vector_start, vector_end);
        //
        std::cout << transform2D << std::endl;
//        std::cout << input_cloud.size() << std::endl;


        std::cout << "Position in image " << x << " , " << y << std::endl;
        //std::cout << "cloud_normal at point: " << normal_point << std::endl;
        std::cout << "Position of point : " << _point.x << " , " << _point.y << " , " << _point.z << std::endl;
        std::cout << "Normal vector: " << z_axis[0] << " , " <<  z_axis[1] << " , " << z_axis[2] << std::endl;
        std::cout << "angle: " << ( acos(z_axis_standard.dot(z_axis) )  /3.14 )*180 << std::endl;

        std::cout << std::endl;
        cv::Mat output_image;
//        output_image = image_color;//
        cv::warpPerspective(image_color, output_image, transform2D, input_cloud.size() );



        /** **/

//        std::vector<cv::Point2f> orig;
//        orig.push_back( cv::Point2f( x, y ) );
//        std::vector<cv::Point2f>  of;

//        cv::perspectiveTransform(orig, of, transform2D );


//        cv::Point2f srcTri[3];
//        cv::Point2f dstTri[3];

//        cv::Mat warp_mat( 2, 3, CV_32FC1 );

////        warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

//        //Affine Transform: As we explained lines above, we need two sets of 3 points to derive the affine transform relation. Take a look:

//        srcTri[0] = cv::Point2f( of[0].x , of[0].y );
//        srcTri[1] = cv::Point2f( of[0].x + 100, of[0].y + 100);
//        srcTri[2] = cv::Point2f( of[0].x , of[0].y + 100 );

////        srcTri[0] = cv::Point2f( x, y);
////        srcTri[1] = cv::Point2f( (x + 100) * (0.8/(-_point.z) ), (y + 100) * (0.8/(-_point.z) ));
////        srcTri[2] = cv::Point2f( x , (y +100 ) * (0.8/(-_point.z) ));


//        dstTri[0] = cv::Point2f( input_cloud.cols/2 , input_cloud.rows/2 );
//        dstTri[1] = cv::Point2f( input_cloud.cols/2 + 100, input_cloud.rows/2 + 100);
//        dstTri[2] = cv::Point2f( input_cloud.cols/2 , input_cloud.rows/2 + 100 );

//        //You may want to draw the points to make a better idea of how they change. Their locations are approximately the same as the ones depicted in the example figure (in the Theory section). You may note that the size and orientation of the triangle defined by the 3 points change.

//        //Armed with both sets of points, we calculate the Affine Transform by using OpenCV function getAffineTransform:

//        warp_mat = cv::getAffineTransform( srcTri, dstTri );

//        //We get as an output a 2 \times 3 matrix (in this case warp_mat)

//        //We apply the Affine Transform just found to the src image

////        cv::imshow("Non warped", image_color);
////        cv::waitKey();

//        cv::Mat warped_image;

//        cv::warpAffine( output_image, output_image, warp_mat, image_color.size() );

////        cv::imshow("Warped", warped_image);
////        cv::waitKey();

        /** **/

        transformed_images.push_back(  output_image );


//        cv::imshow("Non warped", image_color);


////        cv::imshow("Warped", warped_image);

//        cv::imshow("Warped3D", output_image);
//        cv::waitKey();

    }



    return transformed_images;
}
