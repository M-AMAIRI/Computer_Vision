// create_MASK.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat AppMsK(string MaskFilePath, string OrigFilePath)
{

	Mat frame, mask;
	// Load an image using imread
	frame = imread(OrigFilePath, CV_LOAD_IMAGE_UNCHANGED);   // Read the file
	mask = imread(MaskFilePath, CV_LOAD_IMAGE_UNCHANGED);   // Read the mask file
	cv::threshold(mask, mask, 100, 255, cv::THRESH_BINARY);
	cvtColor(mask, mask, COLOR_BGR2GRAY); // Convert the image to Gray
	imshow("mask", mask);
	imshow("before", frame);
	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{
			if (mask.at<uchar>(i, j) == 0)
			{
				Point3_<uchar>* p = frame.ptr<Point3_<uchar> >(i, j);
				p->x = 255;
				p->y = 255;
				p->z = 255;
			}
		}
	}
	imshow("after", frame);
	return frame;
}


int main() {

	    // apply the transformation  
		Mat im = AppMsK("costumMask.png","im.png");

		// Save your transformed image in a file on disk
		imwrite("image.png",im);

	return 0;
}
