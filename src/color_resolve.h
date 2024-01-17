/*
 * color_resolve.h
 *
 *  Created on: Nov 15, 2023
 *      Author: anakin
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

typedef struct {
    int top;
    int bottom;
    int left;
    int right;
} bounding_box_t;


/**
 * Function that converts rgb pixel to hsv pixel
 *
 * It's a modified function found here: https://gist.github.com/ciembor/1494530
 *
 * @param r - r component of color
 * @param g - g component of color
 * @param b - b component of color
 * @return pixel in hsl code
 */
pixelhsl_t rgb2hsl(float r, float g, float b);


/**
 * Get height width and number of channels of an image
 *
 * @param img - variable in which the image will be stored
 * @param image_dir - string with image path
 * @return 0 if ok
 */
int getImage(image_t* img,char* image_dir);

/**
 * Get image pixels and store it
 *
 * @param img - variable in which the image will be stored
 * @param data - unformated pixels of an image
 * @return 0 if ok
 */
int getImageData(image_t* img, unsigned char* data);

/**
 * Print image
 *
 * @param img - Printed image
 * @param mode - mode in which it will be printed: 1- RGB values, 2- '#' in the color of the pixel, 3- HSL values
 */
void printImageArray(image_t* src, char mode);

/**
 * Get blobs of the mask and apply it to get
 *
 * @param img - Processed image
 * @param mask - mask applied to the image
 * @param i - i variable to navigate in image
 * @param j - j variable to navigate in image
 * @param regionLabel - number given to the region
 * @param visited - tag to know if a pixel has been visited or not
 */
void DFS(image_t *img, image_t *mask, int i, int j, int regionLabel, int **visited, int *pixelCount);

/**
 * Initialize the bounding box
 *
 * @param top - top corner of the box
 * @param bottom - bottom corner of the box
 * @param left - left corner of the box
 * @param right - right corner of the box
 * @return Initialized boundig box
 */
bounding_box_t initBoundingBox(int top, int bottom, int left, int right);

/**
 * Find the box surrounding a blob
 *
 * @param mask - mask applied to the image
 * @param regionLabel - number given to the region
 * @param visited - tag to know if a pixel has been visited or not
 * @return average color of the blob
 */
bounding_box_t findBoundingBox(image_t *mask, int regionLabel, int **visited);

/**
 * Do the mean color of a blob
 *
 * @param img - Processed image
 * @param box - corners of box surroundig the blob
 * @return average color of the blob
 */
pixelrgb_t calculateAverageColor(image_t *img, bounding_box_t box);

/**
 * Do the mean color of each blob using 'calculateAverageColor' on the studied image and store it
 *
 * @param img - Processed image
 * @param mask - mask applied to the image
 * @param output - Array in which each color mean is stored
 */
void processRegions(image_t* img, image_t* mask, pixelrgb_t* output)





#endif /* COLOR_RESOLVE_H_ */
