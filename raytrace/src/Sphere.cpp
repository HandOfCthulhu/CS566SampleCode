/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Object describing a sphere
 */
#include "Sphere.h"
#include <iostream>
#include "Point.h"

Sphere::Sphere() {
	_mat = Material();
	_pos = Point3d();
	_rad = 0.0;
}

Sphere::Sphere(Point3d position, float radius, Material mat) {
	_mat = mat;
	_pos = position;
	_rad = radius;
}

Point3d Sphere::getPosition() {
	return(_pos);
}

float Sphere::getRadius() {
	return(_rad);
}

Material Sphere::getMaterial() {
	return(_mat);
}

void Sphere::setPosition(Point3d position) {
	_pos = position;
}

void Sphere::setRadius(float radius) {
	_rad = radius;
}

void Sphere::setMaterial(Material material) {
	_mat = material;
}

Hit Sphere::intersect(Ray r, float minDepth) {
	Hit h;
	//Vector3d centerToViewOrigin = _pos.plus(r.getOrigin().negative());
	float t;

	float x0 = r.getOrigin().getX();
	float y0 = r.getOrigin().getY();
	float z0 = r.getOrigin().getZ();

	float dx = r.getDirection().getX();
	float dy = r.getDirection().getY();
	float dz = r.getDirection().getZ();

	float cx = _pos.getX();
	float cy = _pos.getY();
	float cz = _pos.getZ();

	float a = dx*dx + dy*dy + dz*dz;
	float b = 2*dx*(x0-cx) + 2*dy*(y0-cy) + 2*dz*(z0-cz);
	float c =  cx*cx + cy*cy + cz*cz + x0*x0 + y0*y0 + z0*z0 + (-2*(cx*x0 + cy*y0 + cz*z0)) - _rad*_rad;

	float discr = b * b - 4 * a * c;
    
    if (discr < 0.0) {
		//imaginary root
		if (debugMode) {
			std::cout << "\t\tSphere Miss: " << "center: " << _pos  << " radius: " << _rad <<  std::endl;
		}
        return h;
	}

    float distSqrt = sqrtf(discr); //disc

    float t0 = (float)((-b - distSqrt)/(2.0*a));
	float t1 = (float)((-b + distSqrt)/(2.0*a));

	if (debugMode) {
		std::cout << "\t\tt0: " << t0 << std::endl;
		std::cout << "\t\tt1: " << t1 << std::endl;
	}

    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    if (t1 < 0) {
        return h;
	}

    // if t0 is less than zero, the intersection Point3d is at t1
    if (t0 < 0)
    {
		t = t1;
    }
    // else the intersection Point3d is at t0
    else
    {
        t = t0;
    }
	if ((t < minDepth) || (minDepth < 0.0)) {
		Vector3d temp = r.getDirection().scalarProduct(t);
		Point3d hitPoint3d = (r.getOrigin().translate(temp.getX(), temp.getY(), temp.getZ()));
		Vector3d sphereNormal(hitPoint3d, _pos);
		h.hit(true, t, hitPoint3d, r.getDirection(), sphereNormal, _mat);
	}
    return h;
}

void Sphere::write( std::ostream &out ) const{
	out << "Sphere: " << std::endl;
	out << "\tCenter: " << _pos << std::endl;
	out << "\tRadius: " << _rad << std::endl;
	out << _mat << std::endl;
}
