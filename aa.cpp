
// to install opencv for c++, run the following command(s):
// sudo apt update
// sudo apt install libopencv-dev

#include <opencv2/opencv.hpp>
#include <iostream>
#include "aa.h"

int main(int argc, char** argv)
{

  cv::Mat input;
  input = cv::imread("src_img/600p.png", CV_LOAD_IMAGE_COLOR);

  if (!input.data)
  {
      std::cout <<  "Error:  Image not found!  Terminating..." << std::endl ;
      return -1;
  }

  // create an empty matrix to hold antialiased image
  cv::Mat aa(input.size().height, input.size().width, CV_8UC3);

  // convert to Lab colorspace
  cv::cvtColor(input, input, cv::COLOR_RGB2Lab);

  cv::Mat* input_p = &input;
  cv::Mat* aa_p = &aa;

  // perform 2xAA (reassign ptr to make it easy to reapply ixAA)
  for (int i = 0; i < 2; i++)
  {
    antialias(input_p, aa_p);
    input_p = aa_p;
  }

  // convert back to RGB colorspace
  cv::cvtColor(aa, aa, cv::COLOR_Lab2RGB);

  cv::imwrite("processed_img/600pAA.png", aa);

  return 0;
}

// performs traversal of matrix 'im' to smooth pixels and stores in 'aa'
void antialias(cv::Mat* im, cv::Mat* aa)
{
  double val = 0;

  // iterate through x and y values, as well as the L*a*b values (c for color)
  for (int y = 1; y < im->size().height-1; y++)
  {

    for (int x = 1; x < im->size().width-1; x++)
    {

      for (int c = 0; c < 3; c++)
      {

        // Amazing formula.  Its really simple too, we just take the average between the (avg of surrounding pixels) & our current pixel
        aa->at<cv::Vec3b>(y,x)[c] = (0.5) * (im->at<cv::Vec3b>(y,x)[c] + (0.25) * (im->at<cv::Vec3b>(y,x+1)[c] + im->at<cv::Vec3b>(y,x-1)[c]
                                     + im->at<cv::Vec3b>(y+1,x)[c] + im->at<cv::Vec3b>(y-1,x)[c]));
      }
    }
  }
}