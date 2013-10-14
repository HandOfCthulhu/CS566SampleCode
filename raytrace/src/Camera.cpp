/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Used to generate the rays for intercepts.
 */
/*
 * Copyright (c) 2005-2013 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Vector3d.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(void) {
	_mode = orthographic;
	_up = Vector3d();
	_direction = Vector3d();
	_angle = 0.0;
	_right = Vector3d();
	_x = 0;
	_y = 0;
	_pxWidth = 0;
	_pxHeight = 0;
	_position = Point3d();
	_up = Vector3d();
	_distance = 0.0;
	_viewPlaneWidth = 0;
	_viewPlaneHeight = 0;
	_pixelSize = 1;
	done = false;
}

Camera::Camera(CameraMode mode, Point3d location, Vector3d up, Vector3d direction) {
	_mode = mode;
	_position = location;
	_direction = direction;
	_up = up;
	_right = _up.crossProduct(_direction).normalized();
	_angle = 0.0;
	_x = 0;
	_y = 0;
	_pxWidth = 0;
	_pxHeight = 0;
	_distance = 0.0;
	_viewPlaneWidth = 0;
	_viewPlaneHeight = 0;
	_pixelSize = 1;
	done = false;
}

CameraMode Camera::getMode() {
	return(_mode);
}

Point3d Camera::getPosition() {
	return(_position);
}

Vector3d Camera::getDirection() {
	return(_direction);
}

Vector3d Camera::getUpVector() {
	return (_up);
}

void Camera::setMode(CameraMode mode) {
	_mode = mode;
}

void Camera::setPosition(Point3d pos) {
	_position = pos;
}

void Camera::setDirection(Vector3d dir) {
	_direction = dir;
	//Always keep our right vector up to date
	_right = _up.crossProduct(_direction).normalized();
}

void Camera::setUpVector(Vector3d up) {
	_up = up;
	//Always keep our right vector up to date
	_right = _up.crossProduct(_direction).normalized();
}

float Camera::getAngle(){
	return (_angle);
}

float Camera::getDistance() {
	return (_distance);
}

int Camera::getViewPlaneWidth() {
	return (_viewPlaneWidth);
}

int Camera::getViewPlaneHeight() {
	return (_viewPlaneHeight);
}

float Camera::getPixelSize() {
	return (_pixelSize);
}

void Camera::setAngle(float angle) {
	_angle = angle;
}

void Camera::setDistance(float distance) {
	_distance = distance;
}

void Camera::setViewPlaneWidth(int planeWidth) {
	_viewPlaneWidth = planeWidth;
	_pxWidth = (int)(_viewPlaneWidth / _pixelSize);
}

void Camera::setViewPlaneHeight(int planeHeight) {
	_viewPlaneHeight = planeHeight;
	_pxHeight = (int)(_viewPlaneHeight / _pixelSize);
}

void Camera::setPixelSize(float pxSize) {
	_pixelSize = pxSize;
	_pxWidth = (int)(_viewPlaneWidth / _pixelSize);
	_pxHeight = (int)(_viewPlaneHeight / _pixelSize);
}

Ray Camera::getNextRay() {
	Point3d origin;
	Vector3d dir;
	Vector3d temp;
	if (debugMode) {
		std::cout << "Creating ray for (" << _x << ", " << _y << "):";
	}
	origin = calcRayBase(_x, _y);
	
	switch(_mode)
	{
		case(orthographic):
			//origin = calcRayBase(_x, _y);
			dir = _direction;
			break;
		case(perspective):
			//origin = _position;
			temp = _direction.scalarProduct(_distance);
			dir = Vector3d(origin.translate(temp.getX(), temp.getY(), temp.getZ()), _position).normalized();
			break;
		case(simple):
			//origin = _position;
			temp = _direction.scalarProduct(_distance);
			dir = Vector3d(origin.translate(temp.getX(), temp.getY(), temp.getZ()), _position).normalized();
			break;
		default:
			//origin = calcRayBase(_x, _y);
			dir = _direction;
			break;
	}
	_x = _x + 1;
	if ( _x >= _pxWidth ) {
		_x = 0;
		_y = _y + 1;
	}
	if(_y >= _pxHeight ) {
		done = true;
	}
	if (debugMode) {
		std::cout << " o(" << origin.getX() << ", " << origin.getY() << ", " << origin.getZ() << ") dir(" << dir.getX() << ", " << dir.getY() << ", " << dir.getZ() << ")" << std::endl;
	}
	return(Ray(origin, dir));
}

Point3d Camera::calcRayBase(int x, int y) {
	Vector3d horizontal = _right.scalarProduct((float)((-0.5 *(_viewPlaneWidth)) + ((x+0.5) * _pixelSize)));
	Vector3d vertical = _up.scalarProduct((float)((0.5*(_viewPlaneHeight)) - ((y+0.5) * _pixelSize)));
	Vector3d temp = horizontal.plus(vertical);
	return(_position.translate(temp.getX(), temp.getY(), temp.getZ()));
}

int Camera::numPxWidth() {
	return(_pxWidth);
}

int Camera::numPxHeight() {
	return(_pxHeight);
}

int Camera::getLastX() {
	return(_x);
}

int Camera::getLastY() {
	return(_y);
}

std::ostream& operator <<( std::ostream &out, const Camera &c ) {
	c.write( out );
	return( out );
}

void Camera::write( std::ostream &out ) const {
	out << "Camera: " << std::endl;
	out << "\tMode: " << _mode << std::endl;
	out << "\tOrigin: " << _position << std::endl;
	out << "\tDirection: " << _direction << std::endl;
	out << "\tUp: " << _up << std::endl;
	out << "\tDistance: " << _distance << std::endl;
	out << "\tAngle: " << _angle << std::endl;
	out << "\tPlaneWidth: " << _viewPlaneWidth << std::endl;
	out << "\tPlaneHeight: " << _viewPlaneHeight << std::endl;
	out << "\tPixelSize: " << _pixelSize << std::endl;
}

bool Camera::isDone() {
	return(done);
}