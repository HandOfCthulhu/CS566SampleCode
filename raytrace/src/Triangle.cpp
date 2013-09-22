/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#include "Triangle.h"
#include <iostream>

Triangle::Triangle(Vector3d a, Vector3d b, Vector3d c, Material m) {
	_a = a;
	_b = b;
	_c = c;
	_m = m;
}

Hit Triangle::intersect(Ray r) {
	Hit h = Hit();
	return (h);
}

void Triangle::setMaterial(Material mat) {
	_m = mat;
}

Material Triangle::getMaterial() {
	return(_m);
}

std::ostream& operator <<( std::ostream &out, const Triangle &t ){
	t.write( out );
	return( out );
}

void Triangle::write( std::ostream &out ) const{
	out << "Triangle:" << std::endl;
	out << "\tA:" << _a << std::endl;
	out << "\tB:" << _b << std::endl;
	out << "\tC:" << _c << std::endl;
	out << "Material:" << _m << std::endl;
}