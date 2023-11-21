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

const size_t cote = 5;

int getImageData(image_t* img, unsigned char* data){ // REVOIR TAILLE DES TABLEAUX, PROBLEME AVEC CA SUREMENT
	img->array=malloc(img->width*sizeof(pixel_t*));
	for(int i=0; i<img->width; i++){
		img->array[i]=malloc(img->height*sizeof(pixel_t));
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
}


int main(void) {

	image_t test;
	getImage(&test, "palette.png");
	printImageArray(&test,2);

	return EXIT_SUCCESS;
}

