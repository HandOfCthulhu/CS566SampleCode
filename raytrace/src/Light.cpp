#include "Light.h"

Light::Light() {
	_mode = point;
	_pos = Vector3d();
	_dir = Vector3d();
	_color = Vector3d();
	_angle = 0.0;
	_att = Vector3d();
}

Light::Light(Vector3d position, Vector3d color) {
	_mode = point;
	_pos = position;
	_color = color;
	_dir = Vector3d();
	_angle = 0.0;
	_att = Vector3d();
}

Light::Light(Vector3d position, Vector3d direction, Vector3d color, float angle, Vector3d attenuation) {
	_mode = directional;
	_pos = position;
	_dir = direction;
	_color = color;
	_angle = angle;
	_att = attenuation;
}

Vector3d Light::getPosition() {
	return(_pos);
}

Vector3d Light::getDirection() {
	return(_dir);
}

Vector3d Light::getColor() {
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

void Light::setposition(Vector3d position) {
	_pos = position;
}

void Light::setDirection(Vector3d direction) {
	_dir = direction;
}

void Light::setColor(Vector3d color) {
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