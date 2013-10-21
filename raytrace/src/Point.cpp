/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Differentiating Points from Vectos
 */
#include "Point.h"
#include <iostream>

Point3d::Point3d() {_x = 0.0; _y = 0.0; _z = 0.0;}
Point3d::Point3d(float x, float y, float z) {_x = x; _y = y; _z = z;}
Point3d::Point3d(float p[3]){_x = p[0]; _y = p[1]; _z = p[2];}
void Point3d::setX(float x) {_x = x;}
void Point3d::setY(float y) {_y = y;}
void Point3d::setZ(float z) {_z = z;}
float Point3d::getX() {return _x; }
float Point3d::getY() {return _y; }
float Point3d::getZ() {return _z; }
Point3d Point3d::translate(float x, float y, float z) {
	return (Point3d((_x + x), (_y + y), (_z + z))); 
}

std::ostream& operator <<( std::ostream &out, const Point3d &p ){
	p.write( out );
	return( out );
}

void Point3d::write( std::ostream &out ) const{
	out << "(" << _x << ", " << _y << ", " << _z << ")";
}