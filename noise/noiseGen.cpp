/*
  Take in one picture from argv[1] as grayscale and create some salt and peper noise
  TODO: clean up methods, write s&p noise + Gaussian noise into small lib
 */

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
char* window_name= "Noisy Image";

//Headers 
Mat saltAndPepper(Mat, int, int);

int main(int argc, char **argv)
{
  Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  namedWindow(window_name, CV_WINDOW_NORMAL);
  Mat noisymask = img.clone();
  Mat output;
  randn(noisymask, 128, 30); //alpha value = 3rd arg
  add(img, noisymask, output); // this output Gaussian noised image
  Mat sAndp = saltAndPepper(img, 10, 245);
  imshow(window_name, output);
  imshow("salt and pepper", sAndp);
  Mat se = getStructuringElement(MORPH_ELLIPSE,Size(3, 3) ,Point(-1,-1));
  morphologyEx(sAndp, sAndp, MORPH_OPEN, se);
  morphologyEx(sAndp, sAndp, MORPH_CLOSE, se);
  imshow("Morph open and closed", sAndp);
  waitKey(0);
  return 0;
}

// take input image and returns salted and peppered image; take two thresholds for B&W
Mat saltAndPepper(Mat input, int blackThres, int whiteThres)
{
  Mat saltpepper_noise = Mat::zeros(input.rows, input.cols,CV_8U);
  randu(saltpepper_noise,0,255);

  Mat black = saltpepper_noise < blackThres;
  Mat white = saltpepper_noise > whiteThres;

  Mat saltpepper_img = input.clone();
  saltpepper_img.setTo(255,white);
  saltpepper_img.setTo(0,black);
  return saltpepper_img;
}
