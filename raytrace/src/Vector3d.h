/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_
#include <iostream>
class Vector3d	{
	public:
		Vector3d(void);
		Vector3d(float x, float y, float z);
		Vector3d(float vec[3]);
		float dotProduct(Vector3d operand);
		Vector3d crossProduct(Vector3d operand);
		Vector3d scalarProduct(float scalar);
		Vector3d plus(Vector3d operand);
		Vector3d negative();
		float getX();
		float getY();
		float getZ();
		float getLength();
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void normalize();

		void write( std::ostream &out ) const;

		Vector3d normalized();
		~Vector3d(void);
	private:
		float _x;
		float _y;
		float _z;
};
std::ostream& operator <<( std::ostream &out, const Vector3d &v );
#endif
