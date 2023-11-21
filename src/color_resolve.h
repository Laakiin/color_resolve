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
	unsigned char r;
	unsigned char g;
	unsigned char b;
}pixel_t;

typedef struct{
	int height;
	int width;
	int channels;
	pixel_t** array;
}image_t;

//get height width and number of channels of an image, store it in img
int getImage(image_t* img,char* image_dir);
//get image pixels, stored in pixel_t 2D array
int getImageData(image_t* img, unsigned char* data);

#endif /* COLOR_RESOLVE_H_ */
