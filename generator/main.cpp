#include <iostream>
#include <cstring>
#include <math.h>

#define REGULAR 1
#define INVERT -(REGULAR)

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

void write_point(FILE * f, float x, float y, float z){
    fprintf(f,"%f, %f, %f\n",x,y,z);
}

int isNumber(char * num){
    int i;
    for (i = 0; i < strlen(num) && isdigit(num[i]); ++i);
    return i==strlen(num);
}

int plane(char * file_path, float a){
    FILE * f = fopen(file_path,"w");
    write_point(f,  a/2 , 0.0f,  a/2);
    write_point(f,  a/2 , 0.0f, -a/2);
    write_point(f, -a/2 , 0.0f, -a/2);
    write_point(f,  a/2 , 0.0f,  a/2);
    write_point(f, -a/2 , 0.0f, -a/2);
    write_point(f, -a/2 , 0.0f,  a/2);
    fclose(f);
    return 0;
}

void planeXZ(FILE * f,  float x, float y, float z, float tamx, float tamz, int dir){
    write_point(f, x * dir          , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, x * dir          , y , z );

    write_point(f, x * dir          , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , z );
}

void planeXY(FILE * f,  float x, float y, float z, float tamx, float tamy, int dir){
    write_point(f, x * dir          , y , z );
    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, x * dir          , y + tamy , z );

    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, (x + tamx) * dir , y + tamy , z );
    write_point(f, x * dir          , y + tamy , z );
}

void planeYZ(FILE * f,  float x, float y, float z, float tamy, float tamz, int dir){
    write_point(f, x , y * dir           , z );
    write_point(f, x , (y + tamy) * dir  , z );
    write_point(f, x , y * dir           , z + tamz );

    write_point(f, x , (y + tamy) * dir , z );
    write_point(f, x , (y + tamy) * dir , z + tamz );
    write_point(f, x , y * dir          , z + tamz );
}

int box(char * file_path, float x, float y, float z, int div){
    float a,b,c;
    a = x/div;
    b = y/div;
    c = z/div;
    FILE * f = fopen(file_path,"w");

    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
    //planos paralelos ao XZ
    //plano de cima
            planeXZ(f,-x/2+(a*i),y/2,-z/2+(c*j),a,c,REGULAR);
    //plano de baixo
            planeXZ(f,-x/2+(a*i),-y/2,-z/2+(c*j),a,c,INVERT);

    //planos paralelos ao XY
    //plano da frente
            planeXY(f,-x/2+(a*i),-y/2+(b*j),z/2,a,b,REGULAR);
    //plano de trás
            planeXY(f,-x/2+(a*i),-y/2+(b*j),-z/2,a,b,INVERT);

    //planos paralelos ao YZ
    //plano de direita
            planeYZ(f,x/2,-y/2+(b*j),-z/2+(c*i),b,c,REGULAR);
    //plano da esquerda
            planeYZ(f,-x/2,-y/2+(b*j),-z/2+(c*i),b,c,INVERT);
        }
    }

    fclose(f);
    return 0;
}

void cone(char * file, float h, float r, float slices, float stacks){
    FILE * f = fopen(file,"w");
    float a = 0;
    float h1 = -h / 2;
    float h2;
    float r1 = r;
    float r2 = 0;
    float angulo = (float)(2 * M_PI) / (slices);


    //base
    while (a < 2 * M_PI) {
        write_point(f,0,h1, 0);
        write_point(f,r * cos(a), h1, r * sin(a));
        a += angulo;
        write_point(f,r * cos(a), h1, r * sin(a));
    }
    a=0;

    //h-((r/h)*x)
    for (int i = 0; i < stacks; i++) {
        r2 = r1 - r / stacks;
        h2 = h1 + h / stacks;
        while (a < 2 * M_PI) {
            write_point(f,r1 * cos(a), h1, r1 * sin(a));
            write_point(f,r2 * cos(a), h2, r2 * sin(a));
            write_point(f,r1 * cos(a+ angulo), h1, r1 * sin(a+angulo));

            write_point(f,r2 * cos(a), h2, r2 * sin(a));
            write_point(f,r2 * cos(a+angulo), h2, r2 * sin(a+angulo));
            write_point(f,r1 * cos(a+angulo), h1, r1 * sin(a+angulo));
            a += angulo;
        }
        h1 = h2;
        r1 = r2;
        a = 0;
    }
    fclose(f);
}


//encontrar a posição do vertice em coordenadas cartesianas a partir das coordenadas polares
void findPosition(FILE * f, float raio, int stacks, int slices, float alfa_j,float beta_i){
    float alfa = (float)(2 * M_PI) * ((float)alfa_j / (float)slices);
    float beta = M_PI * ((float)beta_i / (float)(stacks + 1)) - ((float)M_PI/(float)2);
    write_point(f,(float)raio * cos(beta) * sin(alfa),
                (float)raio * sin(beta),
                (float)raio * cos(beta) * cos(alfa));
}


void sphere(char * file, float raio, int slices, int stacks){
    // O numero de argumentos do programa generator difere consoante a primitiva
    // sphere -> 5 argumentos: 1|nome da primitiva; 2|raio; 3|slices; 4|stacks; 5|nome do ficheiro que vai conter os vértices
    // exemplo para criar ficheiro do modelo, com nome sphere.3d, para uma esfera com 0.5 de raio, 8 slices, 9 stacks: ./generator sphere 0.5 8 9 sphere.3d
    FILE * f = fopen(file,"w");
    int alfa_j = 0, beta_i = 0;

    for (int j = 0; j < slices; j++) { // percorrer todas as fatias da esfera
        for (int i = stacks + 1; i > 0; i--) { // desenhar todos os triangulos de uma fatia da esfera
            if (i == (stacks + 1)) {
                // 1 triangulo da stack do topo da fatia
                for (int k = 1; k <= 3; k++) { // Construir cada vértice
                    switch (k) {
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i - 1; break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            } else if (i == 1) {
                // 1 triangulo da stack da base da fatia
                for (int k = 1; k <= 3; k++) { // Construir cada vértice
                    switch (k) {
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i; break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            } else {// 2 triangulos da stack i da fatia que juntos formam um quadrilátero
                for (int k = 1; k <= 6; k++) { // Construir cada vértice
                    switch (k) {
                        //Vertices correspondentes ao Triangulo 1
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i; break;
                            //Vertices correspondentes ao Triangulo 2
                        case 4: alfa_j = j; beta_i = i - 1; break;
                        case 5: alfa_j = j + 1; beta_i = i - 1; break;
                        case 6: alfa_j = j + 1; beta_i = i; break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            }
        }
    }
    fclose(f);
}

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

int main(int argc, char ** argv) {

    if(argc > 3 && !strcmp(argv[1],"plane") && isNumber(argv[2])){
        plane(argv[3],atof(argv[2]));
    }
    else if(argc > 6 && !strcmp(argv[1],"box") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4]) && isNumber(argv[5])){
        box(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atoi(argv[5]));
    }
    else if(argc > 6 && !strcmp(argv[1],"cone") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4]) && isNumber(argv[5])){
        cone(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atof(argv[5]));
    }
    else if(argc > 5 && !strcmp(argv[1],"sphere") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4])){
        sphere(argv[5],atof(argv[2]),atoi(argv[3])
                ,atoi(argv[4]));
    }
    // generator      bezierPatch                  teapot.patch                 10            teapotBezier.3d
    //                    modo       |  ficheiro com os bezierpatches | tesselation level | ficheiro do modelo
    else if(argc == 5 && !strcmp(argv[1],"bezierPatch") && isNumber(argv[3])){
        BezierPatchTXT bp = read_Bezier_Patches(argv[2]);
        bezierPatches(bp,argv[4],atof(argv[3]));
    }
    else puts("Invalid arguments.");

    return 0;
}
