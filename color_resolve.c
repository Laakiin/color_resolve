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

const size_t NUM_PIXEL_TO_PRINT = 50625U;

int main(void) {

	int w,h,c;
	unsigned char* data = stbi_load("images.png",&w,&h,&c,0);
	if(data){
		printf("width= %d, height= %d, comp=%d (channels)\n",w,h,c);
		for(size_t i=0; i<NUM_PIXEL_TO_PRINT*c; i++){
			printf("%02x%s ",data[i],((i+1)%c) ? "" : "");
			if(i%225==0){
				printf("\n");
			}
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
