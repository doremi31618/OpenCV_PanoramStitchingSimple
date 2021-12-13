// PanoDevIntegration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "OpencvInterface.h"

int main()
{
    //use Default value to init app environment
    string img1_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img1.JPG";
    string img2_path = "C:\\Users\\panos\\Desktop\\PanoAWS\\Projects\\PanoDevIntegration\\pic\\img2.JPG";
    StitcherApp app(img1_path, img2_path);
    app.Start();
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
