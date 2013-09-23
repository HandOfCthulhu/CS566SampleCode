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
 * $Id: Ray.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#ifndef _RAY_H_
#define _RAY_H_
#include "Vector3d.h"

enum RayType {primary, shadow, reflection};

class Ray{
	public:
		Ray(void) {_o = Vector3d(); _d = Vector3d(); _mode=primary;};
		Ray(Vector3d origin, Vector3d direction) { _o = origin; _d = direction.normalized(); _mode=primary; };
		Vector3d getOrigin() { return (_o); };
		Vector3d getDirection() { return (_d); };
		RayType getType() { return(_mode); };
		void setType(RayType type) { _mode = type; };
		void setOrigin(Vector3d origin) { _o = origin; };
		void setDirection(Vector3d direction) { _d = direction.normalized(); };
		~Ray(void){};
	private:
		Vector3d _o;
		Vector3d _d;
		RayType _mode;
};
#endif