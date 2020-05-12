
#include "bezier.h"
#include <math.h>


BezierPatchTXT read_Bezier_Patches(const char *file) {
    //fazer a leitura da informação do ficheiro com os bezier patches para estruturas adequadas
    BezierPatchTXT bp;
    FILE *f;
    f = fopen(file, "r");

    //ler o numero de patches
    if(!feof(f)) fscanf(f,"%d\n",&(bp.patches));
    /*
     * indices correpondentes às posições dos vértices para os diferentes patches
     */
    for(int i = 0;i < 16;i++){
        bp.verticesPatches[i] = (int*)malloc(sizeof(int) * bp.patches);
    }
    for(int i = 0; i < bp.patches && !feof(f); i++){
        for(int j = 0; j < 15; j++) fscanf(f, "%d, ", &bp.verticesPatches[j][i]);
        fscanf(f, "%d\n", &bp.verticesPatches[15][i]);
    }
    //Control points
    fscanf(f, "%d\n", &bp.controlPoints);
    for(int i = 0;i < 3;i++){
        bp.controlPointsVertices[i] = (float*)malloc(sizeof(int) * bp.controlPoints);
    }
    for(int c = 0; c < bp.controlPoints && !feof(f); c++){
        fscanf(f, "%f, %f, %f\n", &bp.controlPointsVertices[0][c], &bp.controlPointsVertices[1][c], &bp.controlPointsVertices[2][c]);
    }
    fclose(f);

    return bp;
}

Matrix multiplyMatrices(Matrix fstMatrix, Matrix sndMatrix){
    Matrix mult; mult.lines = fstMatrix.lines; mult.cols = sndMatrix.cols;
    for(int a = 0; a < 4; a++)
        for(int b = 0; b < 4; b++)
            mult.values[a][b] = 0;

    for(int i = 0; i < fstMatrix.lines; ++i){
        for(int j = 0; j < sndMatrix.cols; ++j){
            for(int k = 0; k < fstMatrix.cols; ++k){
                mult.values[i][j] += fstMatrix.values[i][k] * sndMatrix.values[k][j];
            }
        }
    }
    return mult;
}

void bezierPatches(BezierPatchTXT bp, char * fileModel, int tesselation){
    FILE * f = fopen(fileModel,"w");
    // Matriz da bezier Curve
    Matrix bezierCurveMatrix; bezierCurveMatrix.lines = 4; bezierCurveMatrix.cols = 4;
    int bcm[4][4] = { {-1,  3, -3, 1},
                      { 3, -6,  3, 0},
                      {-3,  3,  0, 0},
                      { 1,  0,  0, 0} };

    for(int a = 0; a < 4; a++){
        for(int b = 0; b < 4; b++){
            bezierCurveMatrix.values[a][b] = bcm[a][b];
        }
    }

    //Pontos do bezier patch calculados com a tesselation
    float bezierPatchPoints[tesselation + 1][tesselation + 1][3];

    for(int i = 0;i < bp.patches;i++){
        //matrix com coordenadas X dos pontos do patch i
        Matrix patchPoints_X; patchPoints_X.lines = 4; patchPoints_X.cols = 4;
        Matrix patchPoints_Y; patchPoints_Y.lines = 4; patchPoints_Y.cols = 4;
        Matrix patchPoints_Z; patchPoints_Z.lines = 4; patchPoints_Z.cols = 4;

        //preenche matriz com os pontos do patch
        for(int p = 0; p < 16; p++){
            int v = bp.verticesPatches[15 - p][i];
            int indX = p / 4; int indY = p % 4;
            patchPoints_X.values[indX][indY] = bp.controlPointsVertices[0][v];
            patchPoints_Y.values[indX][indY] = bp.controlPointsVertices[1][v];
            patchPoints_Z.values[indX][indY] = bp.controlPointsVertices[2][v];
        }

        for(int u = 0; u <= tesselation; u++){
            for(int v = 0; v <= tesselation; v++){
                Matrix uVetor; uVetor.cols = 4; uVetor.lines = 1;
                uVetor.values[0][0] = pow(u * 1/(float)tesselation, 3);
                uVetor.values[0][1] = pow(u * 1/(float)tesselation, 2);
                uVetor.values[0][2] = pow(u * 1/(float)tesselation, 1);
                uVetor.values[0][3] = 1;

                Matrix vVetor; vVetor.cols = 1; vVetor.lines = 4;
                vVetor.values[0][0] = pow(v * 1/(float)tesselation, 3);
                vVetor.values[1][0] = pow(v * 1/(float)tesselation, 2);
                vVetor.values[2][0] = pow(v * 1/(float)tesselation, 1);
                vVetor.values[3][0] = 1;

                //calcular ponto final do bezierPatch
                bezierPatchPoints[u][v][0] = multiplyMatrices( multiplyMatrices( multiplyMatrices( multiplyMatrices(uVetor,bezierCurveMatrix), patchPoints_X ), bezierCurveMatrix ), vVetor).values[0][0];
                bezierPatchPoints[u][v][1] = multiplyMatrices( multiplyMatrices( multiplyMatrices( multiplyMatrices(uVetor,bezierCurveMatrix), patchPoints_Y ), bezierCurveMatrix ), vVetor).values[0][0];
                bezierPatchPoints[u][v][2] = multiplyMatrices( multiplyMatrices( multiplyMatrices( multiplyMatrices(uVetor,bezierCurveMatrix), patchPoints_Z ), bezierCurveMatrix ), vVetor).values[0][0];
            }
        }

        //desenhar os triangulos no ficheiro com o model
        int a,b;
        for(int u = 0; u < tesselation; u++){
            for(int v = 0; v < tesselation; v++){
                for(int w = 0; w < 6; w++){
                    switch(w){
                        case 0:
                        case 3:
                            a = u; b = v;
                            break;
                        case 1:
                            a = u + 1; b = v;
                            break;
                        case 2:
                        case 4:
                            a = u + 1; b= v + 1;
                            break;
                        case 5:
                            a = u; b = v + 1;
                            break;
                        default:
                            break;
                    }
                    float x = bezierPatchPoints[a][b][0];
                    float y = bezierPatchPoints[a][b][1];
                    float z = bezierPatchPoints[a][b][2];
                    write_point(f,x,y,z);
                }
            }
        }

    }
    fclose(f);
}
