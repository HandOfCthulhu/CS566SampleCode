/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#ifndef _PLANE_H_
#define _PLANE_H_
#include "RTObject.h"
#include "Vector3d.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include <iostream>

class Plane : public RTObject {
	public:
		Plane();
		Plane(Vector3d normal, float displacement, Material material);
		Hit intersect(Ray r);
		void setMaterial(Material mat);
		Material getMaterial();
		void write( std::ostream &out ) const;
	private:
		Vector3d _normal;
		float _displace;
		Material _m;
};

std::ostream& operator <<( std::ostream &out, const Plane &p );

#endif