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


float max(float a, float b, float c) {
   return ((a > b)? (a > c ? a : c) : (b > c ? b : c));
}
float min(float a, float b, float c) {
   return ((a < b)? (a < c ? a : c) : (b < c ? b : c));
}
pixelhsv_t rgb_to_hsv(float r, float g, float b) {
	pixelhsv_t pixel;
   // R, G, B values are divided by 255
   // to change the range from 0..255 to 0..1:
   float h, s, v;
   r /= 255.0;
   g /= 255.0;
   b /= 255.0;
   float cmax = max(r, g, b); // maximum of r, g, b
   float cmin = min(r, g, b); // minimum of r, g, b
   float diff = cmax-cmin; // diff of cmax and cmin.
   if (cmax == cmin)
      h = 0;
   else if (cmax == r)
      h = fmod((60 * ((g - b) / diff) + 360), 360.0);
   else if (cmax == g)
      h = fmod((60 * ((b - r) / diff) + 120), 360.0);
   else if (cmax == b)
      h = fmod((60 * ((r - g) / diff) + 240), 360.0);
   // if cmax equal zero
      if (cmax == 0)
         s = 0;
      else
         s = (diff / cmax) * 100;
   // compute v
   v = cmax * 100;
   //printf("h s v=(%f, %f, %f)", h, s, v );
   pixel.h=(char)h;
   pixel.s=(char)s;
   pixel.v=(char)v;
   return pixel;
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
		pixelhsv_t pix;
			for(int i=0; i<src->height; i++){
				for(int j=0; j<src->width; j++){
					pix=rgb_to_hsv((float)src->array[i][j].r,(float)src->array[i][j].g,(float)src->array[i][j].b);
					printf("[%03d %03d %03d]",pix.h,pix.s,pix.v);
				}
				printf("\n");
			}
		}
}




int main(void) {

	image_t test;
	getImage(&test, "5_5_test.png");
	printImageArray(&test,3);

	return EXIT_SUCCESS;
}

