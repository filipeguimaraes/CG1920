#include "sphere.h"
#include "../utils/utils.h"
#include <math.h>

std::vector<float> normal, texture;

void add_point_normal(float x, float y, float z) {
    normal.push_back(x);
    normal.push_back(y);
    normal.push_back(z);
}

void add_point_texture(float f1, float f2) {
    texture.push_back(f1);
    texture.push_back(f2);
}


//encontrar a posição do vertice em coordenadas cartesianas a partir das coordenadas polares
void findPosition(FILE *f, float raio, int stacks, int slices, float alfa_j, float beta_i) {
    float alfa = (float) (2 * M_PI) * ((float) alfa_j / (float) slices);
    float beta = M_PI * ((float) beta_i / (float) (stacks + 1)) - ((float) M_PI / (float) 2);
    write_point(f, (float) raio * cos(beta) * sin(alfa),
                (float) raio * sin(beta),
                (float) raio * cos(beta) * cos(alfa));

    add_point_normal((float) raio * cos(beta) * sin(alfa),
                     (float) raio * sin(beta),
                     (float) raio * cos(beta) * cos(alfa));
}


void sphere(char *file, float raio, int slices, int stacks) {
    // O numero de argumentos do programa generator difere consoante a primitiva
    // sphere -> 5 argumentos: 1|nome da primitiva; 2|raio; 3|slices; 4|stacks; 5|nome do ficheiro que vai conter os vértices
    // exemplo para criar ficheiro do modelo, com nome sphere.3d, para uma esfera com 0.5 de raio, 8 slices, 9 stacks: ./generator sphere 0.5 8 9 sphere.3d
    FILE *f = fopen(file, "w");
    int alfa_j = 0, beta_i = 0;

    for (int j = 0; j < slices; j++) { // percorrer todas as fatias da esfera
        for (int i = stacks + 1; i > 0; i--) { // desenhar todos os triangulos de uma fatia da esfera
            if (i == (stacks + 1)) {
                // 1 triangulo da stack do topo da fatia
                for (int k = 1; k <= 3; k++) { // Construir cada vértice
                    switch (k) {
                        case 1:
                            alfa_j = j;
                            beta_i = i;
                            break;
                        case 2:
                            alfa_j = j;
                            beta_i = i - 1;
                            break;
                        case 3:
                            alfa_j = j + 1;
                            beta_i = i - 1;
                            break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            } else if (i == 1) {
                // 1 triangulo da stack da base da fatia
                for (int k = 1; k <= 3; k++) { // Construir cada vértice
                    switch (k) {
                        case 1:
                            alfa_j = j;
                            beta_i = i;
                            break;
                        case 2:
                            alfa_j = j;
                            beta_i = i - 1;
                            break;
                        case 3:
                            alfa_j = j + 1;
                            beta_i = i;
                            break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            } else {// 2 triangulos da stack i da fatia que juntos formam um quadrilátero
                for (int k = 1; k <= 6; k++) { // Construir cada vértice
                    switch (k) {
                        //Vertices correspondentes ao Triangulo 1
                        case 1:
                            alfa_j = j;
                            beta_i = i;
                            break;
                        case 2:
                            alfa_j = j;
                            beta_i = i - 1;
                            break;
                        case 3:
                            alfa_j = j + 1;
                            beta_i = i;
                            break;
                            //Vertices correspondentes ao Triangulo 2
                        case 4:
                            alfa_j = j;
                            beta_i = i - 1;
                            break;
                        case 5:
                            alfa_j = j + 1;
                            beta_i = i - 1;
                            break;
                        case 6:
                            alfa_j = j + 1;
                            beta_i = i;
                            break;
                    }
                    findPosition(f, raio, stacks, slices, alfa_j, beta_i);
                }
            }
        }
    }

    write_normal(f,normal);
    write_texture(f,texture);

    fclose(f);
}