/* Gregory N Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Group of objects, also includes interception checks and shading
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
 * $Id: Group.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */
#include <vector>
#include "Ray.h"
#include "Hit.h"
#include "RTObject.h"
#include "Light.h"

#ifndef _GROUP_H_
#define _GROUP_H_

class Group{
	public:
		Group( );
		void addObject(RTObject* obj);
		void addLight(Light light);
		Hit intersect(Ray r, int recDepth, int maxDepth);
		void write( std::ostream &out ) const;
		int getNumberOfObjects();
		int getNumberOfLights();
		void setBGColor(Vector3d color);

		bool debugMode;

		~Group( );
	private:
		std::vector<RTObject*> _objects;
		std::vector<Light> _lights;
		Vector3d _bgColor;
};
std::ostream& operator <<( std::ostream &out, const Group &g );
#endif
