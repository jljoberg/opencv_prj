
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/aruco.hpp>

#include <iostream>
#include <string>

using namespace cv;

using namespace std;

int main(int argc, char**argv){
  if(argc != 2)
  {
    cout << "Usage: display_image ImageToLoadAndDisplay\n";
    return -1;
  }

  Mat image, img;
  image = imread(argv[1], IMREAD_COLOR);
  
  if(!image.data)
  {
    cout << "Could not open or find the image\n";
    return -1;
  }
  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow("Display window", image);


  waitKey(0);
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);
  
  waitKey(0);
  
  /*
    image.copyTo(img);

    std::cout << "size: " << img.size << std::endl;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;

    std::cout <<"About to set param\n";
    cv::Ptr<cv::aruco::DetectorParameters> parameters;

    std::cout <<"About to get dict\n";
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    std::vector<int> markerIds;

    std::cout <<"About to detect\n";

    cv::Mat emtpy_img;
    cv::aruco::detectMarkers(image, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
*/

  return 0;
}

      

