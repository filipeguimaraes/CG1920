#include "../utils/utils.h"
#ifndef GENERATOR_BEZIER_H
#define GENERATOR_BEZIER_H

struct matrix{
    int lines;
    int cols;
    float values[4][4];
};

struct bezierpatchtxt{
    int patches;
    int controlPoints;
    int* verticesPatches[16];
    float* controlPointsVertices[3];
};


typedef struct bezierpatchtxt BezierPatchTXT;

typedef struct matrix Matrix;

BezierPatchTXT read_Bezier_Patches(const char *file);

void bezierPatches(BezierPatchTXT bp, char * fileModel, int tesselation);


#endif //GENERATOR_BEZIER_H
