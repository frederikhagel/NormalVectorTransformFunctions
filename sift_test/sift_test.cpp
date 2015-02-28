#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d.hpp"

//#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

const double THRESHOLD = 400;

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "Too few arguments" << endl;
    return -1;
  }

  const char* filename1 = argv[1];
  const char* filename2 = argv[2];


  printf("load file:%s\n", filename1);

  // initialize detector and extractor
  cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(300);
  //cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create();
  //cv::Ptr<Feature2D> f2d = ORB::create();
  // you get the picture, i hope..


  Mat originalGrayImage = imread(filename1, IMREAD_GRAYSCALE);
  if (!originalGrayImage.data) {
    cerr << "gray image load error" << endl;
    return -1;
  }

  Mat newGrayImage = imread(filename2, IMREAD_GRAYSCALE);
  if (!newGrayImage.data) {
    cerr << "gray image load error" << endl;
    return -1;
  }

  Mat originalColorImage = imread(filename1, IMREAD_ANYCOLOR|IMREAD_ANYDEPTH);
  if (!originalColorImage.data) {
    cerr << "color image open error" << endl;
    return -1;
  }

  Mat img_1 = originalGrayImage;
  Mat img_2 = newGrayImage;

  //-- Step 1: Detect the keypoints:
  std::vector<KeyPoint> keypoints_1, keypoints_2;
  f2d->detect( img_1, keypoints_1 );
  f2d->detect( img_2, keypoints_2 );

  //-- Step 2: Calculate descriptors (feature vectors)
  Mat descriptors_1, descriptors_2;
  f2d->compute( img_1, keypoints_1, descriptors_1 );
  f2d->compute( img_2, keypoints_2, descriptors_2 );

  //-- Step 3: Matching descriptor vectors using BFMatcher :
  BFMatcher matcher;
  std::vector< DMatch > matches;
  matcher.match( descriptors_1, descriptors_2, matches );

    printf("image1:%zd keypoints are found.\n", keypoints_1.size());

    for (int i=0; i<keypoints_1.size(); i++){
      KeyPoint kp = keypoints_1[i];
      circle(originalColorImage, kp.pt, cvRound(kp.size*0.25), Scalar(255,255,0), 1, 8, 0);
    }
    imshow("mywindow", originalColorImage);

    int c = waitKey(0);


  return 0;
}
