/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 * This class just stores the light information for use in shading code
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Vector3d.h"
#include "Point.h"
#include "Color.h"

enum LightMode { Point, directional };
class Light {
	public:
		Light();
		Light(Point3d position, Color color, Vector3d attenuation);
		Light(Point3d position, Vector3d direction, Color color, float angle, Vector3d attenuation);

		Point3d getPosition();
		Vector3d getDirection();
		Color getColor();
		float getAngle();
		Vector3d getAttenuation();
		LightMode getMode();
		void setposition(Point3d position);
		void setDirection(Vector3d direction);
		void setColor(Color color);
		void setAngle(float angle);
		void setAttenuation(Vector3d attenuation);
		void setMode(LightMode mode);

		bool debugMode;

	private:
		LightMode _mode;
		Point3d _pos;
		Vector3d _dir;
		Color _color;
		float _angle;
		Vector3d _att;

};
#endif