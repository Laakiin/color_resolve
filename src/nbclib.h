/*
 * nbclib.h
 *
 *  Created on: Jan 26, 2024
 *      Author: anakin
 */

#ifndef NBCLIB_H_
#define NBCLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_COLORS 1000

typedef struct {
    int r;
    int g;
    int b;
    char color_name[50];
} color_t;

typedef struct {
    char color_name[50];
    char color_component;
    double esperence;
    double variance;
    double Pcolor;
} colorStat_t;

/**
 * Sort colors in a color_t array by color name
 *
 * @param colors - Colors with r,g,b and colorname
 * @param numColors - number of entries in colors
 * @param JAUNES,BLEUS... - Arrays in which each color is classified by colorname
 */
void sortByColorName(color_t *colors, int numColors, color_t **JAUNES, color_t **BLEUS, color_t **ROUGES,color_t **VERTS, color_t **BLANCS, color_t **ORANGES);

/**
 * Calculate the expectation of each color components in colors
 *
 * @param colors - Colors with r,g,b and colorname
 * @param numColors - number of entries in colors
 * @param esperence_r,g,b - expectations of each component in colors
 */
void esperence_color(color_t *colors, int numColors, double *esperence_r, double *esperence_g, double *esperence_b);

/**
 * Calculate the variance of each color components in colors
 *
 * @param colors - Colors with r,g,b and colorname
 * @param numColors - number of entries in colors
 * @param variance_r,g,b - variances of each component in colors
 */
void variance_color(color_t *colors, int numColors, double *variance_r, double *variance_g, double *variance_b);

/**
 * Calculate number of entries for a given colorname
 *
 * @param colors - Colors with r,g,b and colorname
 * @param numColors - number of entries in colors
 * @param colorName - studied colorname
 * @return Number of entries for the given colorname
 */
int calculateLength(color_t *colors, int numColors, const char *colorName);

/**
 * Calculate expectation of each colorname and color component
 *
 * @param colors - Colors with r,g,b and colorname
 * @param numColors - number of entries in colors
 * @return an array with expectation, variance and number of entries for each colorname and color component
 */
colorStat_t* calculateColorStats(color_t *colors, int numColors);

/**
 * Calculate the gaussian distribution of a given sample
 *
 * @param x - studied sample
 * @param esperence - esperence for this sample
 * @param variance - variance for this sample
 * @return the gaussian distribution of the given sample
 */
double gaussianDistribution(double x, double esperence, double variance);

/**
 * Do a Naive Bayesian Classification for an entry
 *
 * @param x - studied entry
 * @param colorStats - array with expectation, variance and number of entries for each colorname and color component
 * @param P_JAUNE, P_BLEU... - Probabilities that the studied sample is either of these colors
 */
void NBC(color_t x, colorStat_t *colorStats, double *P_JAUNE, double *P_BLEU, double *P_ROUGE,
         double *P_VERT, double *P_BLANC, double *P_ORANGE);

/**
 * Open CSV file with color entries with this format: r,g,b,COLOR and store it in an array
 *
 * @param filename - csv file opened
 * @param numColors - number of entries in colors (output)
 * @return Array of color_t with each entry in the CSV file
 */
color_t* openCSV(const char *filename, int *numColors);

/**
 * Test the NBC and verify if there is errors, and how many there are
 *
 * @param colors - studied set of entries
 * @param numColors - number of entries in colors
 * @param colorStats - array with expectation, variance and number of entries for each colorname and color component
 */
void test(color_t *colors, int numColors, colorStat_t *colorStats);

#endif /* NBCLIB_H_ */
