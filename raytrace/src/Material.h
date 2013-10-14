/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 * This class just stores the material information for use in objects and retrieval during the intersection shading code
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
 * $Id: Material.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#ifndef _PHONG_MATERIAL_H_
#define _PHONG_MATERIAL_H_
#include "Vector3d.h"
#include "Color.h"

class Material{
	public:
		Material( );
		Material(Color color, float exponent, Color specColor, Color reflecColor, Color transColor, float refractInd);
		
		void setDiffColor(Color color);
		void setReflectiveColor(Color color);
		void setTransparencyColor(Color color);
		void setSpecularColor(Color color);

		void setExponent(float exp);
		void setRefractionIndex(float refractInd);
		
		Color getDiffuseColor();
		Color getReflectiveColor();
		Color getTransparencyColor();
		Color getSpecularColor();
		float getIndexOfRefraction();
		float getSpecularExponent();

		void write( std::ostream &out ) const;

		bool debugMode;

		~Material( );
	private:
		Color _diffColor;
		Color _specColor;
		Color _transColor;
		Color _reflectColor;
		float _exponent;
		float _indxRefract;
};
std::ostream& operator <<( std::ostream &out, const Material &m );
#endif
