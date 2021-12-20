#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching/detail/warpers.hpp>
#include "ThirdParty/TinyEXIF-master/TinyEXIF.h"

#ifndef EQUIRECTANGULAR
#define EQUIRECTANGULAR


using namespace cv;
using namespace std;

class EquiElement {
private:
	Mat& imgSrc;
	TinyEXIF::EXIFInfo exif;
	Mat imgEqui;
	float focal;
	/// <summary>
	/// center(x,y), hFov, vFov
	/// </summary>
	Rect2f transform;
	Size imgSize;
	Point2f convert_from_equi_to_src(Point2f);
	void calculateEqui();
public:
	EquiElement(TinyEXIF::EXIFInfo, Mat&);
	void displaySrc();
	void displayEqui();
	void recalculateEqui();
};

/// <summary>
/// Define a container for Equirectangular 
/// </summary>
//class EquiContainer
//{
//private:
//	Mat img_equirectangular;
//public:
//	
//	EquiContainer(Mat img);
//	EquiContainer(Mat** img);
//
//	void edit_element();
//	void edit_element_list();
//	void addImage(Mat img);
//	void display();
//	void Init();
//
//};

#endif // !1