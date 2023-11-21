/*
 ============================================================================
 Name        : color_resolve.c
 Author      : anakin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "color_resolve.h"


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
/*
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns HSL in the set [0, 1].
 */
pixelhsl_t rgb2hsl(float r, float g, float b) {

  pixelhsl_t result;

  r /= 255;
  g /= 255;
  b /= 255;

  float h,s,l;

  float max = MAX(MAX(r,g),b);
  float min = MIN(MIN(r,g),b);

  h = s = l = (max + min) / 2;

  if (max == min) {
    h = s = 0; // achromatic
  }
  else {
    float d = max - min;
    s = (l > 0.5) ? d / (2 - max - min) : d / (max + min);

    if (max == r) {
      h = (g - b) / d + (g < b ? 6 : 0);
    }
    else if (max == g) {
      h = (b - r) / d + 2;
    }
    else if (max == b) {
      h = (r - g) / d + 4;
    }

    h /= 6;
  }

  result.h=(unsigned char)255*h;
  result.s=(unsigned char)255*s;
  result.l=(unsigned char)255*l;
  return result;
}

int getImageData(image_t* img, unsigned char* data){ // REVOIR TAILLE DES TABLEAUX, PROBLEME AVEC CA SUREMENT
	img->array=malloc(img->width*sizeof(pixelrgb_t*));
	for(int i=0; i<img->width; i++){
		img->array[i]=malloc(img->height*sizeof(pixelrgb_t));
	}
	int counter=0;
	for(int i=1; i<=(img->height); i++){
		for(int j=1 ; j<=img->width; j++){
			img->array[i-1][j-1].r=data[counter];
			img->array[i-1][j-1].g=data[counter+1];
			img->array[i-1][j-1].b=data[counter+2];
			counter+=3;
		}
	}

	return 0;
}

int getImage(image_t* img,char* image_dir){
	unsigned char* data = stbi_load(image_dir,&(img->width),&(img->height),&(img->channels),0);
	printf("width= %d, height= %d, comp=%d (channels)\n",img->width,img->height,img->channels);
	getImageData(img,data);
	return 0;
}

void printImageArray(image_t* src, char mode){
	if(mode==1){
		for(int i=0; i<src->height; i++){
			for(int j=0; j<src->width; j++){
				printf("[%03d %03d %03d]",src->array[i][j].r,src->array[i][j].g,src->array[i][j].b);
			}
			printf("\n");
		}
	}
	else if(mode==2){
		for(int i=0; i<src->height; i++){
			for(int j=0; j<src->width; j++){
				printf("\e[38;2;%d;%d;%dm#\x1b[0m",src->array[i][j].r,src->array[i][j].g,src->array[i][j].b);
			}
			printf("\n");
		}
	}
	else if(mode==3){
		pixelhsl_t pix;
			for(int i=0; i<src->height; i++){
				for(int j=0; j<src->width; j++){
					pix=rgb2hsl((float)src->array[i][j].r,(float)src->array[i][j].g,(float)src->array[i][j].b);
					printf("[%03d %03d %03d]",pix.h,pix.s,pix.l);
				}
				printf("\n");
			}
		}
}




int main(void) {

	image_t test;
	getImage(&test, "palette.png");
	printImageArray(&test,2);

	return EXIT_SUCCESS;
}

