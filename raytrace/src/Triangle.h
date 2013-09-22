/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "Vector3d.h"
#include "RTObject.h"
#include "Material.h"
#include "Ray.h"
#include <iostream>

class Triangle : public RTObject {
	public:
		Triangle(Vector3d a, Vector3d b, Vector3d c, Material m);
		Hit intersect(Ray r);
		void setMaterial(Material mat);
		Material getMaterial();
		void write( std::ostream &out ) const;
	private:
		Vector3d _a;
		Vector3d _b;
		Vector3d _c;
		Material _m;
};

std::ostream& operator <<( std::ostream &out, const Triangle &t );

#endif