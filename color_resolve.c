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

const size_t cote = 20;
const size_t NUM_PIXEL_TO_PRINT = 400U;

int getImageData(image_t* img, unsigned char* data){
	img->array=malloc(img->width*sizeof(pixel_t*));
	for(int i=0; i<img->width; i++){
		img->array[i]=malloc(img->height*sizeof(pixel_t));
	}
	int counter=0;
	for(int i=1; i<=(img->height); i++){
		for(int j=1 ; j<(img->width*img->channels); j+=3){
			img->array[i][j].b=data[counter];
			img->array[i][j].g=data[counter+1];
			img->array[i][j].r=data[counter+2];
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


int main(void) {

	image_t test;
	getImageInfos(&test, "red.png");

	/*
	int w,h,c;
	unsigned char* data = stbi_load("red.png",&w,&h,&c,0);
	if(data){
		printf("width= %d, height= %d, comp=%d (channels)\n",w,h,c);
		printf("[");
		for(size_t i=1; i<=NUM_PIXEL_TO_PRINT*c; i++){
			printf("%02x%s,",data[i],((i+1)%c) ? "" : "");

			if(i%(3*cote)==0){
				printf("\n");
			}
			if(i%3==0){
				printf("];[");
			}
		}
		printf("\n");
	}
	*/

	return EXIT_SUCCESS;
}
