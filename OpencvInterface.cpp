#include "OpencvInterface.h"

void StitcherApp::Start() {
    getImageFeatures();
    VisualizeFeatures();

    matchImages();
    VisualizeMatches();
    estimateHomography();
    transformImage();
    
    sphericalWarping(result, result);
    DisplayResult();
}

StitcherApp::StitcherApp(string path1, string path2) {
    img1 = imread(path1, IMREAD_COLOR);
    img2 = imread(path2, IMREAD_COLOR);

    //read exif data 
    ifstream istream_img1(path1, ifstream::binary);
    TinyEXIF::EXIFInfo imageEXIF1(istream_img1);
    
    ifstream istream_img2(path2, ifstream::binary);
    TinyEXIF::EXIFInfo imageEXIF2(istream_img2);
    if (imageEXIF1.Fields && imageEXIF2.Fields) {
        std::cout
            << "Image Description " << imageEXIF2.ImageDescription << "\n"
            << "Image Resolution " << imageEXIF2.ImageWidth << "x" << imageEXIF2.ImageHeight << " pixels\n"
            << "Camera Model " << imageEXIF2.Make << " - " << imageEXIF2.Model << "\n"
            << "Focal Length " << imageEXIF2.FocalLength << " mm" << std::endl;
        
        std::cout
            << "Image Description " << imageEXIF1.ImageDescription << "\n"
            << "Image Resolution " << imageEXIF1.ImageWidth << "x" << imageEXIF1.ImageHeight << " pixels\n"
            << "Camera Model " << imageEXIF1.Make << " - " << imageEXIF1.Model << "\n"
            << "Focal Length " << imageEXIF1.FocalLength << " mm" << std::endl;
    }

    resize(img1, img1, Size(683, 1024));
    resize(img2, img2, Size(683, 1024));

    cvtColor(this->img1, this->img1_gray, COLOR_BGR2GRAY);
    cvtColor(this->img2, this->img2_gray, COLOR_BGR2GRAY);


    if (img1.empty() | img2.empty()) {
        std::cout << "Could not open or find the image!\n" << endl;
        std::cout << "Usage: " << path1 <<" ; " << path2 << " <Input image>" << endl;
    }
}

StitcherApp::StitcherApp(string path) {
    img1 = imread(path, IMREAD_COLOR);
    ifstream istream_img1(path, ifstream::binary);
    TinyEXIF::EXIFInfo imageEXIF1(istream_img1);
    resize(img1, img1, Size(683, 1024));
    cvtColor(this->img1, this->img1_gray, COLOR_BGR2GRAY);
    EquiElement newEqui(imageEXIF1, img1);
    newEqui.displayEqui();
}
void StitcherApp::ShowEquirectangular() {
    EquiElement single_equi();
}

void StitcherApp::getImageFeatures() {
    Ptr<SIFT> detector = SIFT::create();

    detector->detectAndCompute(this->img1_gray, noArray(), this->kp1, this->descriptor1);
    detector->detectAndCompute(this->img2_gray, noArray(), this->kp2, this->descriptor2);

    std::cout << "kp1 count : " << kp1.size() << " ; kp2 count : " << kp2.size() << endl;
}

void StitcherApp::matchImages() {
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    vector<vector<DMatch>> knn_matches;
    matcher->knnMatch(descriptor1, descriptor2, knn_matches, 2);

    //filter matches using the lowe's ratio test
    vector<DMatch> good_matches;
    for (int i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
            this->good_matches.push_back(knn_matches[i][0]);
    }
}

void StitcherApp::estimateHomography() {
    if (MIN_MATCH_COUNT < good_matches.size()) {
        // get point from good matches 
        vector<Point2f> img1_points, img2_points;
        for (int i = 0; i < good_matches.size(); i++) {
            img1_points.push_back(kp1[good_matches[i].queryIdx].pt);
            img2_points.push_back(kp2[good_matches[i].trainIdx].pt);
        }
        
        // findHomography : estimate homography
        // describe : 
        // this function is use to transform img2 to img1 
        // which is the transformation of maping img2 plane to img1 plane
        // findHomography ?????N?q????: https://blog.csdn.net/fengyeer20120/article/details/87798638
        VisualizeMatchesAfterRansac(img1_points, img2_points);
        this->H = findHomography(img2_points, img1_points, RANSAC, 2, noArray(), 2000, 0.995);
    }
    else {
        std::cout << "doesn't have enough matches to estimate homography" << endl;
    }
}

//apply homography and compose images
void StitcherApp::transformImage() {
    warpPerspective(img2, result, H, Size(img2.cols * 2, img2.rows));

    //the last step : compose 2 images
    Mat half = result(Rect(0, 0, img1.cols, img1.rows));//get img1's roi
    img1.copyTo(half);//replace roi to result
    //DisplayResult();

}

Point2f StitcherApp::covert_pt(Point2f point, float w, float h, float f) {
    //step 1 transform point to image center space
    float omega = w/2;
    float thigma = h/2 ;
    point.x = point.x - omega;
    point.y = point.y - thigma;

    
    //step 2 process projection
    float r_square = omega * omega + thigma * thigma + f * f;
    float zc = sqrtf(r_square - point.x * point.x - point.y * point.y);

    Point2f final_point(
        point.x * (f / zc) + omega,
        point.y * (f / zc) + thigma);

    return final_point;
}


void StitcherApp::sphericalWarping(Mat srcImg, Mat& outputImg) {
#if true
    float f = 500;//focal length
    int width = outputImg.cols;
    int height = outputImg.rows;
    Mat new_img(height, width, CV_8UC3, Scalar(0, 0, 0));
    //Mat debug_img(height, width , CV_8UC3, Scalar(0, 0, 0));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            //step 1 get origin image corresponding coordinate
            Point2f current_pos((float)x, (float)y);
            current_pos = covert_pt(current_pos, (float)width, (float)height, f);
            Point2i top_left((int)current_pos.x, (int)current_pos.y);

            //step2 check if this point inside the image
            if ((top_left.x < 0) ||
                (top_left.y < 0) ||
                (top_left.x > width - 2 )||
                (top_left.y > height - 2)) {
                new_img.at<Vec3b>(y, x) = Vec3b(0,0,0);
                continue;
            }
            
            //step3 resampling color - bilinear interpolation
            float dx = current_pos.x - top_left.x;
            float dy = current_pos.y - top_left.y;

            float weight_tl = ( 1.0 - dx ) * ( 1.0 - dy );
            float weight_tr = dx * (1.0 - dy);
            float weight_bl = (1.0 - dx) * dy;
            float weight_br = dx * dy;

            Vec3b color = srcImg.at<Vec3b>(top_left.y, top_left.x) * weight_tl +
                srcImg.at<Vec3b>(top_left.y, top_left.x + 1) * weight_tr +
                srcImg.at<Vec3b>(top_left.y + 1, top_left.x) * weight_bl +
                srcImg.at<Vec3b>(top_left.y + 1, top_left.x + 1) * weight_br;
            
            new_img.at<Vec3b>(y, x) = color;
            //Vec3b debug_color(255*top_left.x/width, 255*top_left.y/height, 0);
            //debug_img.at<Vec3b>(y, x) = debug_color;
            
        }
        
    }
    imshow("new img", new_img);//the actual image
#else
    //reference : https://stackoverflow.com/questions/45761194/how-to-use-opencvs-sphericalwarper
    float scale = 500.0f;
    float fx = 100, fy = 100, cx = 341, cy = 512;
    Vec3f rot(0, 0, 0);
    SphericalWarper warp(scale);
    Mat K = (Mat_<float>(3, 3) <<
        fx, 0, cx,
        0, fy, cy,
        0, 0, 1);
    Mat R = eulerAnglesToRotationMatrix(rot);
    warp.warp(srcImg, K, R, INTER_LINEAR, BORDER_CONSTANT, outputImg);
#endif

}

void StitcherApp::VisualizeMatchesAfterRansac(vector<Point2f> img1_points, vector<Point2f> img2_points) {
    Mat m_fundamental = findFundamentalMat(img2_points, img1_points, m_RANSACStatus, FM_RANSAC);
    int outlinerCount = 0, inlinerCount = 0;
    vector<DMatch> m_inlierMatches;
    vector<Point2f> m_img1_inliner, m_img2_inliner;
    for (int i = 0; i < m_RANSACStatus.size(); i++) {
        if (m_RANSACStatus[i] == 0) {
            outlinerCount++;
        }
        else {
            m_img1_inliner.push_back(img1_points[i]);
            m_img2_inliner.push_back(img2_points[i]);
            DMatch new_match(inlinerCount, inlinerCount, good_matches[i].distance);
            m_inlierMatches.push_back(new_match);
            inlinerCount++;
        }
    }
    cout << " img1 point size : " << m_img1_inliner.size() <<
         " img2 point size : " << m_img2_inliner.size() <<
        " good matches size : " << m_inlierMatches.size() << endl;
    cout << "total count : " << m_RANSACStatus.size() << " outliner count : " << outlinerCount << endl;
    Mat img_matches;
    vector<KeyPoint> new_kp1, new_kp2;
    KeyPoint::convert(m_img1_inliner, new_kp1);
    KeyPoint::convert(m_img2_inliner, new_kp2);
    drawMatches(img1, new_kp1, img2, new_kp2, m_inlierMatches, img_matches);
    imshow("after ransac matches", img_matches);
    waitKey(0);
    destroyAllWindows();
    
}
void StitcherApp::VisualizeFeatures() {
    if (this->kp1.size() == 0 || this->kp2.size() == 0) getImageFeatures();
    //cout << "kp1 count" << kp1.size() << "kp2 count" << kp2.size() << endl;
    Mat img1_sift_visualize, img2_sift_visualize;
    drawKeypoints(this->img1_gray, this->kp1, img1_sift_visualize);
    drawKeypoints(this->img2_gray, this->kp2, img2_sift_visualize);
    imshow("img1 sift", img1_sift_visualize);
    imshow("img2 sift", img2_sift_visualize);
    waitKey(0);
    destroyAllWindows();
}

void StitcherApp::VisualizeMatches() {
    if (this->kp1.size() == 0 || this->kp2.size() == 0) getImageFeatures();
    if (this->good_matches.size() == 0) matchImages();

    Mat img_matches;
    drawMatches(img1, kp1, img2, kp2, good_matches, img_matches, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("img matches", img_matches);
    waitKey(0);
}

void StitcherApp::ShowAllImages() {
    imshow("img1 src", img1);
    imshow("img2 src", img2);
    waitKey(0);
    destroyAllWindows();
}

void StitcherApp::DisplayResult() {
    imshow("result", result);
    waitKey(0);
    destroyAllWindows();
}
TinyEXIF::EXIFInfo StitcherApp::readEXIF(string path) {

    //read exif file
    ifstream istream_img1(path, ifstream::binary);
    TinyEXIF::EXIFInfo imageEXIF1(istream_img1);
    if (imageEXIF1.Fields) {
        std::cout
            << "Image Description " << imageEXIF1.ImageDescription << "\n"
            << "Image Resolution " << imageEXIF1.ImageWidth << "x" << imageEXIF1.ImageHeight << " pixels\n"
            << "Camera Model " << imageEXIF1.Make << " - " << imageEXIF1.Model << "\n"
            << "Focal Length " << imageEXIF1.FocalLength << " mm" << std::endl;
    }
    return imageEXIF1;
}

void StitcherApp::ReadImage(string path, bool display=false) {
    //range from 0~1
    float working_scale = 1;
    Mat img_src, img_resize, img_gray;
    TinyEXIF::EXIFInfo exif;

    //read and Init
    exif = readEXIF(path);
    img_src = imread(path, IMREAD_COLOR);
    resize(img_src, img_resize, Size((int)(img_src.cols * working_scale), (int)(img_src.cols * working_scale)));
    cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

    if (img_src.empty()) {
        std::cout << "Could not open or find the image!\n" << endl;
        std::cout << "Usage: " << path << " ; " <<  endl;
    }

    if (display) {
        imshow("src", img_src);
        imshow("resize", img_resize);
        imshow("gray", img_gray);

        waitKey(0);

        destroyWindow("src");
        destroyWindow("resize");
        destroyWindow("gray");
    }
}


