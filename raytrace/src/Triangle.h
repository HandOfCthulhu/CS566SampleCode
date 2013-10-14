/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Object describing a triangle in the scene
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
		Triangle(Point3d a, Point3d b, Point3d c, Material m);
		Hit intersect(Ray r, float minDepth);
		void setMaterial(Material mat);
		Material getMaterial();
		void write( std::ostream &out ) const;
		bool debugMode;
	private:
		Point3d _a;
		Point3d _b;
		Point3d _c;
		Material _m;
};

std::ostream& operator <<( std::ostream &out, const Triangle &t );

#endif