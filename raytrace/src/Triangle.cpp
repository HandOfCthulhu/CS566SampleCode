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
	Vector3d E1 (_b, _a);
	Vector3d E2 (_c, _a);
	Vector3d pvec = r.getDirection().crossProduct(E2);
	double det = E1.dotProduct(pvec);

	if ((det > -0.001f) && (det < 0.001f)) {
		if (debugMode) {
			std::cout << "No Hit Det" << std::endl;
		}
		return h;
	}

	float invDet = 1 / det;

	Vector3d tvec (r.getOrigin(), _a);
	double u = tvec.dotProduct(pvec) * invDet;
	if ((u < 0) || (u > 1)) {
		if (debugMode) {
			std::cout << "No Hit U" << std::endl;
		}
		return h;
	}

	Vector3d qvec = tvec.crossProduct(E1);
	double v = qvec.dotProduct(r.getDirection()) * invDet;
	if ((v < 0) || (v > 1) || (u+v > 1)) {
		if (debugMode) {
			std::cout << "No Hit V" << std::endl;
		}
		return h;
	}

	float t = E2.dotProduct(qvec) * invDet;

	if ((t < 0) || ((minDepth > 0) && (t > minDepth))){
		if (debugMode) {
			std::cout << "No Hit Obstructed" << std::endl;
		}
		return h;
	}

	Vector3d temp = r.getDirection().scalarProduct(t);
	Point3d hitPoint = (r.getOrigin().translate(temp.getX(), temp.getY(), temp.getZ()));
	h.hit(true, t, hitPoint, r.getDirection(), E1.crossProduct(E2).normalized(), _m);
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