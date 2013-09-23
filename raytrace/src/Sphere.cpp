/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */
#include "Sphere.h"
#include <iostream>

Sphere::Sphere() {
	_mat = Material();
	_pos = Vector3d();
	_rad = 0.0;
}

Sphere::Sphere(Vector3d position, float radius, Material mat) {
	_mat = mat;
	_pos = position;
	_rad = radius;
}

Vector3d Sphere::getPosition() {
	return(_pos);
}

float Sphere::getRadius() {
	return(_rad);
}

Material Sphere::getMaterial() {
	return(_mat);
}

void Sphere::setPosition(Vector3d position) {
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
	Vector3d centerToViewOrigin = _pos.plus(r.getOrigin().negative());
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
	
    /*float a = r.getDirection().dotProduct(r.getDirection());
    float b = 2 * r.getDirection().dotProduct(r.getOrigin());
    float c = r.getOrigin().dotProduct(r.getOrigin()) - (_rad * _rad);
	float t;

    //Find discriminant
    float disc = b * b - 4 * a * c;*/
    
    if (discr < 0.0) {
		//imaginary root
		//std::cout << "Sphere Miss: " << "center: " << _pos  << " radius: " << _rad <<  std::endl;
        return h;
	}

    float distSqrt = sqrtf(discr); //disc
    //float q;
    //if (b < 0) {
    float t0 = (float)((-b - distSqrt)/(2.0*a));
	float t1 = (float)((-b + distSqrt)/(2.0*a));
	//}
    //else {
    //   q = (float)((-b + distSqrt)/2.0);
	//}

    // compute t0 and t1
    //float t0 = q / a;
    //float t1 = c / q;

	std::cout << "t0: " << t0 << std::endl;
	std::cout << "t1: " << t1 << std::endl;

    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0) {
        return h;
	}

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0)
    {
		t = t1;
    }
    // else the intersection point is at t0
    else
    {
        t = t0;
    }
	if ((t < minDepth) || (minDepth < 0.0)) {
		Vector3d hitPoint = (r.getOrigin().plus(r.getDirection().scalarProduct(t)));
		Vector3d sphereNormal = hitPoint.plus(_pos.negative());
		h.hit(true, t, hitPoint, r.getDirection(), sphereNormal, _mat);
	}
    return h;
	/*
	//Hit h = Hit();
	//
	//Vector3d directToCenter(r.getOrigin().plus(_pos.negative()));

 //   double foobar = 2 * ( directToCenter.dotProduct(r.getDirection() ));
 //   double discriminant = foobar * foobar - 4 * ( (directToCenter.dotProduct(directToCenter)) - (_rad*_rad) );  // The discriminant.

 //   if( discriminant < 0 ) // If the discriminant if negative no intersections exist
	//{
	//	return (h);
	//}

 //   double rootOfDiscriminant = sqrt( discriminant );
 //   double t = ( -foobar - rootOfDiscriminant ) / 2;

 //   if( t <= 0.0 ) {//check first intersection is "behind us"
	//	//check larger root to see if we are "inside of the sphere"
 //       t = ( rootOfDiscriminant - foobar )/2.0;
 //       if( t <= 0.0) { //sphere is behind us, so no intersection
	//		return h;
	//	}
 //       if( (t > minDepth) && (minDepth >= 0) ) //inside of sphere, but there is something closer than the inside of sphere
	//	{
	//		return h;
	//	}
	//}
 //   else
	//{
 //       // If first intersection is further away then our current closest hit, this hit is occluded
 //       if( (t > minDepth) && (minDepth >= 0) )
	//	{
	//		return h;
	//	}
	//}

 //   // It's a confirmed hit.  
	//// update hitinfo variable for the shader
	//Vector3d hitPoint = (r.getOrigin().plus(r.getDirection().scalarProduct((float)t)));
	//Vector3d normal = hitPoint.plus(_pos.negative()).normalized();
	//h.hit(true, (float)t, hitPoint, r.getDirection(), normal, _mat);
	//return h;
	*/
}

void Sphere::write( std::ostream &out ) const{
	out << "Sphere: " << std::endl;
	out << "\tCenter: " << _pos << std::endl;
	out << "\tRadius: " << _rad << std::endl;
	out << _mat << std::endl;
}
