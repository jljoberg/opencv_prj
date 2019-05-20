
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void process_image(Mat img, const char* window_name)
{
  int level = 77;
  int erodeSz  = 6;
  int dilateSz = 8;
  
  threshold(img,img,level,255,THRESH_BINARY);
  imshow(window_name, img);
  waitKey(0);

  Mat erodeElement  = getStructuringElement(MORPH_ELLIPSE, Size(2*erodeSz+1,2*erodeSz+1));
  Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(2*dilateSz+1,2*dilateSz+1));

  erode(img, img, erodeElement);
  imshow(window_name, img);
  waitKey(0);

  dilate(img,img,dilateElement);
  imshow(window_name, img);
  waitKey(0);

  dilate(img,img,dilateElement);
  imshow(window_name, img);
  waitKey(0);
}

int main(int argc, char**argv){
  if(argc != 2)
  {
    cout << "Usage: DetectBuoy ImageToLoadAndDisplay\n";
    return -1;
  }

  const char* window_name = "Display window";

  Mat img_orig = imread(argv[1], IMREAD_GRAYSCALE);
  Mat img_proc = img_orig.clone();

  if(!img_orig.data)
  {
    cout << "Could not open or find the image\n";
    return -1;
  }

  namedWindow( window_name, WINDOW_AUTOSIZE );
  imshow(window_name, img_orig);
  waitKey(0);

  process_image(img_proc, window_name);

  return 0;
}

      

