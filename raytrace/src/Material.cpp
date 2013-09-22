/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#include "Material.h"
#include "Vector3d.h"
#include <iostream>

Material::Material( ) {
	_diffColor = Vector3d();
	_specColor = Vector3d();
	_reflectColor = Vector3d();
	_transColor = Vector3d();
	_exponent = 0.0;
	_indxRefract = 0.0;

}

Material::Material(Vector3d diffuseColor, float specularExponent, Vector3d specColor, Vector3d reflecColor, Vector3d transColor, float refractInd) {
		_diffColor = diffuseColor;
		_exponent = specularExponent;
		_specColor = specColor;
		_reflectColor = reflecColor;
		_transColor = transColor;
		_indxRefract = refractInd;
}

void Material::setSpecularColor(Vector3d color) {
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

void Material::setDiffColor(Vector3d color) {
	_diffColor = color;
}

void Material::setReflectiveColor(Vector3d color) {
	_reflectColor = color;
}

void Material::setRefractionIndex(float refractInd) {
	_indxRefract = refractInd;
}

void Material::setTransparencyColor(Vector3d color) {
	_transColor = color;
}

Vector3d Material::getDiffuseColor() {
	return(_diffColor);
}

Vector3d Material::getSpecularColor() {
	return(_specColor);
}

Vector3d Material::getReflectiveColor() {
	return(_reflectColor);
}

Vector3d Material::getTransparencyColor() {
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
	out << "\treflectColor: " << _transColor << std::endl;
	out << "\texp: " << _exponent << std::endl;
	out << "\tindRefract: " << _indxRefract << std::endl;
}

Material::~Material( ) {
}