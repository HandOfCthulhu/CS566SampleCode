/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 * This class just stores the material information for use in objects and retrieval during the intersection shading code
 */

#include "Material.h"
#include "Vector3d.h"
#include <iostream>

Material::Material( ) {
	_diffColor = Color();
	_specColor = Color();
	_reflectColor = Color();
	_transColor = Color();
	_exponent = 0.0;
	_indxRefract = 0.0;

}

Material::Material(Color diffuseColor, float specularExponent, Color specColor, Color reflecColor, Color transColor, float refractInd) {
		_diffColor = diffuseColor;
		_exponent = specularExponent;
		_specColor = specColor;
		_reflectColor = reflecColor;
		_transColor = transColor;
		_indxRefract = refractInd;
}

void Material::setSpecularColor(Color color) {
	_specColor = color;
}

void Material::setExponent(float exp){
	_exponent = exp;
}

float Material::getIndexOfRefraction(){
	return(_indxRefract);
}

float Material::getSpecularExponent(){
	return(_exponent);
}

void Material::setDiffColor(Color color) {
	_diffColor = color;
}

void Material::setReflectiveColor(Color color) {
	_reflectColor = color;
}

void Material::setRefractionIndex(float refractInd) {
	_indxRefract = refractInd;
}

void Material::setTransparencyColor(Color color) {
	_transColor = color;
}

Color Material::getDiffuseColor() {
	return(_diffColor);
}

Color Material::getSpecularColor() {
	return(_specColor);
}

Color Material::getReflectiveColor() {
	return(_reflectColor);
}

Color Material::getTransparencyColor() {
	return(_transColor);
}

std::ostream& operator <<( std::ostream &out, const Material &m ){
	m.write( out );
	return( out );
}

void Material::write( std::ostream &out ) const {
	out << "Material:" << std::endl;
	out << "\tdiffColor: " << _diffColor << std::endl;
	out << "\tspecColor: " << _specColor << std::endl;
	out << "\ttransColor: " << _transColor << std::endl;
	out << "\treflectColor: " << _reflectColor << std::endl;
	out << "\texp: " << _exponent << std::endl;
	out << "\tindRefract: " << _indxRefract << std::endl;
}

Material::~Material( ) {
}