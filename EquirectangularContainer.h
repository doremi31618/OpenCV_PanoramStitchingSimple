#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching/detail/warpers.hpp>

#pragma once
using namespace cv;
using namespace std;

struct EquirectangularElement {
	Mat &img;
	Point2f polar_center;

};

class EquirectangularContainer
{
private:
	Mat img_equirectangular;
public:
	EquirectangularContainer();
	//init with 1 image
	EquirectangularContainer(Mat img);
	
	void AddImageToContainer(Mat img);
	// 

};

