#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

#include <iostream>
#include <chrono>

#include "methods/processing.h"


using namespace cv;
using namespace std;


void undist(Mat &img)
{
  Size newSize = Size(1900,1900);
  Mat dst;
  float fx = 961.7226;
  float fy = 962.7481;
  float cx = 649.1621;
  float cy = 488.2451;
  float k1 = -0.4081;
  float k2 = 0.1515;
    
  Mat intrinsic = (Mat1d(3,3) << fx,0,cx, 0,fy,cy, 0,0,1);
  Mat dist      = (Mat1d(1,4) << k1,k2, 0,0);
  //Mat dist = (Mat1d(1,4) << 100,10000,10,10);

  Mat newIntrinsic = getOptimalNewCameraMatrix(intrinsic, dist, img.size(), 1, newSize);
  undistort(img,dst,intrinsic,dist,newIntrinsic);
  cout << "original size " << img.size() << endl;
  cout << "new size " << dst.size() << endl;
  img = dst.clone();
}


int main(int argc, char** argv)
{
  if(argc != 2)
  {
    cout << "Usage: ./[name] directory\n"; 
    return -1;
  }
  const char* window_name = "Display window";
  namedWindow(window_name, WINDOW_AUTOSIZE);
  cout << "Defining display window\n";

  cv::String imDir = argv[1];
  vector<cv::String> files;
  cv::glob(imDir, files);
  cout << files.size() << " files in directory\n";

  for(int i=1500; i<files.size(); i++)
  {
    cv::String file = files[i];
    if(!((file.find("im_")==cv::String::npos) | (file.find(".bmp")==cv::String::npos)))
    {
      Mat img_color = imread(file, IMREAD_COLOR);
      Mat img_orig = imread(file, IMREAD_GRAYSCALE);

      undist(img_orig);
      imshow(window_name, img_color);

      Mat img = img_orig.clone();
      //auto t0 = std::chrono::high_resolution_clock::now();
      //process_bin_erode_dilate(img, window_name);
      //auto t1 = std::chrono::high_resolution_clock::now();
      //cout << "Processing time: "
      //     << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " ms\n";

      vector<vector<Point>> blobPts;
      vector<Vec4i> hierarchy;
      Mat centroids, blobs;
      Mat blobStats;
      int nBlobs = connectedComponentsWithStats(img, blobs, blobStats, centroids, 4, CV_32S);
      //findContours(img, blobPts, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));
//      cvtColor(img_orig, img_color, COLOR_GRAY2RGB);
      for(int label = 1; label<nBlobs; label++)
      {
      auto t0 = std::chrono::high_resolution_clock::now();
        if( blobStats.at<int>(label, CC_STAT_AREA) > 10000)
          continue;
        //int t =blobStats(label,CC_STAT_TOP);
        Point topLeft(blobStats.at<int>(label, CC_STAT_LEFT), blobStats.at<int>(label,CC_STAT_TOP));
        Point botRight( blobStats.at<int>(label,CC_STAT_LEFT)+blobStats.at<int>(label,CC_STAT_WIDTH)-1,
                        blobStats.at<int>(label,CC_STAT_TOP)+blobStats.at<int>(label,CC_STAT_HEIGHT)-1);
        //Rect bbox = boundingRect(blobPts[label]);

        Rect bbox = boundingRect(vector<Point>{topLeft, botRight});
        
        vector<Vec3f> circles;
        Mat roi = img_orig(bbox);
        HoughCircles(roi,circles, HOUGH_GRADIENT, 1, 150,100,30,7,70);
        for(int circleNum=0; circleNum < circles.size(); circleNum ++)
        {
          int radius = cvRound(circles[circleNum][2]);
          if(radius < 4)
            continue;
          Point center(cvRound(circles[circleNum][0]),cvRound(circles[circleNum][1]) );
          circle(img_color,center+bbox.tl(),radius, Scalar(0,0,255),3,8,0);
          //cout << "Circle is found, radius = " << radius <<"\n";
        }

        //rectangle(img_color, topLeft, botRight, Scalar(0,255,0), 2,8,0); 
        //rectangle(img_color, bbox.tl(), bbox.br(), Scalar(0,255,0), 2,8,0); 
      auto t1 = std::chrono::high_resolution_clock::now();
      cout << "Processing time: "
           << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " ms\n";

      }

      cvtColor(img,img,COLOR_GRAY2RGB);
      //img_color = img_color*img ;
      //img_color = (img_color + img_color.mul(img/(255)) )/2;
      img_color = (img_color*0.4+img*1.2);
      //imshow(window_name, img_color);
      waitKey(1);
    }
  }

}


