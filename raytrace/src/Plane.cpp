/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#include "Plane.h"
#include <iostream>

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
	_normal = normal;
	_displace = displacement;
	_m = material;
}

Hit Plane::intersect(Ray r) {
	Hit h = Hit();
	return h;
}

void Plane::setMaterial(Material mat) {
	_m = mat;
}

Material Plane::getMaterial() {
	return(_m);
}