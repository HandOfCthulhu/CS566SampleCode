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
Hit Sphere::intersect(Ray r) {
	Hit h = Hit();
	return h;
}

void Sphere::write( std::ostream &out ) const{
	out << "Sphere: " << std::endl;
	out << "\tCenter: " << _pos << std::endl;
	out << "\tRadius: " << _rad << std::endl;
	out << _mat << std::endl;
}
