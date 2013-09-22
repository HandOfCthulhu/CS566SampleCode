#include <iostream>
#include "RTObject.h"
std::ostream& operator <<( std::ostream &out, const RTObject &o ) {
	o.write( out );
	return( out );
}