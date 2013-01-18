#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <iostream>

std::vector< cv::Point > contour( cv::Mat& img )
{
  std::vector< std::vector< cv::Point > > contours;

  cv::findContours( img, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE );

  double largest = 0.;

  std::vector< cv::Point > largestContour;

  for(size_t i=0; i < contours.size(); i++)
    {
    double t = cv::contourArea(contours[i], false );

    if(largest < t)
      {
      largest = t;
      largestContour=contours[i];
      }
    }

  return largestContour;
}

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat img = cv::imread( argv[1], 0 );
  if( !img.data )
    {
    std::cerr <<"can't open this image" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat dest;
  cv::threshold( img, dest, 128, 255, cv::THRESH_BINARY );

  std::vector< cv::Point > output = contour( dest );

  for( size_t i = 0; i < output.size(); i++ )
    {
    std::cout << output[i] << std::endl;
    }

  return EXIT_SUCCESS;
}
