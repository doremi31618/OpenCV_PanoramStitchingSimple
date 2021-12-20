#include "EquirectangularContainer.h"

EquiElement::EquiElement(TinyEXIF::EXIFInfo _exif, Mat& img) : imgSrc(img) {
	//from camera model to guess cmos width and height (here is using )
    exif = _exif;
    Point2f cmos(36, 24);
	if (exif.Model == "Canon EOS R5")
		cmos = Point2f(36, 24);

	//transform focal length (scale)
    float focal_real = exif.FocalLength;
	focal = img.cols > img.rows ?
        focal_real * img.cols / cmos.x :
        focal_real * img.rows / cmos.x ;

    cout << "cols > rows : "<< (img.cols > img.rows) << "focal : " << focal_real << endl;

	//get fov by f and cmos , be care for angle is using degree
	float vFov = atan2(img.rows/2, focal) * 2 ;
	float hFov = atan2(img.cols/2 , focal) * 2 ;

    cout << "vFov : " << vFov<< " ; hFov : " << hFov  << endl;

    //default is use imgSrc size
    transform = Rect2f(0, 0, hFov, vFov);
    imgEqui = Mat(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    calculateEqui();
}

//convert from equi to src
Point2f EquiElement::convert_from_equi_to_src(Point2f point) {
    float w = imgEqui.cols;
    float h = imgEqui.rows;

    float omega = w / 2;
    float thigma = h / 2;

    // -0.5 ~ 0.5
    point.x = (point.x - omega) / w; 
    point.y = -(point.y - thigma) / h;

    //-fov/2 ~ fov/2 
    Point2f angle;
    angle.x = point.x * transform.width;
    angle.y = point.y * transform.height;

    //
    Point2f final_point;
    final_point.x = tan(angle.x) * focal + imgEqui.cols/2;
    final_point.y = -tan(angle.y) * focal + imgEqui.rows/2;

    //cout <<" final_point : "<< final_point << endl;
    return final_point;
}

void EquiElement::calculateEqui() {
    int width = imgEqui.cols;
    int height = imgEqui.rows;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            //step 1 get origin image corresponding coordinate
            Point2f current_pos((float)x, (float)y);
            //current_pos = convert_pt(current_pos);
            current_pos = convert_from_equi_to_src(current_pos);
            Point2i top_left((int)current_pos.x, (int)current_pos.y);
            
            //step2 check if this point inside the image
            if ((top_left.x < 0) ||
                (top_left.y < 0) ||
                (top_left.x > width - 2) ||
                (top_left.y > height - 2)) {
                //cout << "skip";
                continue;
            }

            //step3 resampling color - bilinear interpolation
            float dx = current_pos.x - top_left.x;
            float dy = current_pos.y - top_left.y;

            float weight_tl = (1.0 - dx) * (1.0 - dy);
            float weight_tr = dx * (1.0 - dy);
            float weight_bl = (1.0 - dx) * dy;
            float weight_br = dx * dy;

            Vec3b color = imgSrc.at<Vec3b>(top_left.y, top_left.x) * weight_tl +
                imgSrc.at<Vec3b>(top_left.y, top_left.x + 1) * weight_tr +
                imgSrc.at<Vec3b>(top_left.y + 1, top_left.x) * weight_bl +
                imgSrc.at<Vec3b>(top_left.y + 1, top_left.x + 1) * weight_br;

            imgEqui.at<Vec3b>(y, x) = color;
            //imgEqui.at<Vec3b>(y, x) = imgSrc.at<Vec3b>(top_left.y, top_left.x);
        }
    }
}

void EquiElement::recalculateEqui() {
    if (!imgEqui.empty())
        imgEqui.release();
    calculateEqui();
}

void EquiElement::displaySrc() {
	imshow("src", imgSrc);
	waitKey(0);
	destroyWindow("src");
}

void EquiElement::displayEqui() {
    imshow("equi", imgEqui);
    waitKey(0);
    destroyAllWindows();
}