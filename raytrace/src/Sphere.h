/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Object describing a sphere
 */


#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Vector3d.h"
#include "Material.h"
#include "RTObject.h"
#include "Hit.h"
#include "Ray.h"
#include "Point.h"
#include <iostream>

class Sphere : public RTObject {
	public:
		Sphere();
		Sphere(Point3d position, float radius, Material mat);
		Point3d getPosition();
		float getRadius();
		Material getMaterial();
		void setPosition(Point3d position);
		void setRadius(float radius);
		void setMaterial(Material material);
		Hit intersect(Ray r, float minDepth);
		void write( std::ostream &out ) const;
		bool debugMode;
	private:
		Point3d _pos;
		float _rad;
		Material _mat;
};

#endif // !_SPHERE_H_
