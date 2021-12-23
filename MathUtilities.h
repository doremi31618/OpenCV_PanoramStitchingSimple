#include "OpenCV_include.h"

#pragma once

#ifndef PI
#define PI 3.14159265359
#endif // !1

static class MathUtilities
{
public:
	//numerical tool
	static float PI_to_Degree(float);
	static float Degree_to_PI(float);

	//3d space transform tool 
	static Mat getRotationMatrix3D(float x, float y, float z);
	static Mat getTranslateMatrix3D(float x, float y, float z);

	//vector opeation tool
	static float getVectorAngle(Vec3f, Vec3f);
	static float getMagnitude(Vec3f);
	
	//other utilities

	/// <summary>
	/// this function will return the longitude and latitude calc by the angle of two vectors 
	/// so you don't have to input the point on the sphere surface
	/// </summary>
	/// <param name="front">the vector where lon = 0, lat = 0, usually this vector is (0,0,1)</param>
	/// <param name="point">the point that you want to find out its lon and lat</param>
	/// <returns></returns>
	static Vec2f getLonAndLat(Vec3f front, Vec3f point);
	   

	//image space transform tool
	static Point2f convert_from_topcorner_to_center(Point2f point, float width, float height);
	static Point2f covert_from_center_to_topcorner(Point2f point, float width, float height);
};

