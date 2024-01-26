#include "nbclib.h"



void sortByColorName(color_t *colors, int numColors, color_t **JAUNES, color_t **BLEUS, color_t **ROUGES,
                     color_t **VERTS, color_t **BLANCS, color_t **ORANGES) {
    *JAUNES = (color_t *)malloc(MAX_COLORS * sizeof(color_t));
    *BLEUS = (color_t *)malloc(MAX_COLORS * sizeof(color_t));
    *ROUGES = (color_t *)malloc(MAX_COLORS * sizeof(color_t));
    *VERTS = (color_t *)malloc(MAX_COLORS * sizeof(color_t));
    *BLANCS = (color_t *)malloc(MAX_COLORS * sizeof(color_t));
    *ORANGES = (color_t *)malloc(MAX_COLORS * sizeof(color_t));

    int jauneCount = 0, bleuCount = 0, rougeCount = 0, vertCount = 0, blancCount = 0, orangeCount = 0;

    for (int i = 0; i < numColors; i++) {
        if (strcmp(colors[i].color_name, "JAUNE") == 0) {
            (*JAUNES)[jauneCount++] = colors[i];
        } else if (strcmp(colors[i].color_name, "BLEU") == 0) {
            (*BLEUS)[bleuCount++] = colors[i];
        } else if (strcmp(colors[i].color_name, "ROUGE") == 0) {
            (*ROUGES)[rougeCount++] = colors[i];
        } else if (strcmp(colors[i].color_name, "VERT") == 0) {
            (*VERTS)[vertCount++] = colors[i];
        } else if (strcmp(colors[i].color_name, "BLANC") == 0) {
            (*BLANCS)[blancCount++] = colors[i];
        } else if (strcmp(colors[i].color_name, "ORANGE") == 0) {
            (*ORANGES)[orangeCount++] = colors[i];
        }
    }
}

void esperence_color(color_t *colors, int numColors, double *esperence_r, double *esperence_g, double *esperence_b) {
    *esperence_r = 0;
    *esperence_g = 0;
    *esperence_b = 0;

    for (int i = 0; i < numColors; i++) {
        *esperence_r += colors[i].r;
        *esperence_g += colors[i].g;
        *esperence_b += colors[i].b;
    }

    *esperence_r /= numColors;
    *esperence_g /= numColors;
    *esperence_b /= numColors;
}

void variance_color(color_t *colors, int numColors, double *variance_r, double *variance_g, double *variance_b) {
    double esperence_r, esperence_g, esperence_b;
    esperence_color(colors, numColors, &esperence_r, &esperence_g, &esperence_b);

    *variance_r = 0;
    *variance_g = 0;
    *variance_b = 0;

    for (int i = 0; i < numColors; i++) {
        *variance_r += (colors[i].r - esperence_r) * (colors[i].r - esperence_r);
        *variance_g += (colors[i].g - esperence_g) * (colors[i].g - esperence_g);
        *variance_b += (colors[i].b - esperence_b) * (colors[i].b - esperence_b);
    }

    *variance_r /= numColors;
    *variance_g /= numColors;
    *variance_b /= numColors;
}

int calculateLength(color_t *colors, int numColors, const char *colorName) {
    int count = 0;
    for (int i = 0; i < numColors; ++i) {
        if (strcmp(colors[i].color_name, colorName) == 0) {
            count++;
        }
    }
    return count;
}

colorStat_t* calculateColorStats(color_t *colors, int numColors) {
    color_t *JAUNES, *BLEUS, *ROUGES, *VERTS, *BLANCS, *ORANGES;
    int lenJAUNES, lenBLEUS, lenROUGES, lenVERTS, lenBLANCS, lenORANGES, lenTOTAL;

    sortByColorName(colors, numColors, &JAUNES, &BLEUS, &ROUGES, &VERTS, &BLANCS, &ORANGES);

    lenJAUNES = calculateLength(colors, numColors, "JAUNE");
    lenBLEUS = calculateLength(colors, numColors, "BLEU");
    lenROUGES = calculateLength(colors, numColors, "ROUGE");
    lenVERTS = calculateLength(colors, numColors, "VERT");
    lenBLANCS = calculateLength(colors, numColors, "BLANC");
    lenORANGES = calculateLength(colors, numColors, "ORANGE");
    lenTOTAL = lenJAUNES + lenBLEUS + lenROUGES + lenVERTS + lenBLANCS + lenORANGES;

    colorStat_t *colorStats = (colorStat_t *)malloc(18 * sizeof(colorStat_t));

    double esperence_r, esperence_g, esperence_b;
    double variance_r, variance_g, variance_b;

    esperence_color(JAUNES, lenJAUNES, &esperence_r, &esperence_g, &esperence_b);
    variance_color(JAUNES, lenJAUNES, &variance_r, &variance_g, &variance_b);
    colorStats[0] = (colorStat_t){"JAUNE", 'r', esperence_r, variance_r, lenJAUNES / (double)lenTOTAL};
    colorStats[1] = (colorStat_t){"JAUNE", 'g', esperence_g, variance_g, lenJAUNES / (double)lenTOTAL};
    colorStats[2] = (colorStat_t){"JAUNE", 'b', esperence_b, variance_b, lenJAUNES / (double)lenTOTAL};

    esperence_color(BLEUS, lenBLEUS, &esperence_r, &esperence_g, &esperence_b);
    variance_color(BLEUS, lenBLEUS, &variance_r, &variance_g, &variance_b);
    colorStats[3] = (colorStat_t){"BLEU", 'r', esperence_r, variance_r, lenBLEUS / (double)lenTOTAL};
    colorStats[4] = (colorStat_t){"BLEU", 'g', esperence_g, variance_g, lenBLEUS / (double)lenTOTAL};
    colorStats[5] = (colorStat_t){"BLEU", 'b', esperence_b, variance_b, lenBLEUS / (double)lenTOTAL};

    esperence_color(ROUGES, lenROUGES, &esperence_r, &esperence_g, &esperence_b);
    variance_color(ROUGES, lenROUGES, &variance_r, &variance_g, &variance_b);
    colorStats[6] = (colorStat_t){"ROUGE", 'r', esperence_r, variance_r, lenROUGES / (double)lenTOTAL};
    colorStats[7] = (colorStat_t){"ROUGE", 'g', esperence_g, variance_g, lenROUGES / (double)lenTOTAL};
    colorStats[8] = (colorStat_t){"ROUGE", 'b', esperence_b, variance_b, lenROUGES / (double)lenTOTAL};

    esperence_color(VERTS, lenVERTS, &esperence_r, &esperence_g, &esperence_b);
    variance_color(VERTS, lenVERTS, &variance_r, &variance_g, &variance_b);
    colorStats[9] = (colorStat_t){"VERT", 'r', esperence_r, variance_r, lenVERTS / (double)lenTOTAL};
    colorStats[10] = (colorStat_t){"VERT", 'g', esperence_g, variance_g, lenVERTS / (double)lenTOTAL};
    colorStats[11] = (colorStat_t){"VERT", 'b', esperence_b, variance_b, lenVERTS / (double)lenTOTAL};

    esperence_color(BLANCS, lenBLANCS, &esperence_r, &esperence_g, &esperence_b);
    variance_color(BLANCS, lenBLANCS, &variance_r, &variance_g, &variance_b);
    colorStats[12] = (colorStat_t){"BLANC", 'r', esperence_r, variance_r, lenBLANCS / (double)lenTOTAL};
    colorStats[13] = (colorStat_t){"BLANC", 'g', esperence_g, variance_g, lenBLANCS / (double)lenTOTAL};
    colorStats[14] = (colorStat_t){"BLANC", 'b', esperence_b, variance_b, lenBLANCS / (double)lenTOTAL};

    esperence_color(ORANGES, lenORANGES, &esperence_r, &esperence_g, &esperence_b);
    variance_color(ORANGES, lenORANGES, &variance_r, &variance_g, &variance_b);
    colorStats[15] = (colorStat_t){"ORANGE", 'r', esperence_r, variance_r, lenORANGES / (double)lenTOTAL};
    colorStats[16] = (colorStat_t){"ORANGE", 'g', esperence_g, variance_g, lenORANGES / (double)lenTOTAL};
    colorStats[17] = (colorStat_t){"ORANGE", 'b', esperence_b, variance_b, lenORANGES / (double)lenTOTAL};

    free(JAUNES);
    free(BLEUS);
    free(ROUGES);
    free(VERTS);
    free(BLANCS);
    free(ORANGES);

    return colorStats;
}

double gaussianDistribution(double x, double esperence, double variance) {
    return 1 / (sqrt(2 * M_PI * variance)) * exp(-pow((x - esperence), 2) / (2 * variance));
}

void NBC(color_t x, colorStat_t *colorStats, double *P_JAUNE, double *P_BLEU, double *P_ROUGE,
         double *P_VERT, double *P_BLANC, double *P_ORANGE) {

    double P_JAUNE_r = gaussianDistribution(x.r, colorStats[0].esperence, colorStats[0].variance);
    double P_JAUNE_g = gaussianDistribution(x.g, colorStats[1].esperence, colorStats[1].variance);
    double P_JAUNE_b = gaussianDistribution(x.b, colorStats[2].esperence, colorStats[2].variance);
    *P_JAUNE = P_JAUNE_r * P_JAUNE_g * P_JAUNE_b * colorStats[0].Pcolor;

    double P_BLEU_r = gaussianDistribution(x.r, colorStats[3].esperence, colorStats[3].variance);
    double P_BLEU_g = gaussianDistribution(x.g, colorStats[4].esperence, colorStats[4].variance);
    double P_BLEU_b = gaussianDistribution(x.b, colorStats[5].esperence, colorStats[5].variance);
    *P_BLEU = P_BLEU_r * P_BLEU_g * P_BLEU_b * colorStats[3].Pcolor;

    double P_ROUGE_r = gaussianDistribution(x.r, colorStats[6].esperence, colorStats[6].variance);
    double P_ROUGE_g = gaussianDistribution(x.g, colorStats[7].esperence, colorStats[7].variance);
    double P_ROUGE_b = gaussianDistribution(x.b, colorStats[8].esperence, colorStats[8].variance);
    *P_ROUGE = P_ROUGE_r * P_ROUGE_g * P_ROUGE_b * colorStats[6].Pcolor;

    double P_VERT_r = gaussianDistribution(x.r, colorStats[9].esperence, colorStats[9].variance);
    double P_VERT_g = gaussianDistribution(x.g, colorStats[10].esperence, colorStats[10].variance);
    double P_VERT_b = gaussianDistribution(x.b, colorStats[11].esperence, colorStats[11].variance);
    *P_VERT = P_VERT_r * P_VERT_g * P_VERT_b * colorStats[9].Pcolor;

    double P_BLANC_r = gaussianDistribution(x.r, colorStats[12].esperence, colorStats[12].variance);
    double P_BLANC_g = gaussianDistribution(x.g, colorStats[13].esperence, colorStats[13].variance);
    double P_BLANC_b = gaussianDistribution(x.b, colorStats[14].esperence, colorStats[14].variance);
    *P_BLANC = P_BLANC_r * P_BLANC_g * P_BLANC_b * colorStats[12].Pcolor;

    double P_ORANGE_r = gaussianDistribution(x.r, colorStats[15].esperence, colorStats[15].variance);
    double P_ORANGE_g = gaussianDistribution(x.g, colorStats[16].esperence, colorStats[16].variance);
    double P_ORANGE_b = gaussianDistribution(x.b, colorStats[17].esperence, colorStats[17].variance);
    *P_ORANGE = P_ORANGE_r * P_ORANGE_g * P_ORANGE_b * colorStats[15].Pcolor;

    double evidence = *P_JAUNE + *P_BLEU + *P_ROUGE + *P_VERT + *P_BLANC + *P_ORANGE;
    *P_JAUNE = *P_JAUNE / evidence;
    *P_BLEU = *P_BLEU / evidence;
    *P_ROUGE = *P_ROUGE / evidence;
    *P_VERT = *P_VERT / evidence;
    *P_BLANC = *P_BLANC / evidence;
    *P_ORANGE = *P_ORANGE / evidence;
}


color_t* openCSV(const char *filename, int *numColors) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int bufferSize = 256;  // Adjust the buffer size accordingly
    char buffer[bufferSize];

    // Count the number of lines in the file
    *numColors = 0;
    while (fgets(buffer, bufferSize, f) != NULL) {
        (*numColors)++;
    }

    // Rewind the file to the beginning
    rewind(f);

    // Allocate memory for colors
    color_t *colors = (color_t *)malloc(*numColors * sizeof(color_t));
    if (colors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Read colors from the file
    int index = 0;
    while (fgets(buffer, bufferSize, f) != NULL) {
        char *token = strtok(buffer, ",");
        colors[index].r = atoi(token);

        token = strtok(NULL, ",");
        colors[index].g = atoi(token);

        token = strtok(NULL, ",");
        colors[index].b = atoi(token);

        token = strtok(NULL, ",");
        strcpy(colors[index].color_name, token);
        colors[index].color_name[strcspn(colors[index].color_name, "\n")] = 0;  // Remove newline character

        index++;
    }

    fclose(f);
    return colors;
}

void test(color_t *colors, int numColors, colorStat_t *colorStats) {
    int error = 0;

    for (int i = 0; i < numColors; ++i) {
        double P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE;
        char predictedColor[10];

        NBC(colors[i], colorStats, &P_JAUNE, &P_BLEU, &P_ROUGE, &P_VERT, &P_BLANC, &P_ORANGE);

        printf("Test pour couleur %s (%d, %d, %d):\n", colors[i].color_name, colors[i].r, colors[i].g, colors[i].b);
        printf("Probabilités :\n");
        printf("JAUNE : %.6lf\n", P_JAUNE);
        printf("BLEU : %.6lf\n", P_BLEU);
        printf("ROUGE : %.6lf\n", P_ROUGE);
        printf("VERT : %.6lf\n", P_VERT);
        printf("BLANC : %.6lf\n", P_BLANC);
        printf("ORANGE : %.6lf\n", P_ORANGE);

        // Trouver la couleur prédite
        if (P_JAUNE > P_BLEU && P_JAUNE > P_ROUGE && P_JAUNE > P_VERT && P_JAUNE > P_BLANC && P_JAUNE > P_ORANGE) {
            strcpy(predictedColor, "JAUNE");
        } else if (P_BLEU > P_JAUNE && P_BLEU > P_ROUGE && P_BLEU > P_VERT && P_BLEU > P_BLANC && P_BLEU > P_ORANGE) {
            strcpy(predictedColor, "BLEU");
        } else if (P_ROUGE > P_JAUNE && P_ROUGE > P_BLEU && P_ROUGE > P_VERT && P_ROUGE > P_BLANC && P_ROUGE > P_ORANGE) {
            strcpy(predictedColor, "ROUGE");
        } else if (P_VERT > P_JAUNE && P_VERT > P_BLEU && P_VERT > P_ROUGE && P_VERT > P_BLANC && P_VERT > P_ORANGE) {
            strcpy(predictedColor, "VERT");
        } else if (P_BLANC > P_JAUNE && P_BLANC > P_BLEU && P_BLANC > P_ROUGE && P_BLANC > P_VERT && P_BLANC > P_ORANGE) {
            strcpy(predictedColor, "BLANC");
        } else if (P_ORANGE > P_JAUNE && P_ORANGE > P_BLEU && P_ORANGE > P_ROUGE && P_ORANGE > P_VERT && P_ORANGE > P_BLANC) {
            strcpy(predictedColor, "ORANGE");
        }

        if (strcmp(predictedColor, colors[i].color_name) != 0) {
            error += 1;
            printf("Erreur : couleur prédite = %s, couleur réelle = %s\n", predictedColor, colors[i].color_name);
        }

        printf("\n");
    }

    printf("Nombre d'erreurs : %d\n", error);
}

int main() {
    int numBaseColors, numSampleColors;
    int numSample = 4848;
    color_t *base = openCSV("OK-TOUT3.csv", &numBaseColors);
    colorStat_t *colorStats = calculateColorStats(base, numBaseColors);

    color_t *sample = openCSV("OK-TOUT3.csv", &numSampleColors);

    test(sample, numSample, colorStats);


    // Libérer la mémoire allouée
    free(base);
    free(colorStats);
    free(sample);

    return 0;
}
