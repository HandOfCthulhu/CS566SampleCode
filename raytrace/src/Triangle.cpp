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

Hit Triangle::intersect(Ray r, float minDepth) {
	Hit h = Hit();

	Vector3d E1= _b.plus(_a.negative());
	Vector3d E2=_c.plus(_a.negative());
	Vector3d P=r.getDirection().crossProduct(E2);
	float A=E1.dotProduct(P);
	if (A == 0.0) {
		return h;
	}

	float F = 1/A;
	Vector3d S = r.getOrigin().plus(_a.negative());
	float U = S.dotProduct(P) * F;
	if (U < 0.0 || U > 1.0) {
		return h;
	}

	Vector3d Q=S.crossProduct(E1);
	float V = r.getDirection().dotProduct(Q) * F;
	if(V < 0.0 || V > 1.0) {
		return h;
	}
	float T = E2.dotProduct(Q)*F;
	
	if ((minDepth > 0) && (T > minDepth)){
		return h;
	}

	Vector3d hitPoint = (r.getOrigin().plus(r.getDirection().scalarProduct(T)));
	h.hit(true, T, hitPoint, r.getDirection(), P.normalized(), _m);
	//h.p=rayeval(r,t);
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