/* Gregory Parsons
 * gnparsons@gmail.com
 * CS 566
 * September 2013
 * The main process
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
 * $Id: raytrace.cpp 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#include <iostream>
#include <string>
#include "getopt.h"
#include "Scene.h"

Scene *gTheScene;
string gProgramName;
static const double epsilon = 1.0E-4;
static const int MAX_RECURSION_DEPTH = 4;
static const int DEPTH_IMAGE_MAX_SCALE = 20;

void usage( string message = "" ){
	cerr << message << endl;
	cerr << gProgramName << " -i <inputfile> -o <outputfile> -d <depthfile>" << endl;
	cerr << "          -or-" << endl;
	cerr << gProgramName << " --input <inputfile> --output <outputfile> --depth <depthfile>" << endl;
	
}

void parseCommandLine( int argc, char **argv ){
	int ch;
	string inputFile( "" ), outputFile( "" ), depthFile( "" );
	int resolution;
	bool debugMode = false;
	static struct option longopts[] = {
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "depth", required_argument, NULL, 'd' },
    { "resolution", required_argument, NULL, 'r' },
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
	};

	while( (ch = getopt_long(argc, argv, "i:o:d:r:vh", longopts, NULL)) != -1 ){
		switch( ch ){
			case 'i':
				// input file
				inputFile = string(optarg);
				break;
			case 'o':
				// image output file
				outputFile = string(optarg);
				break;
			case 'd':
				// depth output file
				depthFile = string( optarg );
				break;
			case 'r':
        resolution = atoi(optarg);
        break;
      case 'v':
        debugMode = true;
        break;
      case 'h':
        usage( );
        break;
			default:
				// do nothing
				break;
		}
	}
	gTheScene = new Scene( inputFile, outputFile, depthFile );
	gTheScene->debugMode = debugMode;
}

int main( int argc, char **argv ){
	string pathStr;
	gProgramName = argv[0];

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
		gTheScene->parse( );
		cout << *gTheScene << endl;
		Image depth = Image(gTheScene->camera().numPxWidth(), gTheScene->camera().numPxHeight());
		Image output = Image(gTheScene->camera().numPxWidth(), gTheScene->camera().numPxHeight());
		float pxDepth = 0.0;
		Hit h;
		int x=0, y=0;
		while(!(gTheScene->camera().isDone()))
		{
			x=gTheScene->camera().getLastX();
			y=gTheScene->camera().getLastY();
			if (gTheScene->debugMode) {
				cout << "(" << x << ", " << y << ")" << endl;
			}
			h = gTheScene->group().intersect(gTheScene->camera().getNextRay(), 0, MAX_RECURSION_DEPTH);
			if (h.didHit()) {
				pxDepth = 1-(h.getDepth()/DEPTH_IMAGE_MAX_SCALE);
				if (pxDepth < 0) {
					pxDepth = 0.0;
				} else if (pxDepth > 1) {
					pxDepth = 1.0;
				}
				depth(y, x) = Pixel(Color(pxDepth, pxDepth, pxDepth));
				output(y, x) = Pixel(h.getColor());
			} else {
				if (gTheScene->debugMode) {
					cout << "No Hit" << endl;
				}
				depth(y, x) = Pixel(0,0,0);
				output(y, x) = gTheScene->backgroundColor();
			}
		}
		if (gTheScene->debugMode) {
			cout << "Writing Depth File" << endl;
		}
		depth.write(gTheScene->depthFile().c_str());
		if (gTheScene->debugMode) {
			cout << "Writing Output File" << endl;
		}
		output.write(gTheScene->outputFile().c_str());
		if (gTheScene->debugMode) {
			cout << "Wrote Both Files" << endl;
		}
	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}


	return( 0 );
}
