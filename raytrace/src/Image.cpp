/* Gregory Parsons
* gnparsons@gmail.com
* CS 566
* September 2013
*
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
 * $Id: Image.cpp 4419 2013-09-12 04:16:46Z mshafae $
 *
 *
 *
 * The image class defines a trivial encoding for images known as PPM
 * format; it simply consists of an array or RGB triples, with one byte
 * per component, preceeded by a simple header giving the size of the
 * image.
 */

#include "Image.h"


std::ostream& operator <<( std::ostream &out, const Pixel &p ){
  p.write( out );
  return( out );
}

Pixel& Image::operator()( int i, int j ) { return *( pixels + ( i * width + j ) ); }  

Image::Image( int x_res, int y_res ){
  width  = x_res;
  height = y_res;
  pixels = new Pixel[ width * height ];
  Pixel *p = pixels;
  for( int i = 0; i < width * height; i++ ) *p++ = Pixel(0,0,0);
}

unsigned char* Image::read( const char *file_name ){
  char buffer[100];
  FILE *fp;
  int size_x, size_y, maxval;
  unsigned char c;
  int i;

  // open file
#ifndef _MSC_VER
  if ((fp=fopen (file_name, "rb"))==NULL){
#else
  errno_t err;
  if ((err=fopen_s (&fp, file_name, "rb")) != 0){
#endif
      fprintf (stderr, "unable to open file%c\n", 7);
    exit (1);
  }

  // read file identifier (magic number)
  fgets (buffer, sizeof (buffer), fp);
  if ((buffer[0] != 'P') || (buffer[1] != '6')){
    fprintf (stderr, "incorrect file type%c\n", 7);
    exit (1);
  }

  // read image size
  do
    fgets (buffer, sizeof (buffer), fp);
  while (buffer[0] == '#' || buffer[0] == ' ');

#ifndef _MSC_VER
  sscanf (buffer, "%d %d", &size_x, &size_y);
#else
  sscanf_s(buffer, "%d %d", &size_x, &size_y);
#endif

  printf( "Image width: %d, Image height: %d\n", size_x, size_y );

  // read maximum pixel value (usually 255)
  do{
    fgets (buffer, sizeof (buffer), fp);
  }while (buffer[0] == '#');

#ifndef _MSC_VER
  sscanf (buffer, "%d", &maxval);
#else
  sscanf_s (buffer, "%d", &maxval);
#endif

  // allocate RGBA texture buffer
  unsigned char *texture = (unsigned char *)malloc(size_x*size_y*4*sizeof(unsigned char));

  // read RGB data and calculate alpha value
  for (i=0; i < size_x*size_y*4; i++){
    // insert alpha value (0 or 255) after each RGB
    if ((i%4) == 3){
      // alpha channel example: make all nearly black pixels transparent
      texture[i]=(unsigned char)
        (((texture[i-3]+texture[i-2]+texture[i-1])<10)?0:255);
    }else{
      c=fgetc(fp);
      texture[i]=(unsigned char) c;
    }
  }

  // close input file
  fclose(fp);
  return(texture);
}

bool Image::write( const char *file_name ){
	std::cout << "In Write Routine A" << std::endl;
  Pixel *p = pixels;
  std::cout << "In Write Routine B" << std::endl;
#ifndef _MSC_VER
  std::cout << "In Write Routine C1" << std::endl;
  FILE  *fp = fopen( file_name, "w+b" );
#else
  std::cout << "In Write Routine C2" << std::endl;
  FILE *fp;
  errno_t err;
  err = fopen_s(&fp, file_name, "w+b");
#endif
  std::cout << "In Write Routine D" << std::endl;
  if( fp == NULL ){
    return false;
  }
  std::cout << "In Write Routine E" << std::endl;
  fprintf( fp, "P6\n%d %d\n255\n", width, height );
  std::cout << "In Write Routine F" << std::endl;
  for( int i = 0; i < width * height; i++ ){
    fprintf( fp, "%c%c%c", p->r, p->g, p->b );
    p++;
  }
  std::cout << "In Write Routine G" << std::endl;
  fclose( fp );
  std::cout << "In Write Routine H" << std::endl;
  return true;
}
