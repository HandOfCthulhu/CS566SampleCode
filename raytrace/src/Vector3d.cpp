/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#include "Vector3d.h"
#include <iostream>
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

Vector3d::Vector3d(float vec[3]) {
	_x = vec[0];
	_y = vec[1];
	_z = vec[2];
}

float Vector3d::dotProduct(Vector3d operand) {
	return ((_x*operand.getX()) + (_y*operand.getY()) + (_z*operand.getZ()));
}

Vector3d Vector3d::crossProduct(Vector3d operand) {
	Vector3d ret(((_y*operand.getZ())-(_z*operand.getY())),
				 ((_z*operand.getX())-(_x*operand.getZ())),
				 ((_x*operand.getY())-(_y*operand.getX())));
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
	if(len > 0) {
		_x = _x/len;
		_y = _y/len;
		_z = _z/len;
	}
}

Vector3d Vector3d::normalized() {
	float len = getLength();
	Vector3d ret;
	if(len > 0) {
		ret = Vector3d(_x = _x/len, _y = _y/len, _z = _z/len);
	} else {
		ret = *this;
	}
	return ret;
}

float Vector3d::getLength() {
	return(sqrt(_x*_x+_y*_y+_z*_z));
}

Vector3d Vector3d::plus(Vector3d operand) {
	return(Vector3d(_x+operand.getX(), _y+operand.getY(), _z+operand.getZ()));
}

Vector3d Vector3d::negative() {
	return(Vector3d(-1*_x, -1*_y, -1*_z));
}

std::ostream& operator <<( std::ostream &out, const Vector3d &v ){
	v.write( out );
	return( out );
}

void Vector3d::write( std::ostream &out ) const{
	out << "(" << _x << ", " << _y << ", " << _z << ")";
}

Vector3d::~Vector3d(void) {
}
