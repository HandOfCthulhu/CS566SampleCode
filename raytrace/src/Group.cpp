/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 *
 */

#include "Group.h"
#include <iostream>

Group::Group() {
	_objects = std::vector<RTObject*>();
	_numObjects = 0;
}

Group::~Group() {
}

void Group::addObject(RTObject* obj) {
	_numObjects++;
	_objects.push_back(obj);
}

Hit Group::intersect(Ray r) {
	Hit h = Hit();
	return (h);
}

std::ostream& operator <<( std::ostream &out, const Group &g ) {
	g.write( out );
	return( out );
}

void Group::write( std::ostream &out ) const {
	out << "Group: " << std::endl;
	for (int i = 0; i < _numObjects; i++) { 
		out << (*(_objects.at(i))) << std::endl;
	}
}