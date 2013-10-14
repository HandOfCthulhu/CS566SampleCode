/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Abstract class describing all possible objects for ray intercepts
 */

#include <iostream>
#include "RTObject.h"
std::ostream& operator <<( std::ostream &out, const RTObject &o ) {
	o.write( out );
	return( out );
}