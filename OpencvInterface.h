
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching/detail/warpers.hpp>

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
	Mat img1, img2, img1_gray, img2_gray, result;
	Mat descriptor1, descriptor2;
	Mat H;

	vector<KeyPoint> kp1, kp2;
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

	//some other opencv utilities 
	Mat eulerAnglesToRotationMatrix(Vec3f& theta)
	{
		//reference : https://stackoverflow.com/questions/45761194/how-to-use-opencvs-sphericalwarper
		// Calculate rotation about x axis
		Mat R_x = (Mat_<float>(3, 3) <<
			1, 0, 0,
			0, cosf(theta[0]), -sinf(theta[0]),
			0, sinf(theta[0]), cosf(theta[0])
			);

		// Calculate rotation about y axis
		Mat R_y = (Mat_<float>(3, 3) <<
			cosf(theta[1]), 0, sinf(theta[1]),
			0, 1, 0,
			-sinf(theta[1]), 0, cosf(theta[1])
			);

		// Calculate rotation about z axis
		Mat R_z = (Mat_<float>(3, 3) <<
			cosf(theta[2]), -sinf(theta[2]), 0,
			sinf(theta[2]), cosf(theta[2]), 0,
			0, 0, 1);


		// Combined rotation matrix
		Mat R = R_z * R_y * R_x;

		return R;

	}
public: 
	void VisualizeFeatures();
	void VisualizeMathes();
	void DisplayResult();
	void ShowAllImages();// display img1 & img2
	void Start(); //set the whole pipeline from
	StitcherApp(string path1, string path2);
};



#endif // !1
