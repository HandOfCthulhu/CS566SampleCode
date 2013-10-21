/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * For storing and dealing with colors
 */
#ifndef _COLOR_H_
#define _COLOR_H_
#include <iostream>
class Color {
public:
	Color ();
	Color (float r, float g, float b);
	Color (float col[3]);
	void setR(float r);
	void setG(float g);
	void setB(float b);
	float getR();
	float getG();
	float getB();
	Color add(Color scalars, Color color);
	bool isBlack();

	void write( std::ostream &out ) const;

private:
	float _r;
	float _g;
	float _b;
};
std::ostream& operator <<( std::ostream &out, const Color &c );
#endif