
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "processing.h"

using namespace cv;

void process_bin_erode_dilate(Mat img, const char* window_name)
{
  int level = 77;
  int erodeSz  = 6;
  int dilateSz = 6;
  
  threshold(img,img,level,255,THRESH_BINARY);
  // imshow(window_name, img);
  // waitKey(0);

  Mat erodeElement  = getStructuringElement(MORPH_ELLIPSE, Size(2*erodeSz+1,2*erodeSz+1));
  Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(2*dilateSz+1,2*dilateSz+1));

  erode(img, img, erodeElement);
  // imshow(window_name, img);
  // waitKey(0);

//  dilate(img,img,dilateElement);
  // imshow(window_name, img);
  // waitKey(0);

//  dilate(img,img,dilateElement);
  // imshow(window_name, img);
  // waitKey(0);
}
