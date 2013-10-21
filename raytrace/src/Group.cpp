/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Group of objects, also includes interception checks and shading
 */

#include "Group.h"
#include <iostream>
#include "Color.h"
#include "Point.h"

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

//This is the really important function, gets the intersections and the final colors of the rays
//r - ray we are checking against
//recDepth - current recursion depth
//maxDepth - maximum recursion depth
Hit Group::intersect(Ray r, int recDepth, const int maxDepth) {
	Hit h;
	Hit closest;
	float minDepth = -1;

	Vector3d normalLightUnitVec;
	Vector3d normalCameraUnitVec;
	Vector3d lightToPointUnitVec;
	Vector3d pointToLightUnitVec;
	Vector3d lightReflectionUnitVec;
	Vector3d viewReflectionUnitVec;
	Vector3d pointToViewUnitVec;
	Vector3d viewToPointUnitVec;

	Color finalColor;
	float finalR = 0.0;
	float finalG = 0.0;
	float finalB = 0.0;

	if (debugMode) {
		std::cout << "number of objects to check against: " << _objects.size() << std::endl;
	}
	for (size_t i = 0; i < _objects.size(); i++) {
		h = Hit();
		if (debugMode) {
			std::cout << "Checking Ray against object#" << i << std::endl;
		}
		h = (*_objects.at(i)).intersect(r, minDepth);

		if (h.didHit()) {
			if(r.getType() == shadow) {
				if (debugMode) {
					std::cout << "\tShadow Hit Detected against object " << i << std::endl;
				}
				return(h);
			}
			closest = Hit(h);
			minDepth = closest.getDepth();
			if (debugMode) {
				std::cout << "\tObject " << i << " Hit Detected t=" << minDepth << " location: " << closest.getHitLocation() << " normal: " << closest.getHitNormal() << std::endl;
			}
		}
	}

	if(closest.didHit()) {
		viewToPointUnitVec = closest.getHitVector();
		Vector3d temp (r.getOrigin(), closest.getHitLocation());
		pointToViewUnitVec = temp.normalized();
		normalCameraUnitVec = closest.getHitNormal();
		if (normalCameraUnitVec.dotProduct(pointToViewUnitVec) < 0) {
			normalCameraUnitVec=normalCameraUnitVec.negative();
		}
		if (r.getType() != shadow) {
			for (size_t i = 0; i < _lights.size(); i ++) {

				//CHECK IF WE ARE IN THIS LIGHT

				//TODO: Temporary placeholder for future area lighting/soft shadows
				float percentLit = 1.0;
				float attenuation = 1.0;


				Ray shadowRay;
				shadowRay.setType(shadow);
				pointToLightUnitVec = Vector3d(_lights.at(i).getPosition(), closest.getHitLocation());
				float distanceToLight = pointToLightUnitVec.getLength();
				
				pointToLightUnitVec.normalize();
				lightToPointUnitVec = pointToLightUnitVec.negative();
				shadowRay.setDirection(pointToLightUnitVec);
					
				normalLightUnitVec = closest.getHitNormal();
				if(normalLightUnitVec.dotProduct(pointToLightUnitVec) < 0) {
					normalLightUnitVec = normalLightUnitVec.negative();
				}

				//TODO: universal epsilon declaration
				Vector3d temp = normalLightUnitVec.scalarProduct(0.0001f);
				shadowRay.setOrigin(closest.getHitLocation().translate(temp.getX(), temp.getY(), temp.getZ()));

				if (debugMode) {
					std::cout << "normalLightUnitVec " << normalLightUnitVec << std::endl;
					std::cout << "ShadowRay: " << " o(" << shadowRay.getOrigin() << ") dir(" << shadowRay.getDirection() << ")" << std::endl;
				}

				Hit shadowHit;
				shadowHit = intersect(shadowRay, 0, 0);
				if (shadowHit.didHit() && (shadowHit.getDepth() < distanceToLight)) {
					if (debugMode) {
						std::cout << "Shadow Hit: T: " << shadowHit.getDepth() << " Point " << shadowHit.getHitLocation() << std::endl;
					}
				} else { //not in shadow, this light contributes to final color
					//BEGIN ATTENUATION
					Vector3d att = _lights.at(i).getAttenuation();
					attenuation = 1 / (att.getX() + att.getY()*distanceToLight + att.getZ()*distanceToLight*distanceToLight);
					if (debugMode) {
						std::cout << "Attenuation " << att << std::endl;
					}
					//END ATTENUATION


					// BEGIN SPECULAR COLOR
					// Full Reflection Phong Shading
					//R = 2n(n.L)-L
					if (debugMode) {
						std::cout << "Calculating specular. Point3d: " << closest.getHitLocation() << " Normal: " << normalLightUnitVec << "Light Position: " << _lights.at(i).getPosition() <<  " PointToLightVec: " << pointToLightUnitVec << std::endl;
					}
					Vector3d a = normalLightUnitVec.scalarProduct(pointToLightUnitVec.dotProduct(normalLightUnitVec)).scalarProduct(2);
					lightReflectionUnitVec = a.plus(pointToLightUnitVec.negative());
					lightReflectionUnitVec.normalize();
					float shiny = pointToViewUnitVec.dotProduct(lightReflectionUnitVec);
					

					//Blinn Half-Vector Approximation
					/*
					Vector3d H = Point3dToLightUnitVec.plus(viewToPoint3dUnitVec);
					H = H.scalarProduct(0.5);
					float shiny = normalLightUnitVec.dotProduct(H);
					
					if (debugMode) {
						std::cout << "H: " << H << std::endl;
						std::cout << "normal : " << normalLightUnitVec << std::endl;
					}*/
					
					if (shiny < 0.0) {
						shiny = 0.0;
					}

					float e = closest.getMaterial().getSpecularExponent();

					if (debugMode) {
						std::cout << "Shiny (postfix): " << shiny << std::endl;
						std::cout << "Exponent: " << e << std::endl;
					}
					finalR += percentLit * attenuation * (_lights.at(i).getColor().getR() * closest.getMaterial().getSpecularColor().getR() * pow(shiny, e));
					finalG += percentLit * attenuation * (_lights.at(i).getColor().getG() * closest.getMaterial().getSpecularColor().getG() * pow(shiny, e));
					finalB += percentLit * attenuation * (_lights.at(i).getColor().getB() * closest.getMaterial().getSpecularColor().getB() * pow(shiny, e));
					//END SPECULAR COLOR

					if (debugMode) {
						std::cout << "Post Specular Color (" << finalR << ", " << finalG << ", " << finalB << ")" << std::endl;
					}

					//BEGIN DIFFUSE COLOR
					float shade = pointToLightUnitVec.dotProduct(normalLightUnitVec);
					if(shade < 0.0)
					{
						shade = 0.0;
					}
					finalR += percentLit * attenuation * (shade * _lights.at(i).getColor().getR() * closest.getMaterial().getDiffuseColor().getR());
					finalG += percentLit * attenuation * (shade * _lights.at(i).getColor().getG() * closest.getMaterial().getDiffuseColor().getG());
					finalB += percentLit * attenuation * (shade * _lights.at(i).getColor().getB() * closest.getMaterial().getDiffuseColor().getB());
					//END DIFFUSE COLOR

					if (debugMode) {
						std::cout << "Post Diffuse Color (" << finalR << ", " << finalG << ", " << finalB << ")" << std::endl;
					}
				}
			}
			finalR = finalR/getNumberOfLights();
			finalG = finalG/getNumberOfLights();
			finalB = finalB/getNumberOfLights();

			//Peg light values at 0 or 1
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

			if (recDepth < maxDepth) {
				if (debugMode) {
					std::cout << "Reflection/Refraction" << std::endl;
				}
				if (!closest.getMaterial().getReflectiveColor().isBlack()) {
					
					if (debugMode) {
						std::cout << "In Reflection Code" << std::endl;
					}

					//generate reflection array
					float temp1 = (pointToViewUnitVec.dotProduct(normalCameraUnitVec)) * 2.0f;
					Vector3d a = normalCameraUnitVec.scalarProduct(temp1);
					Vector3d reflectDir = a.plus(pointToViewUnitVec.negative());
					reflectDir.normalize();

					Vector3d blarg = normalCameraUnitVec.scalarProduct(0.0001f);

					Ray reflectionRay(closest.getHitLocation().translate(blarg.getX(), blarg.getY(), blarg.getZ()), reflectDir);
					reflectionRay.setType(reflection);
					if (debugMode) {
						std::cout << "Reflection: I: " << pointToViewUnitVec << " N: " << normalCameraUnitVec << " R: " << reflectDir << std::endl;
						std::cout << "Reflection Ray: o: " << reflectionRay.getOrigin() << " d: " << reflectionRay.getDirection() << std::endl;
					}

					//test for reflection hit
					Hit reflectHit;
					reflectHit = intersect(reflectionRay, recDepth+1, maxDepth);

					//mix colors from reflection vector and our specular/diffuse base
					Color reflectColor = reflectHit.getColor();
					float reflectR = closest.getMaterial().getReflectiveColor().getR();
					float reflectG = closest.getMaterial().getReflectiveColor().getG();
					float reflectB = closest.getMaterial().getReflectiveColor().getB();

					finalR = (float)((1.0-reflectR) * finalR) + (reflectR * reflectHit.getColor().getR());
					finalG = (float)((1.0-reflectG) * finalG) + (reflectG * reflectHit.getColor().getG());
					finalB = (float)((1.0-reflectB) * finalB) + (reflectB * reflectHit.getColor().getB());
				}
				if (!closest.getMaterial().getTransparencyColor().isBlack()) {
					if(debugMode) {
						std::cout << "In Transparency Code" << std::endl;
					}
					//generate refraction ray
					Vector3d blarg2 = viewToPointUnitVec.scalarProduct(0.0001f);
					Point3d refractOrigin = closest.getHitLocation().translate(blarg2.getX(), blarg2.getY(), blarg2.getZ());
					//TODO: refract ray direction based on material refraction index
					Ray refraction_ray(refractOrigin, viewToPointUnitVec);
					refraction_ray.setType(refraction);

					//test for refraction hit
					Hit refractHit;
					refractHit = intersect(refraction_ray, recDepth+1, maxDepth);

					//mix colors from refraction vector and the specular/diffuse/reflection
					float translucentR = closest.getMaterial().getTransparencyColor().getR();
					float translucentG = closest.getMaterial().getTransparencyColor().getG();
					float translucentB = closest.getMaterial().getTransparencyColor().getB();

					finalR = (float)((1.0-translucentR) * finalR) + (translucentR * refractHit.getColor().getR());
					finalG = (float)((1.0-translucentG) * finalG) + (translucentG * refractHit.getColor().getG());
					finalB = (float)((1.0-translucentB) * finalB) + (translucentB * refractHit.getColor().getB());
				}
			}
			finalColor.setR(finalR);
			finalColor.setG(finalG);
			finalColor.setB(finalB);

			closest.setColor(finalColor);
		}
	} else {
		//This was a shadow ray, we don't care what color the hit is.
		closest.setColor(Color());
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
	for (size_t i = 0; i < _lights.size(); i++) {
		out << _lights.at(i) << std::endl;
	}
}