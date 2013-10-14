/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Object describing a triangle in the scene
 */

#include "Triangle.h"
#include <iostream>
#include "Point.h"

Triangle::Triangle(Point3d a, Point3d b, Point3d c, Material m) {
	_a = a;
	_b = b;
	_c = c;
	_m = m;
}

Hit Triangle::intersect(Ray r, float minDepth) {
	Hit h;

	Vector3d E1(_b, _a);
	Vector3d E2(_c, _a);
	Vector3d P=r.getDirection().crossProduct(E2);
	float A=E1.dotProduct(P);
	if (A == 0.0) {
		return h;
	}

	float F = 1/A;
	Vector3d S(r.getOrigin(), _a);
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

	Vector3d temp = r.getDirection().scalarProduct(T);
	Point3d hitPoint3d = (r.getOrigin().translate(temp.getX(), temp.getY(), temp.getZ()));
	h.hit(true, T, hitPoint3d, r.getDirection(), P.normalized(), _m);
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