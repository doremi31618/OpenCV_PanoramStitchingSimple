// PanoDevIntegration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "OpencvInterface.h"

void testFormula() {
    while (true) {
        float omega = 341;
        float thigma = 512;

        float point_x = 600;
        float point_y = 512;
        cout << "please enter point x" << endl;
        cin  >> point_x;
        cout << "please enter point y" << endl;
        cin >> point_y;

        point_x -= omega;
        point_y -= thigma;

        const float r_square = 341 * 341 + 512 * 512 + 300 * 300;
        const float zc = sqrtf(r_square - point_x * point_x - 200 * 200);
        float final_x = point_x * (300 / zc) + omega;
        cout << "final_x" << final_x <<endl;
    }
    
}
int main()
{
    //testFormula();
    //use Default value to init app environment
    string img1_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img1.JPG";
    string img2_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img2.JPG";
    //StitcherApp app(img1_path, img2_path);
    StitcherApp app(img1_path);
    //app.Start();
    //app.ShowAllImages();
    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
