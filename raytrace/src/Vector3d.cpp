#include "Vector3d.h"
#include <cmath>

Vector3d::Vector3d(void) {
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3d::Vector3d(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

float Vector3d::dotProduct(Vector3d operand) {
	return (_x*operand.getX() + _y*operand.getY() + _z*operand.getZ());
}

Vector3d Vector3d::crossProduct(Vector3d operand) {
	Vector3d ret(0.0,0.0,0.0);
	return ret;
}

Vector3d Vector3d::scalarProduct(float scalar) {
	Vector3d ret(_x*scalar, _y*scalar, _z*scalar);
	return(ret);
}

float Vector3d::getX() {
	return(_x);
}
float Vector3d::getY() {
	return(_y);
}
float Vector3d::getZ() {
	return(_z);
}

void Vector3d::setX(float x) {
	_x=x;
}
void Vector3d::setY(float y) {
	_y=y;
}
void Vector3d::setZ(float z) {
	_z = z;
}

void Vector3d::normalize() {
	float len = getLength();
	_x = _x/len;
	_y = _y/len;
	_z = _z/len;
}

Vector3d Vector3d::normalized() {
	float len = getLength();
	Vector3d ret(_x = _x/len, _y = _y/len, _z = _z/len);
	return ret;
}

float Vector3d::getLength() {
	return(sqrt(_x*_x+_y*_y+_z*_z));
}

Vector3d::~Vector3d(void)
{
}
