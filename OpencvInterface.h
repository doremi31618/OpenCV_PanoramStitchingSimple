
#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching/detail/warpers.hpp>
#include "ThirdParty/TinyEXIF-master/TinyEXIF.h"


using namespace std;
using namespace cv;
using namespace cv::detail;

#ifndef OPENCV_INTERFACE
#define OPENCV_INTERFACE

/// <summary>
/// this application is only design for stitching two images
/// </summary>
class StitcherApp {
private:
	TinyEXIF::EXIFInfo img1_exif, img2_exif;
	Mat img1, img2, img1_gray, img2_gray, result;
	Mat descriptor1, descriptor2;
	Mat H;

	vector<KeyPoint> kp1, kp2;
	vector<uchar> m_RANSACStatus;
	const float ratio_thresh = 0.6f;
	const float MIN_MATCH_COUNT = 10;
	vector<DMatch> good_matches;

	//pipline function
	void getImageFeatures();
	void matchImages();
	void estimateHomography();
	void transformImage();
	Point2f covert_pt(Point2f point, float w, float h, float f);
	void sphericalWarping(Mat srcImg, Mat& outputImg);
	 
	
public: 
	void VisualizeFeatures();
	void VisualizeMatches();
	//call at estimate Homography
	void VisualizeMatchesAfterRansac(vector<Point2f> img1_points, vector<Point2f> img2_points);
	void DisplayResult();
	void ShowAllImages();// display img1 & img2
	void Start(); //set the whole pipeline from
	StitcherApp(string path1, string path2);
};



#endif // !1
