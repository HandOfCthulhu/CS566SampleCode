#ifndef _VECTOR3D_H
#define _VECTOR3D_H
class Vector3d	{
	public:
		Vector3d(void);
		Vector3d(float x, float y, float z);
		float dotProduct(Vector3d operand);
		Vector3d crossProduct(Vector3d operand);
		Vector3d scalarProduct(float scalar);
		float getX();
		float getY();
		float getZ();
		float getLength();
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void normalize();
		Vector3d normalized();
		~Vector3d(void);
	private:
		float _x;
		float _y;
		float _z;
};
#endif
