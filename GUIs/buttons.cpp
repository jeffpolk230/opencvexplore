#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat img, hsvimg, temp, se;
int trackbarVal;
int hue_min = 105;
int hue_max = 110;
char* window_name = "GUI from Opencv";

void trackbarCallback(int , void*);
void morphOpenCB(int , void*);
void morphCloseCB(int , void*);
void HSV_extraction(int, void*);

int main(int argc, char **argv)
{
  img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  if (!img.data)
  {
    cout << "image.data failure" << endl;
    return -1;
  }
  namedWindow( window_name, CV_WINDOW_NORMAL);
  cvtColor(img, hsvimg, CV_RGB2HSV); // Take the HSV we need for extraction
  se = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(-1,-1));


  createTrackbar("HueMin: 0 to 180", window_name, &hue_min, 18, HSV_extraction);
  createTrackbar("HueMax: 0 to 180", window_name, &hue_max, 18, HSV_extraction);
  createTrackbar("ShowOriginal", window_name, NULL, 0, trackbarCallback); //ori img
  createTrackbar("MorphOpen", window_name, NULL, 0, morphOpenCB); //performs a morph open on Mat temp and show
   createTrackbar("MorphClose", window_name, NULL, 0, morphCloseCB); //performs a morph open on Mat temp and show


  // init callback
  HSV_extraction(0,0); 
  trackbarCallback(0,0);

  waitKey(0); //wait forever
  return 0;

}

void morphOpenCB(int , void*)
{
  morphologyEx(temp, temp, MORPH_OPEN, se);
  imshow( window_name, temp);
}

void morphCloseCB(int , void*)
{
  morphologyEx(temp, temp, MORPH_CLOSE, se);
  imshow( window_name, temp);
}

void trackbarCallback(int ,void*)
{
  imshow(window_name, img);
}

void HSV_extraction(int, void*)
{
  inRange(hsvimg, Scalar(hue_min*10, 0, 0), Scalar(hue_max*10,255,255), temp);
  imshow(window_name, temp);
}
