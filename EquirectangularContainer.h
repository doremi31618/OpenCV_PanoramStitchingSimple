#include <iostream>
#include "OpenCV_include.h"
#include "ThirdParty/TinyEXIF-master/TinyEXIF.h"
#include "MathUtilities.h"

#ifndef EQUIRECTANGULAR
#define EQUIRECTANGULAR

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
	Point2f convert_from_src_to_equi(Point2f);
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
class EquiContainer
{
private:
	Mat img_equirectangular;
public:
	
	EquiContainer(Mat img);
	EquiContainer(Mat** img);
	int getLength();
	void edit_element();
	void edit_element_list();
	void addImage(Mat img);
	void display();
	void Init();

};

#endif // !1