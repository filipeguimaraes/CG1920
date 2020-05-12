//
// Created by wtv on 12/05/20.
//

#include "primitives.h"
#include <math.h>

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
