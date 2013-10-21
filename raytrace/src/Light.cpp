/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 * This class just stores the light information for use in shading code
 */
#include "Light.h"
#include "Point.h"
#include <iostream>

Light::Light() {
	_mode = Point;
	_pos = Point3d();
	_dir = Vector3d();
	_color = Color();
	_angle = 0.0;
	_att = Vector3d(1,0,0);
}

Light::Light(Point3d position, Color color, Vector3d attenuation) {
	_mode = Point;
	_pos = position;
	_color = color;
	_dir = Vector3d();
	_angle = 0.0;
	_att = attenuation;
}

Light::Light(Point3d position, Vector3d direction, Color color, float angle, Vector3d attenuation) {
	_mode = directional;
	_pos = position;
	_dir = direction;
	_color = color;
	_angle = angle;
	_att = attenuation;
}

Point3d Light::getPosition() {
	return(_pos);
}

Vector3d Light::getDirection() {
	return(_dir);
}

Color Light::getColor() {
	return(_color);
}

float Light::getAngle() {
	return(_angle);
}

Vector3d Light::getAttenuation() {
	return(_att);
}

LightMode Light::getMode() {
	return(_mode);
}

void Light::setposition(Point3d position) {
	_pos = position;
}

void Light::setDirection(Vector3d direction) {
	_dir = direction;
}

void Light::setColor(Color color) {
	_color = color;
}

void Light::setAngle(float angle) {
	_angle = angle;
}

void Light::setAttenuation(Vector3d attenuation) {
	_att = attenuation;
}

void Light::setMode(LightMode mode) {
	_mode = mode;
}

std::ostream& operator <<( std::ostream &out, const Light &l ){
	l.write( out );
	return( out );
}

void Light::write( std::ostream &out ) const{
	if (_mode == Point) {
		out << "PointLight: " << std::endl;
	}
	else if (_mode == directional) {
		out << "DirectionalLight: " << std::endl;
	}
	out << "\tPosition: " << _pos << std::endl;
	out << "\tColor: " << _color << std::endl;
	out << "\tAttenuation: " << _att << std::endl;
	out << "\tDirection: " << _dir << std::endl;
	out << "\tAngle: " << _angle << std::endl;
}