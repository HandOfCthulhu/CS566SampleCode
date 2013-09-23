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
	_normal = normal.normalized();
	_displace = displacement;
	_m = material;
}

Hit Plane::intersect(Ray r, float minDepth) {
	Hit h = Hit();
	//double t = dot (p.a-r.o, p.n) / dot(r.d, p.n);
	Vector3d p0 = _normal.scalarProduct(_displace);
	float t = _normal.dotProduct(p0.plus(r.getOrigin().negative()));
	t = t / (r.getDirection().dotProduct(_normal));
	if (t > 0.0 && ((t < minDepth) || (minDepth < 0))) {
		h.hit(true, t, r.getOrigin().plus(r.getDirection().scalarProduct(t)), r.getDirection(), _normal, _m);
	}
	return h;
}

void Plane::setMaterial(Material mat) {
	_m = mat;
}

Material Plane::getMaterial() {
	return(_m);
}