#include "Color.h"
#include <iostream>

Color::Color () { _r = 0.0; _g = 0.0; _b = 0.0; }
Color::Color (float r, float g, float b) {_r = r; _g = g; _b = b;}
Color::Color (float col[3]) {_r = col[0]; _g = col[1]; _b = col[2];}
void Color::setR(float r) {_r = r;}
void Color::setG(float g) {_g = g;}
void Color::setB(float b) {_b = b;}
float Color::getR() { return _r;}
float Color::getG() { return _g;}
float Color::getB() { return _b;}
Color Color::add(Color scalars, Color color) {
	float r = ((1-scalars.getR()) * _r) + ((scalars.getR()) * color.getR());
	float g = ((1-scalars.getG()) * _g) + ((scalars.getG()) * color.getG());
	float b = ((1-scalars.getB()) * _b) + ((scalars.getB()) * color.getB());
	return (Color(r, g, b));
}

std::ostream& operator <<( std::ostream &out, const Color &c ){
	c.write( out );
	return( out );
}

void Color::write( std::ostream &out ) const{
	out << "(" << _r << ", " << _g << ", " << _b << ")";
}

bool Color::isBlack() {
	std::cout << _r << ", " << _g << ", " << _b << std::endl;
	return !((_r > 0.0) && (_g > 0.0) && (_b > 0.0));
}