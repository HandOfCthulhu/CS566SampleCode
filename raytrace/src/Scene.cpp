/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * Class is used to parse the scene files and set up all other objects
 */
/*
 * Copyright (c) 2005-2013 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: Scene.cpp 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#include "Scene.h"
#include "RTObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <string>

Scene::Scene( string inputFilename, string outputFilename, string depthFilename ) :
	myInputSceneFile( inputFilename ),
	myOutputFile( outputFilename ),
	myDepthFile( depthFilename ),
	myCamera( ),
	myBackgroundColor( (channel)0.0, (channel)0.0, (channel)0.0 ),
	lineNumber(0),
	tokenCount(0),
	length(0),
	i(0),
	j(0)
{
	myNumberOfMaterials = -1;
	materials = vector<Material>();
	myCurrentMaterial = Material();
	myGroup = Group();
}

Scene::~Scene( ){
	// Nothing to free.
}

Camera& Scene::camera( ){
	return( myCamera );
}

Pixel& Scene::backgroundColor( ){
	return( myBackgroundColor );
}

int Scene::numberOfMaterials( ){
	return( myNumberOfMaterials );
}

void Scene::setCurrentMaterial( int i ){
	if( i >= myNumberOfMaterials ){
	  throw( "Index out of range" );	
	}else{
		myCurrentMaterial = materials.at(i);
	}
}

Material Scene::currentMaterial( ){
	return( myCurrentMaterial );
}

Group Scene::group( ){
	return( myGroup );
}

string& Scene::inputSceneFile( ){
	return( myInputSceneFile );
}

string& Scene::outputFile( ){
	return( myOutputFile );
}

string& Scene::depthFile( ){
	return( myDepthFile );
}

bool Scene::hasInputSceneFilePath( void ){
	bool ret = true;
	if( myInputSceneFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasOutputFilePath( void ){
	bool ret = true;
	if( myOutputFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasDepthFilePath( void ){
	bool ret = true;
	if( myDepthFile == "" ){
		ret = false;
	}
	return( ret );
}

void Scene::setInputSceneFile( string file ){
	myInputSceneFile = file;
}

void Scene::setOutputFile( string file ){
	myOutputFile = file;
}

void Scene::setDepthFile( string file ){
	myDepthFile = file;
}

float Scene::parseFloat( ){
	float ret = (float)atof( currentToken );
	return( ret );
}

double Scene::parseDouble( ){
	double ret = (double)atof( currentToken );
	return( ret );
}

int Scene::parseInt( ){
	int ret = atoi( currentToken );
	return( ret );
}

void Scene::checkToken( const char *str, const char *stage  ){
	if( strcmp( currentToken, str ) != 0 ){
		cerr << stage << " parse error at line " << lineNumber << " token " << tokenCount << ": " << currentToken << endl;
		cerr << "Current line: " << currentLine << endl;
		cerr << "Expected \'" << str << "\'" << endl;
		exit( 1 );
	}
}

void Scene::parseCamera( ){
  nextToken( );
  if( strcmp(currentToken, "OrthographicCamera") == 0 ){
    parseOrthographicCamera( );
  }else if( strcmp(currentToken, "PerspectiveCamera") == 0 ){
    parsePerspectiveCamera();
  }else if( strcmp(currentToken, "SimplePerspectiveCamera") == 0 ){
    parseSimplePerspectiveCamera();
  }else{
  	checkToken( "OrthographicCamera | PerspectiveCamera | SimplePerspectiveCamera", "Camera" );
  }
}

void Scene::parseOrthographicCamera( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.
	float vec[3];
	checkToken( "OrthographicCamera", "Camera" );
	myCamera.setMode(orthographic);
	nextToken( );
	checkToken( "{", "Camera" );
	nextToken( );
	checkToken( "center", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	myCamera.setPosition(Point3d(vec));
	nextToken( );
	checkToken( "direction", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	myCamera.setDirection(Vector3d(vec).normalized());
	nextToken( );
	checkToken( "up", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	myCamera.setUpVector(Vector3d(vec).normalized());
	
	nextToken( );
	checkToken( "}", "Camera" );
}

void Scene::parseViewPlane( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.
	nextToken( );
	checkToken( "ViewPlane", "ViewPlane" );
	nextToken( );
	checkToken( "{", "ViewPlane" );
	nextToken( );
	checkToken( "width", "ViewPlane" );
	nextToken( );
	myCamera.setViewPlaneWidth(parseInt( ));

	nextToken( );
	checkToken( "height", "ViewPlane" );
	nextToken( );
	myCamera.setViewPlaneHeight(parseInt( ));

	nextToken( );
	checkToken( "pixelsize", "ViewPlane" );
	nextToken( );
	myCamera.setPixelSize(parseFloat( ));

	nextToken( );
	checkToken( "}", "ViewPlane" );
	myCamera.debugMode = debugMode;
}

void Scene::parseBackground( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.	
	float vec[3];
	nextToken( );
	checkToken( "Background", "Background" );
	nextToken( );
	checkToken( "{", "Background" );
	
	nextToken( );
	checkToken( "color", "Background" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	myBackgroundColor = Pixel(vec);
	myGroup.setBGColor(Vector3d(vec));
	nextToken( );
	checkToken( "}", "Background" );
}

void Scene::parsePhongMaterial() {
	float diffColor[3] = {0.0,0.0,0.0};
	float transColor[3] = {0.0,0.0,0.0};
	float reflectColor[3] = {0.0,0.0,0.0};
	float specColor[3] = {0.0,0.0,0.0};
	float indRefract = 0.0;
	float exp = 0.0;

	checkToken( "PhongMaterial", "PhongMaterial" );
	nextToken( );
	checkToken( "{", "PhongMaterial");
	nextToken( );
	checkToken( "diffuseColor", "PhongMaterial");
	
	for(int i = 0; i < 3; i++) {
		nextToken( );
		diffColor[i] = parseFloat ( );
	}
	
	while(strcmp(currentToken, "}") != 0) {
		nextToken( );
		if (strcmp(currentToken, "specularColor")== 0) {
			for (int i = 0; i < 3; i++) {
				nextToken();
				specColor[i] = parseFloat();
			}
		} else if (strcmp(currentToken, "exponent")==0) {
			nextToken();
			exp = parseFloat();
		} else if (strcmp(currentToken, "transparentColor")==0) {
			for(int i = 0; i < 3; i++) {
				nextToken();
				transColor[i] = parseFloat();
			}
		} else if (strcmp(currentToken, "reflectiveColor")==0) {
			for (int i = 0; i < 3; i++) {
				nextToken();
				reflectColor[i] = parseFloat();
			}
		} else if (strcmp(currentToken, "indexOfRefraction")==0) {
			nextToken();
			indRefract = parseFloat();
		} else if (strcmp(currentToken, "}") == 0) {
			//do nothing, you'll be exiting this loop
		} else {
			checkToken("specularColor | exponent | transparentColor | reflectiveColor | indexOfRefraction | }", "PhongMaterial");
		}
	}
	checkToken( "}", "PhongMaterial");
	Material newMaterial(Color(diffColor), exp, Color(specColor), Color(reflectColor), Color(transColor), indRefract); 
	newMaterial.debugMode = debugMode;
	materials.push_back(newMaterial);
}

void Scene::parseMaterials( ){
	nextToken( );
	checkToken("Materials", "Materials");
	nextToken( );
	checkToken("{", "Materials");
	nextToken();
	checkToken("numMaterials", "Materials");
	nextToken();
	myNumberOfMaterials = parseInt( );
	for (int i = 0; i < myNumberOfMaterials; i++) {
		nextToken();
		if( strcmp(currentToken, "PhongMaterial") == 0 ){
			parsePhongMaterial( );
		}else{
  			checkToken( "PhongMaterial", "Materials" );
		}
	}
	nextToken( );
	checkToken("}", "Materials" );
}

void Scene::parseGroup( ) {
	nextToken();
	checkToken("Group", "Group");
	nextToken();
	checkToken("{", "Group");
	nextToken();
	myGroup.debugMode = debugMode;
	checkToken("numObjects", "Group");
	nextToken();
	myNumberOfObjects = parseInt( );
	int i = 0;
	while (i < myNumberOfObjects) {
		nextToken();
		if (strcmp(currentToken, "MaterialIndex")==0) {
			nextToken();
			setCurrentMaterial(parseInt());
		} else if (strcmp(currentToken, "Plane")==0) {
			parsePlane();
			i++;
		} else if ( strcmp(currentToken, "Sphere") == 0) {
			parseSphere();
			i++;
		} else if ( strcmp(currentToken, "Triangle") == 0) {
			parseTriangle();
			i++;
		} else if (strcmp(currentToken, "TriangleMesh") == 0) {
			parseTriangleMesh();
			i++;
		} else if (strcmp(currentToken, "Group")==0) {
			parseGroup();
			i++;
		} else if (strcmp(currentToken, "Transform")==0) {
			parseTransform();
			i++;
		} else {
			checkToken( "Triangle | Sphere | Plane", "Group" );
		}
	}
	
	nextToken();
	checkToken("}", "Group");
}

void Scene::parseSphere( ) {
	float vec[3];
	float rad;
	checkToken("Sphere", "Sphere");
	nextToken();
	checkToken("{", "Sphere");
	nextToken();
	checkToken("center", "Sphere");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	nextToken();
	checkToken("radius", "Sphere");
	nextToken();
	rad = parseFloat();
	nextToken();
	checkToken("}", "Sphere");
	Sphere* newSphere = new Sphere(Point3d(vec), rad, myCurrentMaterial);
	newSphere->debugMode = debugMode;
	myGroup.addObject(newSphere);
}

void Scene::parsePlane() {
	float vec[3];
	float offset;
	checkToken("Plane", "Plane");
	nextToken();
	checkToken("{", "Plane");
	nextToken();
	checkToken("normal", "Plane");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	nextToken();
	checkToken("offset", "Plane");
	nextToken();
	offset = parseFloat();
	nextToken();
	checkToken("}", "Plane");
	Plane* newPlane = new Plane(Vector3d(vec).normalized(), offset, myCurrentMaterial);
	newPlane->debugMode = debugMode;
	myGroup.addObject(newPlane);
}

void Scene::parseTriangle( ) {
	float vecA[3];
	float vecB[3];
	float vecC[3];
	checkToken("Triangle", "Triangle");
	nextToken();
	checkToken("{", "Triangle");
	nextToken();
	checkToken("vertex0", "Triangle");
	for(int i = 0; i < 3; i++) {
		nextToken();
		vecA[i] = parseFloat();
	}
	nextToken();
	checkToken("vertex1", "Triangle");
	for(int i = 0; i < 3; i++) {
		nextToken();
		vecB[i] = parseFloat();
	}
	nextToken();
	checkToken("vertex2", "Triangle");
	for(int i = 0; i < 3; i++) {
		nextToken();
		vecC[i] = parseFloat();
	}
	Triangle* newTriangle = new Triangle(Point3d(vecA), Point3d(vecB), Point3d(vecC), myCurrentMaterial);
	newTriangle->debugMode = debugMode;
	myGroup.addObject(newTriangle);
}

void Scene::parseTriangleMesh( ) {
	checkToken("TriangleMesh", "TriangleMesh");
	nextToken();
	checkToken("{", "TriangleMesh");
	nextToken();
	checkToken("ply_file", "TriangleMesh");
	nextToken();
	string filename = currentToken;
	nextToken();
	checkToken("}", "TriangleMesh");
	cout << "Triangle Meshs Not Yet Implemented" << endl;
	///TODO: Add code to load triangle mesh
}

void Scene::parseTransform() {
	checkToken("Transform", "Transform");
	nextToken();
	checkToken("{", "Transform");
	float vec[3];
	float mat[4][4];
	float f;

	nextToken();
	if(strcmp(currentToken, "Translate")==0) {
		cout << "Transform not yet implemented" << endl;
		for(int i = 0 ; i < 3; i++) {
			nextToken();
			vec[i] = parseFloat();
		}
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "Scale")==0) {
		cout << "Transform not yet implemented" << endl;
		for (int i = 0; i < 3; i++) {
			nextToken();
			vec[i] = parseFloat();
		}
				
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "XRotate")==0) {
		cout << "Transform not yet implemented" << endl;
		nextToken();
		f = parseFloat();
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "YRotate")==0) {
		cout << "Transform not yet implemented" << endl;
		nextToken();
		f = parseFloat();
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "ZRotate")==0) {
		cout << "Transform not yet implemented" << endl;
		nextToken();
		f = parseFloat();
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "Rotate")==0) {
		cout << "Transform not yet implemented" << endl;
		for (int i = 0; i < 3; i++) {
			nextToken();
			vec[i] = parseFloat();
		}
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "Matrix")==0) {
		cout << "Transform not yet implemented" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j  = 0; j < 4; j++) {
				nextToken();
				mat[i][j] = parseFloat();
			}
		}
		nextToken();
		if (strcmp(currentToken, "Group")==0) {
			cout << "Transform not yet implemented" << endl;
			parseGroup();
		} else if (strcmp(currentToken, "Triangle")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangle();
		} else if (strcmp(currentToken, "Sphere")==0) {
			cout << "Transform not yet implemented" << endl;
			parseSphere();
		} else if (strcmp(currentToken, "Plane")==0) {
			cout << "Transform not yet implemented" << endl;
			parsePlane();
		} else if (strcmp(currentToken, "TriangleMesh")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTriangleMesh();
		} else if (strcmp(currentToken, "Transform")==0) {
			cout << "Transform not yet implemented" << endl;
			parseTransform();
		}
	} else if (strcmp(currentToken, "Group")==0) {
		cout << "Transform not yet implemented" << endl;
		parseGroup();
	} else if (strcmp(currentToken, "Triangle")==0) {
		cout << "Transform not yet implemented" << endl;
		parseTriangle();
	} else if (strcmp(currentToken, "Sphere")==0) {
		cout << "Transform not yet implemented" << endl;
		parseSphere();
	} else if (strcmp(currentToken, "Plane")==0) {
		cout << "Transform not yet implemented" << endl;
		parsePlane();
	} else if (strcmp(currentToken, "TriangleMesh")==0) {
		cout << "Transform not yet implemented" << endl;
		parseTriangleMesh();
	} else if (strcmp(currentToken, "Transform")==0) {
		cout << "Transform not yet implemented" << endl;
		parseTransform();
	}

	nextToken();
	checkToken("}", "Transform");
}

void Scene::parseSimplePerspectiveCamera() {
	float vec[3];
	checkToken("SimplePerspectiveCamera", "SimplePerspectiveCamera");
	myCamera.setMode(simple);
	nextToken();
	checkToken("{", "SimplePerspectiveCamera");
	nextToken();
	checkToken("center", "SimplePerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setPosition(Point3d(vec));
	nextToken();
	checkToken("direction", "SimplePerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setDirection(Vector3d(vec));
	nextToken();
	checkToken("up", "SimplePerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setUpVector(Vector3d(vec));
	nextToken();
	checkToken("distance", "SimplePerspectiveCamera");
	nextToken();
	myCamera.setDistance(parseFloat());
	nextToken();
	checkToken("}", "SimplePerspectiveCamera");
}

void Scene::parsePerspectiveCamera() {
	float vec[3];
	checkToken("PerspectiveCamera", "PerspectiveCamera");
	myCamera.setMode(perspective);
	nextToken();
	checkToken("{", "PerspectiveCamera");
	nextToken();
	checkToken("center", "PerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setPosition(Point3d(vec));
	nextToken();
	checkToken("direction", "PerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setDirection(Vector3d(vec));
	nextToken();
	checkToken("up", "PerspectiveCamera");
	for (int i = 0; i < 3; i++) {
		nextToken();
		vec[i] = parseFloat();
	}
	myCamera.setUpVector(Vector3d(vec));
	nextToken();
	checkToken("angle", "PerspectiveCamera");
	nextToken();
	myCamera.setAngle(parseFloat());
	nextToken();
	checkToken("}", "PerspectiveCamera");
}

void Scene::parseLights() {
	nextToken();
	checkToken("Lights", "Lights");
	nextToken();
	checkToken("{", "Lights");
	nextToken();
	checkToken("numLights", "Lights");
	nextToken();
	int numLights = parseInt();
	for (int i = 0; i < numLights; i++) {
		nextToken();
		checkToken("light", "Lights");
		nextToken();
		if (strcmp(currentToken, "DirectionalLight")==0) {
			parseDirectionalLight();
		} else if (strcmp(currentToken, "PointLight")==0) {
			parsePointLight();
		} else {
			checkToken( "DirectionalLight | PointLight", "Lights");
		}
	}
	nextToken();
	checkToken("}", "Lights");
}

void Scene::parsePointLight() {
	float pos[3];
	float col[3];
	float att[3];
	nextToken();
	checkToken("{", "PointLight");

	nextToken();
	checkToken("position", "PointLight");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		pos[i] = parseFloat( );
	}

	nextToken();
	checkToken("color", "PointLight");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		col[i] = parseFloat( );
	}

	nextToken();
	if 	(strcmp(currentToken, "attenuation")==0) {
		for( int i = 0; i < 3; i++ ){
			nextToken( );
			att[i] = parseFloat( );
		}
		nextToken();
	}
	else {
		att[0] = 1;
		att[1] = 0;
		att[2] = 0;
	}

	checkToken("}", "PointLight");
	myGroup.addLight(Light(Point3d(pos), Color(col), Vector3d(att)));
}

void Scene::parseDirectionalLight() {
	float pos[3];
	float col[3];
	float att[3];
	float dir[3];
	float angle;
	nextToken();
	checkToken("{", "directionalLight");

	nextToken();
	checkToken("position", "directionalLight");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		pos[i] = parseFloat( );
	}

	nextToken();
	checkToken("direction", "directionalLight");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		dir[i] = parseFloat( );
	}

	nextToken();
	checkToken("color", "directionalLight");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		col[i] = parseFloat( );
	}

	nextToken();
	if (strcmp(currentToken, "angle")) {
		nextToken();
		angle = parseFloat();
		nextToken();
	}

	if 	(strcmp(currentToken, "attenuation")==0) {
		for( int i = 0; i < 3; i++ ){
			nextToken( );
			att[i] = parseFloat( );
		}
		nextToken();
	}

	nextToken();
	checkToken("}", "directionalLight");

	myGroup.addLight(Light(Point3d(pos), Vector3d(dir), Color(col), angle, Vector3d(att)));
}

bool Scene::parse( ){	
	bool ret = true;
	lineNumber = 0;
	tokenCount = 0;
	
	inputFileStream.open( myInputSceneFile.c_str( ), ios::in );
	if( inputFileStream.fail( ) ){
		cerr << "Error opening \"" << myInputSceneFile << "\" for reading." << endl;
		exit( 1 );
	}
	parseCamera( );
	parseViewPlane( );
	parseLights( );
	parseBackground( );
	parseMaterials( );
	parseGroup( );

	inputFileStream.close( );
	
	return( ret );
}

bool Scene::areMoreTokens( ){
	bool ret = false;
	if( j < length ){
		ret = true;
	}
	return( ret );
}

void Scene::advance( ){
	if( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
		while( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
			j++;
		}
		i = j;
	}
}

void Scene::nextOnLine( ){
	//advance( );
	while( currentLine[j] != ' ' && currentLine[j] != '\t' && currentLine[j] != '\n' && currentLine[j] != 0 ){
		j++;
	}
	//cout << "ending: " << i <<  ", " << j << endl;
	currentLine[j] = 0;
	int tmp = i;
	if( i != j ){
		while( i <= j ){
			currentToken[i - tmp] = currentLine[i];
			//cout << "copying: " << (i - tmp) <<  ", " << i << endl;
			i++;
		}
		//cerr << lineNumber << ": " << ++tokenCount << ": '" << currentToken << "'" << endl;
	}
	j++;
	i = j;
}

void Scene::nextToken( ){
	if( !inputFileStream.eof( ) ){
		advance( );
		if( areMoreTokens( ) ){
			nextOnLine( );
		}else{
			do{
				inputFileStream.getline( currentLine, sizeof(currentLine) );
				lineNumber++;
				length = strlen( currentLine );
				//cerr << "new line of length: " << length << endl;
			}while( length <= 0 );
			i = 0;
			j = 0;
			advance( );
			//cerr << "Line: " << currentLine << endl;
			if( areMoreTokens( ) ){
				nextOnLine( );
			}
		}
	}
}

void Scene::write( std::ostream &out ) const {
	out << "Input scene file: " << myInputSceneFile << endl;
	out << "Output file: " << myOutputFile << endl;
	out << "Depth file: " << myDepthFile << endl;
	out << myCamera << endl;
	out << "Background Color: " << myBackgroundColor << endl;
	//TODO: LIGHTS
	out << "Number of Materials: " << myNumberOfMaterials << endl;
	for (int i = 0; i < myNumberOfMaterials; i++)
	{
		out << materials[i] << endl;
	}
	out << myGroup << endl;
}

std::ostream& operator <<( std::ostream &out, const Scene &s ){
	s.write( out );
	return( out );
}
