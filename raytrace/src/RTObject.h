/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Abstract class describing all possible objects for ray intercepts
 */
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include <iostream>

#ifndef _RTOBJECT_H_
#define _RTOBJECT_H_


class RTObject {
public:
	virtual Hit intersect(Ray r, float minDepth) = 0;
	virtual void setMaterial(Material mat) = 0;
	virtual Material getMaterial() = 0;
	virtual void write( std::ostream &out ) const = 0;
};

std::ostream& operator <<( std::ostream &out, const RTObject &o );

#endif