/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
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
 *
 *
 * $Id: Camera.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */


#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Vector3d.h"
#include "Ray.h"

enum CameraMode {orthographic, perspective, simple};
class Camera{
	public:
		Camera( );
		Camera(CameraMode mode, Vector3d position, Vector3d up, Vector3d direction);
		~Camera( ){};

		Ray getNextRay();
		int getLastX();
		int getLastY();
		int numPxWidth();
		int numPxHeight();
		bool isDone();

		CameraMode getMode();
		Vector3d getPosition();
		Vector3d getDirection();
		Vector3d getUpVector();
		float getAngle();
		float getDistance();
		int getViewPlaneWidth();
		int getViewPlaneHeight();
		float getPixelSize();

		void setMode(CameraMode mode);
		void setPosition(Vector3d pos);
		void setDirection(Vector3d dir);
		void setUpVector(Vector3d up);
		void setAngle(float angle);
		void setDistance(float distance);
		void setViewPlaneWidth(int planeWidth);
		void setViewPlaneHeight(int planeHeight);
		void setPixelSize(float pxSize);

		void write( std::ostream &out ) const;

	private:
		Vector3d calcRayBase(int x, int y);
		int _x;
		int _y;
		int _pxWidth;
		int _pxHeight;
		bool done;

		CameraMode _mode;
		Vector3d _position;
		Vector3d _direction;
		Vector3d _up;

		Vector3d _right;

		float _angle;
		float _distance;
		int _viewPlaneWidth;
		int _viewPlaneHeight;
		float _pixelSize;
};
std::ostream& operator <<( std::ostream &out, const Camera &c );
#endif
