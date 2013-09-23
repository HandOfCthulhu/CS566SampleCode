/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */


#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Vector3d.h"
#include "Material.h"
#include "RTObject.h"
#include "Hit.h"
#include "Ray.h"
#include <iostream>

class Sphere : public RTObject {
	public:
		Sphere();
		Sphere(Vector3d position, float radius, Material mat);
		Vector3d getPosition();
		float getRadius();
		Material getMaterial();
		void setPosition(Vector3d position);
		void setRadius(float radius);
		void setMaterial(Material material);
		Hit intersect(Ray r, float minDepth);
		void write( std::ostream &out ) const;
	private:
		Vector3d _pos;
		float _rad;
		Material _mat;
};

#endif // !_SPHERE_H_
