/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Differentiating Points from Vectors
 */
#ifndef _Point3d3d_H_
#define _Point3d3d_H_
#include <iostream>

class Point3d {
public:
	Point3d();
	Point3d(float x, float y, float z);
	Point3d(float p[3]);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float getX();
	float getY();
	float getZ();
	Point3d translate(float x, float y, float z);

	void write( std::ostream &out ) const;

private:
	float _x;
	float _y;
	float _z;
};

std::ostream& operator <<( std::ostream &out, const Point3d &p );

#endif