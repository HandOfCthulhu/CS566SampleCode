/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 */

#include "Group.h"
#include <iostream>

Group::Group() {
	_objects = std::vector<RTObject*>();
	_lights = std::vector<Light>();
}

Group::~Group() {
}

void Group::addObject(RTObject* obj) {
	_objects.push_back(obj);
}

void Group::addLight(Light light) {
	_lights.push_back(light);
}

void Group::setBGColor(Vector3d color){
	_bgColor = color;
}


Hit Group::intersect(Ray r, int recDepth, const int maxDepth) {
	Hit h = Hit();
	Hit closest = Hit();
	float minDepth = -1;
	Vector3d finalColor = Vector3d();
	float finalR = 0.0;
	float finalG = 0.0;
	float finalB = 0.0;

	std::cout << "number of objects to check against: " << _objects.size() << std::endl;
	for (size_t i = 0; i < _objects.size(); i++) {
		h = Hit();
		std::cout << "Checking Ray against object#" << i << std::endl;
		h = (*_objects.at(i)).intersect(r, minDepth);

		if (h.didHit()) {
			if(r.getType() == shadow) {
				std::cout << "Shadow Hit Detected against object " << i << std::endl;
				return(h);
			}
			closest = Hit(h);
			minDepth = closest.getDepth();
			std::cout << "Object " << i << " Hit Detected t=" << minDepth << " location: " << closest.getHitLocation() << std::endl;
		}
	}

	if(closest.didHit()) {
		if (r.getType() != shadow) {
			if (recDepth < maxDepth) {
				for (size_t i = 0; i < _lights.size(); i ++) {
					float percentLit = 1.0;
					Ray shadowRay = Ray();
					shadowRay.setType(shadow);
					Vector3d shadowRayDir = _lights.at(i).getPosition().plus(closest.getHitLocation().negative());
					shadowRayDir.normalize();
					shadowRay.setDirection(shadowRayDir);
					
					Vector3d hitNormal = closest.getHitNormal();
					if(hitNormal.dotProduct(closest.getHitVector().negative()) < 0) {
						hitNormal = hitNormal.negative();
					}
					//Vector3d shadowEpsilon = 
					shadowRay.setOrigin(closest.getHitLocation().plus(hitNormal.scalarProduct(0.0001f)));
					//shadowRay.setOrigin(closest.getHitLocation().plus(hitNormal.scalarProduct(0.00001f)));
					std::cout << "ShadowRay: " << " o(" << shadowRay.getOrigin() << ") dir(" << shadowRay.getDirection() << ")" << std::endl;
					Hit shadowHit = Hit();
					shadowHit = intersect(shadowRay, 0, 0);
					if (shadowHit.didHit()) {
						finalR += _bgColor.getX();
						finalG += _bgColor.getY();
						finalB += _bgColor.getZ();
						std::cout << "Shadow Hit Color: (" << finalR << ", " << finalG << ", " << finalB << ")" << std::endl;
					} else {
						Vector3d H = shadowRayDir.plus(r.getDirection());
						std::cout << "H1: " << H << std::endl;
						H = H.scalarProduct(0.5);
						std::cout << "H2: " << H << std::endl;
						H.normalize();
						std::cout << "H3: " << H << std::endl;
						std::cout << "normal : " << hitNormal << std::endl;
						float shiny = hitNormal.dotProduct(H);
						std::cout << "Shiny: " << shiny << std::endl;
						if (shiny < 0.0) {
							shiny = 0.0;
						}
						std::cout << "Shiny (postfix): " << shiny << std::endl;
						float e = closest.getMaterial().getSpecularExponent();
						std::cout << "Exponent: " << e << std::endl;
						finalR += percentLit * (_lights.at(i).getColor().getX() * closest.getMaterial().getSpecularColor().getX() * pow(shiny, e));
						finalG += percentLit * (_lights.at(i).getColor().getY() * closest.getMaterial().getSpecularColor().getY() * pow(shiny, e));
						finalB += percentLit * (_lights.at(i).getColor().getZ() * closest.getMaterial().getSpecularColor().getZ() * pow(shiny, e));
						//END SPECULAR COLOR
						std::cout << "Post Specular Color (" << finalR << ", " << finalG << ", " << finalB << ")" << std::endl;

						//BEGIN DIFFUSE COLOR
						float shade = shadowRayDir.dotProduct(hitNormal);
						if(shade < 0.0)
						{
							shade = 0.0;
						}
						finalR += percentLit * (shade * _lights.at(i).getColor().getX() * closest.getMaterial().getDiffuseColor().getX());
						finalG += percentLit * (shade * _lights.at(i).getColor().getY() * closest.getMaterial().getDiffuseColor().getY());
						finalB += percentLit * (shade * _lights.at(i).getColor().getZ() * closest.getMaterial().getDiffuseColor().getZ());
						std::cout << "Post Diffuse Color (" << finalR << ", " << finalG << ", " << finalB << ")" << std::endl;
					}
				}
				finalR = finalR/getNumberOfLights();
				finalG = finalG/getNumberOfLights();
				finalB = finalB/getNumberOfLights();

				if (finalR > 1.0) {
					finalR = 1.0;
				} else if (finalR < 0.0) {
					finalR = 0.0;
				}
				if (finalG > 1.0) {
					finalG = 1.0;
				} else if (finalG < 0.0) {
					finalG = 0.0;
				}
				if (finalB > 1.0) {
					finalB = 1.0;
				} else if (finalB < 0.0) {
					finalB = 0.0;
				}

				if (closest.getMaterial().getReflectiveColor().getLength() > 0) {
					//generate reflection array
					std::cout << "In Reflection Code" << std::endl;
					Vector3d normal = closest.getHitNormal();
					Vector3d primary = closest.getHitVector();
					if( primary.dotProduct(normal) < 0.0 ) {
						normal = normal.negative();
					}
					float temp1 = (primary.dotProduct(normal)) * 2.0f;
					Vector3d temp = normal.plus(primary.negative());
					Vector3d reflectDir = temp.scalarProduct(temp1);
					reflectDir.normalize();

					Ray reflection_ray = Ray(closest.getHitLocation().plus(normal.scalarProduct(FLT_EPSILON)), reflectDir);
					reflection_ray.setType(reflection);
			
					Hit reflectHit = intersect(reflection_ray, recDepth+1, maxDepth);
					Vector3d reflectColor = reflectHit.getColor();
					float reflectR = closest.getMaterial().getReflectiveColor().getX();
					float reflectG = closest.getMaterial().getReflectiveColor().getY();
					float reflectB = closest.getMaterial().getReflectiveColor().getZ();

					finalR = (float)((1.0-reflectR) * finalR) + (reflectR * reflectHit.getColor().getX());
					finalG = (float)((1.0-reflectG) * finalG) + (reflectG * reflectHit.getColor().getY());
					finalB = (float)((1.0-reflectB) * finalB) + (reflectB * reflectHit.getColor().getZ());
				}
				if (closest.getMaterial().getTransparencyColor().getLength() > 0.0) {
					//generate refraction ray
					//intersect(refraction_ray, recDepth+1, maxDepth);
					//TODO: TRANSLUCENCY
				}


				finalColor.setX(finalR);
				finalColor.setY(finalG);
				finalColor.setZ(finalB);
			
				closest.setColor(finalColor);
			} else {
				closest.setColor(closest.getMaterial().getDiffuseColor());
			}
		}
	} else {
		closest.setColor(_bgColor);
	}

	return (closest);
}

std::ostream& operator <<( std::ostream &out, const Group &g ) {
	g.write( out );
	return( out );
}

int Group::getNumberOfLights() {
	return(_lights.size());
}

int Group::getNumberOfObjects() {
	return(_objects.size());
}

void Group::write( std::ostream &out ) const {
	out << "Group: " << std::endl;
	for (size_t i = 0; i < _objects.size(); i++) { 
		out << (*(_objects.at(i))) << std::endl;
	}
}