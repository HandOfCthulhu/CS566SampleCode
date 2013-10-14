/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Object describing a plane in the scene
 */

#include "Plane.h"
#include <iostream>
#include "Point.h"

std::ostream& operator <<( std::ostream &out, const Plane &p ){
	p.write( out );
	return( out );
}

void Plane::write( std::ostream &out ) const{
	out << "Plane: " << std::endl;
	out << "\tNormal: ";
	out << _normal << std::endl;
	out << "\tDisplace: " << _displace << std::endl;
	out << _m << std::endl;
}

Plane::Plane(Vector3d normal, float displacement, Material material) {
	_normal = normal.normalized();
	_displace = displacement;
	_m = material;
}

Hit Plane::intersect(Ray r, float minDepth) {
	Hit h;

	float denominator = _normal.dotProduct(r.getDirection());
	if(debugMode) {
		std::cout << "Denominator: " << denominator << std::endl;
	}
	if (denominator != 0) {
		Vector3d temp = _normal.scalarProduct(_displace);
		Point3d planeOrigin = Point3d(0,0,0).translate(temp.getX(), temp.getY(), temp.getZ());
		Vector3d viewToPlaneOrigin (planeOrigin, r.getOrigin());
		//Vector3d viewToPlaneOrigin = planeOrigin.plus(r.getOrigin().negative());
		float t = viewToPlaneOrigin.dotProduct(_normal) / denominator;
		if(debugMode) {
			std::cout << "Plane Origin: " << planeOrigin << std::endl;
			std::cout << "Vector view to planeOrigin: " << viewToPlaneOrigin << std::endl;
			std::cout << "t: " << t << std::endl;
		}
		if (t >= 0) {
			if ((t < minDepth) || (minDepth < 0.0)) {
				temp = r.getDirection().scalarProduct(t);
				h.hit(true, t, r.getOrigin().translate(temp.getX(), temp.getY(), temp.getZ()), r.getDirection(), _normal, _m);
			}
		}
	}


	return h;
}

void Plane::setMaterial(Material mat) {
	_m = mat;
}

Material Plane::getMaterial() {
	return(_m);
}