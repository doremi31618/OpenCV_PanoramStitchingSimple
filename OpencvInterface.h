
#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#ifndef OPENCV_INTERFACE
#define OPENCV_INTERFACE

/// <summary>
/// this application is only design for stitching two images
/// </summary>
class StitcherApp {
private:
	Mat img1, img2, img1_gray, img2_gray;
	Mat descriptor1, descriptor2;
	Mat H;

	vector<KeyPoint> kp1, kp2;
	const float ratio_thresh = 0.7f;
	const float MIN_MATCH_COUNT = 10;
	vector<DMatch> good_matches;

	void getImageFeatures();
	void matchImages();
	void estimateHomography();
	void transformImage();
	void resizeImage(Mat& img) {
		Size size = img.size();
		size.height = 1024;
		size.width = 768;
		resize(img, img, size);
	}
public: 
	void VisualizeFeatures();
	void VisualizeMathes();
	void ShowAllImages();// display img1 & img2
	void Start(); //set the whole pipeline from 
	StitcherApp(string path1, string path2);
	class StitchPipeLine {

	};
};



#endif // !1
