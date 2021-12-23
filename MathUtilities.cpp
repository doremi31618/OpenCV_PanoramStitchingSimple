#include "MathUtilities.h"

Mat MathUtilities::getRotationMatrix3D(float x, float y, float z) {
	Mat Rx = (Mat_<float>(3, 3) <<
		1, 0, 0,
		0, cos(x), -sin(x),
		0, sin(x), cos(x));
	Mat Ry = (Mat_<float>(3, 3) <<
		cos(y), 0, sin(y),
		0, 1, 0,
		-sin(y), 0, cos(y));
	Mat Rz = (Mat_<float>(3, 3) <<
		cos(z), -sin(z), 0,
		sin(z), cos(z), 0,
		0, 0, 1);
	return Rz * Rx * Ry ;
}

Mat MathUtilities::getTranslateMatrix3D(float x, float y, float z) {
	Mat translate = (Mat_<float>(4, 4) <<
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
	return translate;
}

Point2f MathUtilities::convert_from_topcorner_to_center(Point2f point, float width, float height) {
	return Point2f(
		point.x - width / 2,
		-(point.y - height / 2));
}

Point2f MathUtilities::covert_from_center_to_topcorner(Point2f point, float width, float height) {
	return Point2f(
		point.x + width / 2,
		-point.y + height / 2
	);
}
float MathUtilities::getMagnitude(Vec3f v1) {
	float result = 0;
	for (int i = 0; i < 3;i++)
		result += pow(v1[i], 2);
	//cout << "magnitude of v (" << v1 << ") : " << sqrtf(result);
	return sqrtf(result);
}

float MathUtilities::getVectorAngle(Vec3f v1, Vec3f v2) {
	float Magnitude_v1 = getMagnitude(v1);
	float Magnitude_v2 = getMagnitude(v2);

	//both are points
	if (Magnitude_v1 == 0 || Magnitude_v2 == 0 )
		return 0;
	float dot = min(max(v1.dot(v2) / (Magnitude_v1 * Magnitude_v2), -1.0f), 1.0f);
	float angle = acos(dot);
	//cout <<"angle : " << angle<<" ; dot "<< v1.dot(v2) << " ; Deniminator : " << Magnitude_v1 * Magnitude_v2 << endl;
	return angle;
}

Vec2f MathUtilities::getLonAndLat(Vec3f front, Vec3f point) {
	Vec3f point_xz = Vec3f(point[0], 0, point[2]);

	float lon = getVectorAngle(front, point_xz);
	float lat = 0;

	if (lon == 0)
		lat = getVectorAngle(front, point);
	else
		lat = getVectorAngle(point_xz, point);

	if (point[0] < 0) lon *= -1;
	if (point[1] < 0) lat *= -1;
	
	return Vec2f(lon, lat);
}

float MathUtilities::Degree_to_PI(float angle) {
	return angle * PI / 180.0f;
}

float MathUtilities::PI_to_Degree(float pi_angle) {
	return pi_angle * 180.0f / PI;
}