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
pixelhsl_t rgb2hsl(float r, float g, float b){

	pixelhsl_t result;

	r /= 255;
	g /= 255;
	b /= 255;

	float h,s,l;

	float max = MAX(MAX(r,g),b);
	float min = MIN(MIN(r,g),b);

	h = s = l = (max + min) / 2;

	if (max == min) {
		h = s = 0;
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

int getImageData(image_t* img, unsigned char* data){ // A fix, ne fonctionne qu'avec des images carré
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
	//printf("width= %d, height= %d, comp=%d (channels)\n",img->width,img->height,img->channels);
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



bounding_box_t initBoundingBox(int top, int bottom, int left, int right){
    bounding_box_t box;
    box.top = top;
    box.bottom = bottom;
    box.left = left;
    box.right = right;
    return box;
}

bounding_box_t findBoundingBox(image_t *mask, int regionLabel, int **visited){
    int top = mask->height - 1;
    int bottom = 0;
    int left = mask->width - 1;
    int right = 0;

    for (int i = 0; i < mask->height; ++i){
        for (int j = 0; j < mask->width; ++j){
            if (visited[i][j] == regionLabel){
                if (i < top) top = i;
                if (i > bottom) bottom = i;
                if (j < left) left = j;
                if (j > right) right = j;
            }
        }
    }
    return initBoundingBox(top, bottom, left, right);
}

pixelrgb_t calculateAverageColor(image_t *img, bounding_box_t box){
    unsigned int totalR = 0, totalG = 0, totalB = 0;
    int pixelCount = 0;

    for (int i = box.top; i <= box.bottom; ++i){
        for (int j = box.left; j <= box.right; ++j){
            totalR += img->array[i][j].r;
            totalG += img->array[i][j].g;
            totalB += img->array[i][j].b;
            pixelCount++;
        }
    }

    pixelrgb_t averageColor;
    averageColor.r = (unsigned char)(totalR / pixelCount);
    averageColor.g = (unsigned char)(totalG / pixelCount);
    averageColor.b = (unsigned char)(totalB / pixelCount);

    return averageColor;
}

void processRegions(image_t* img, image_t* mask, pixelrgb_t* output){
	int **visited = (int **)malloc(mask->height * sizeof(int *));
    for (int i = 0; i < mask->height; ++i){
        visited[i] = (int *)malloc(mask->width * sizeof(int));
        for (int j = 0; j < mask->width; ++j){
            visited[i][j] = 0;
        }
    }

    int regionLabel = 1;

    for (int i = 0; i < mask->height; ++i){
        for (int j = 0; j < mask->width; ++j){
            if (!visited[i][j] && mask->array[i][j].r == 0 && mask->array[i][j].g == 0 && mask->array[i][j].b == 0) {
                int pixelCount = 0;
                DFS(img, mask, i, j, regionLabel, visited, &pixelCount);
                regionLabel++;
            }
        }
    }

    for (int label = 1; label < regionLabel; ++label){
        bounding_box_t box = findBoundingBox(mask, label, visited);
        pixelrgb_t averageColor = calculateAverageColor(img, box);

        output[label-1].r=averageColor.r;
        output[label-1].g=averageColor.g;
        output[label-1].b=averageColor.b;
    }

    for (int i = 0; i < mask->height; ++i){
        free(visited[i]);
    }
    free(visited);
}

void DFS(image_t *img, image_t *mask, int i, int j, int regionLabel, int **visited, int *pixelCount){
    if (i < 0 || i >= mask->height || j < 0 || j >= mask->width || visited[i][j] || (mask->array[i][j].r != 0 && mask->array[i][j].g != 0 && mask->array[i][j].b != 0)){
        // Hors de la limite, déjà visité ou pas un pixel noir dans le masque
        return;
    }

    visited[i][j] = regionLabel;
    (*pixelCount)++;

    DFS(img, mask, i + 1, j, regionLabel, visited, pixelCount);
    DFS(img, mask, i - 1, j, regionLabel, visited, pixelCount);
    DFS(img, mask, i, j + 1, regionLabel, visited, pixelCount);
    DFS(img, mask, i, j - 1, regionLabel, visited, pixelCount);
}




int main(void){

	image_t img;
	getImage(&img, "out.jpg");

	image_t mask;
	getImage(&mask, "mask.jpg");

	pixelrgb_t meansrgb[21]={0};
	processRegions(&img, &mask, meansrgb);

	pixelhsl_t meanshsl[21]={0};
	for(int i=0; i<21; i++){
		meanshsl[i]=rgb2hsl(meansrgb[i].r,meansrgb[i].g,meansrgb[i].b);
	}

	for(int i=0; i<21; i++){
		printf("%d,%d,%d,%d\n",meansrgb[i].r,meansrgb[i].g,meansrgb[i].b,(i+1));
	}

	return EXIT_SUCCESS;
}
