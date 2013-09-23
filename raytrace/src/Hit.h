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
 * $Id: Hit.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#ifndef _HIT_H_
#define _HIT_H_
#include "Vector3d.h"
#include "Material.h"

class Hit{
public:
	Hit( ) {_hit = false; _depth = 0.0; _position = Vector3d(); _m = Material();};
	Hit(Hit &h) {_hit = h.didHit(); _depth = h.getDepth(); _position = h.getHitLocation(); _m = h.getMaterial(); _normal=h.getHitNormal(); _view = h.getHitVector(); _finalColor = h.getColor();};
	float getDepth() {return(_depth);};
	bool didHit() {return(_hit);};
	void hit(bool didHit, float depth, Vector3d position, Vector3d view, Vector3d normal, Material m) { _hit = didHit; _depth = depth; _position = position; _view = view; _normal = normal; _m = m;};
	Vector3d getHitLocation() {return(_position); };
	Material getMaterial() {return(_m);}; //TODO: FIX THIS
	Vector3d getColor() {return(_finalColor); };
	Vector3d getHitNormal() {return _normal;};
	Vector3d getHitVector() {return _view; };
	void setColor(Vector3d finalColor) { _finalColor = finalColor; };
	~Hit( ) {};
private:
	bool _hit;
	float _depth;
	Vector3d _position;
	Vector3d _normal;
	Vector3d _view;
	Material _m;
	Vector3d _finalColor;
};
#endif