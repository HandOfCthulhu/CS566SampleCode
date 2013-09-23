#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Vector3d.h"
enum LightMode { point, directional };
class Light {
	public:
		Light();
		Light(Vector3d position, Vector3d color);
		Light(Vector3d position, Vector3d direction, Vector3d color, float angle, Vector3d attenuation);

		Vector3d getPosition();
		Vector3d getDirection();
		Vector3d getColor();
		float getAngle();
		Vector3d getAttenuation();
		LightMode getMode();
		void setposition(Vector3d position);
		void setDirection(Vector3d direction);
		void setColor(Vector3d color);
		void setAngle(float angle);
		void setAttenuation(Vector3d attenuation);
		void setMode(LightMode mode);

	private:
		LightMode _mode;
		Vector3d _pos;
		Vector3d _dir;
		Vector3d _color;
		float _angle;
		Vector3d _att;

};
#endif