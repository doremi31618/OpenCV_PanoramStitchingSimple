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
    imgEqui = Mat(720, 1440, CV_8UC3, Scalar(0, PI/2, 0));
    calculateEqui();
}

Point2f EquiElement::convert_from_src_to_equi(Point2f point) {
    point.x = point.x - imgSrc.cols / 2; 
    point.y = (point.y - imgSrc.rows / 2);

    //if the center of image is not at origin point (0,0) ,
    //image should rotate first before projection 
    
    //compute the angle of 
    Mat rot = MathUtilities::getRotationMatrix3D(transform.y, transform.y, 0);
    Vec3f img_pt(point.x, point.y, focal);
    Vec3f normal(0, 0, focal);
    Vec3f rot_img_pt = Mat(rot * Mat(img_pt)).reshape(3).at<Vec3f>();

    Vec2f lon_lat = MathUtilities::getLonAndLat(normal, rot_img_pt);
    float lon = lon_lat[0];
    float lat = lon_lat[1];
    

    //assign to equirectangular
    lon = lon * (imgEqui.cols / 2) / PI + imgEqui.cols / 2;
    lat = lat * imgEqui.rows / PI + imgEqui.rows / 2;

    //cout << "lon : " << lon << " ; lat : " << lat << endl;
    return Point2f(lon, lat);
}

void EquiElement::calculateEqui() {
    int width = imgSrc.cols;
    int height = imgSrc.rows;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            //step 1 get origin image corresponding coordinate
            Point2f current_pos((float)x, (float)y);
            current_pos = convert_from_src_to_equi(current_pos);
            Point2i top_left((int)current_pos.x, (int)current_pos.y);
            
            if (top_left.x < 0 || top_left.y < 0 ||
                top_left.x > imgEqui.cols -1 ||
                top_left.y > imgEqui.rows -1)
            {
                cout << "top left : " << top_left.x << " top_left.y : "<<top_left.y << endl;
                continue;
            }

            //imgEqui.at<Vec3b>(y, x) = color;
            imgEqui.at<Vec3b>(top_left.y, top_left.x) = imgSrc.at<Vec3b>(y, x);
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