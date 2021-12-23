// PanoDevIntegration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "OpencvInterface.h"
#include "MathUtilities.h"
#include "OpenCV_include.h"
void testFormula() {
    Vec3f forward(0, 1, 1);
    //cout << MathUtilities::getRotationMatrix3D(PI / 2, 0, 0) * Mat(forward) << endl;
    //cout << "Check vector angle " << MathUtilities::PI_to_Degree(MathUtilities::getVectorAngle(Vec3f(1, 0, 0), Vec3f(0, 0, 1))) << endl;
    //Vec2f lon_lat = MathUtilities::getLonAndLat(Vec3f(0, 0, 1), Vec3f(0, 0, -1));
    //cout << "lon : " << MathUtilities::PI_to_Degree(lon_lat[0]) << " ; lat : " << MathUtilities::PI_to_Degree(lon_lat[1]);

}
int main()
{
    //testFormula();
    //use Default value to init app environment
    string img1_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img1.JPG";
    //string img2_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img2.JPG";
    //StitcherApp app(img1_path, img2_path);
    StitcherApp app(img1_path);
    //app.Start();
    //app.ShowAllImages();
    return 0;
}

