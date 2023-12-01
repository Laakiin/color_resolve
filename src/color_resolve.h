/*
 * color_resolve.h
 *
 *  Created on: Nov 15, 2023
 *      Author: mea
 */

#ifndef COLOR_RESOLVE_H_
#define COLOR_RESOLVE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

typedef struct{
	unsigned char h;
	unsigned char s;
	unsigned char l;
}pixelhsl_t;

typedef struct{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}pixelrgb_t;

typedef struct{
	int height;
	int width;
	int channels;
	pixelrgb_t** array;
}image_t;

//get height width and number of channels of an image, store it in img
int getImage(image_t* img,char* image_dir);
//get image pixels, stored in pixel_t 2D array
int getImageData(image_t* img, unsigned char* data);

//print image data following 3 modes:
//   -Mode 1: print rgb codes of each pixel
//   -Mode 2: print each pixel as a ´#´ colored with the color of the pixel
//   -Mode 3: print hsl codes of each pixel
void printImage(image_t img, char mode);

#endif /* COLOR_RESOLVE_H_ */
