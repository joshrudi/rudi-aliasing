
// to install opencv for c++, run the following command(s):
// sudo apt update
// sudo apt install libopencv-dev

#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{

  cv::Mat input;
  input = cv::imread("src_img/1080p.png", CV_LOAD_IMAGE_COLOR);

  if (!input.data)
  {
      std::cout <<  "Error:  Image not found!  Terminating..." << std::endl ;
      return -1;
  }

  cv::Mat* output = antialias(&input);

  cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display window", *output );

  cv::waitKey(0);
  return 0;
}

// performs traversal of matrix 'im' and smooths pixels
cv::Mat* antialias(cv::Mat* im)
{

  // create an empty matrix to hold antialiased image
  cv::Mat aa(im->size().height, im->size().width, CV_8UC3);

  for (int y = 0; y < im->size().height; y++)
  {

    for (int x = 0; x < im->size().width; x++)
    {

      for (int c = 0; c < 3; c++)
      {

        // Amazing formula.  Its really simple too, we just take the average between the (avg of surrounding pixels) & our current pixel
        aa.at<cv::Vec3b>(y,x)[c] = 1/2 * (im->at<cv::Vec3b>(y,x)[c] + 1/4 * (im->at<cv::Vec3b>(y,x+1)[c] + im->at<cv::Vec3b>(y,x-1)[c]
                                     + im->at<cv::Vec3b>(y+1,x)[c] + im->at<cv::Vec3b>(y-1,x)[c]));
        
      }
    }
  }
}