#include "OpencvInterface.h"

StitcherApp::StitcherApp(string path1, string path2) {
    this->img1 = imread(path1, IMREAD_COLOR);
    this->img2 = imread(path2, IMREAD_COLOR);

    resizeImage(this->img1);
    resizeImage(this->img2);

    cvtColor(this->img1, this->img1_gray, COLOR_BGR2GRAY);
    cvtColor(this->img2, this->img2_gray, COLOR_BGR2GRAY);

    if (img1.empty() | img2.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << path1 <<" ; " << path2 << " <Input image>" << endl;
    }
}

void StitcherApp::Start() {

}

void StitcherApp::getImageFeatures() {
    Ptr<SIFT> detector = SIFT::create();

    detector->detectAndCompute(this->img1_gray, noArray(), this->kp1, this->descriptor1);
    detector->detectAndCompute(this->img2_gray, noArray(), this->kp2, this->descriptor2);

    cout << "kp1 count : " << kp1.size() << " ; kp2 count : " << kp2.size() << endl;
}

void StitcherApp::matchImages() {
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    vector<vector<DMatch>> knn_matches;
    matcher->knnMatch(descriptor1, descriptor2, knn_matches, 2);

    //filter matches using the lowe's ratio test
    const float ratio_thresh = 0.7f;
    vector<DMatch> good_matches;
    for (int i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
            this->good_matches.push_back(knn_matches[i][0]);
    }

    
}

void StitcherApp::estimateHomography() {

}

void StitcherApp::VisualizeFeatures() {
    if (this->kp1.size() == 0 | this->kp2.size() == 0) getImageFeatures();
    //cout << "kp1 count" << kp1.size() << "kp2 count" << kp2.size() << endl;
    Mat img1_sift_visualize, img2_sift_visualize;
    drawKeypoints(this->img1_gray, this->kp1, img1_sift_visualize);
    drawKeypoints(this->img2_gray, this->kp2, img2_sift_visualize);
    imshow("img1 sift", img1_sift_visualize);
    imshow("img2 sift", img2_sift_visualize);
    waitKey(0);
    destroyAllWindows();
}

void StitcherApp::VisualizeMathes() {
    if (this->kp1.size() == 0 | this->kp2.size() == 0) getImageFeatures();
    if (this->good_matches.size() == 0) matchImages();

    Mat img_matches;
    drawMatches(img1, kp1, img2, kp2, good_matches, img_matches, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("img matches", img_matches);
    waitKey(0);
    destroyAllWindows();
}

void StitcherApp::ShowAllImages() {
    imshow("img1 src", img1);
    imshow("img2 src", img2);
    waitKey(0);
    destroyAllWindows();
}

