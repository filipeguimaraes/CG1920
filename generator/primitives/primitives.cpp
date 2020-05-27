#include "primitives.h"
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

void plane_normal(FILE *f) {
    add_point_normal(0, 1, 0);
    add_point_normal(0, 1, 0);
    add_point_normal(0, 1, 0);
    add_point_normal(0, 1, 0);
    add_point_normal(0, 1, 0);
    add_point_normal(0, 1, 0);

    write_normal(f, normal);
}

void plane_texture(FILE *f) {

    add_point_texture(1, 0);
    add_point_texture(1, 1);
    add_point_texture(0, 1);
    add_point_texture(1, 0);
    add_point_texture(0, 1);
    add_point_texture(0, 0);

    write_texture(f, texture);
}


int plane(char *file_path, float a) {

    FILE *f = fopen(file_path, "w");
    write_point(f, a / 2, 0.0f, a / 2);
    write_point(f, a / 2, 0.0f, -a / 2);
    write_point(f, -a / 2, 0.0f, -a / 2);
    write_point(f, a / 2, 0.0f, a / 2);
    write_point(f, -a / 2, 0.0f, -a / 2);
    write_point(f, -a / 2, 0.0f, a / 2);
    plane_normal(f);
    plane_texture(f);
    fclose(f);

    return 0;
}


void planeXZ(FILE *f, float x, float y, float z, float tamx, float tamz, int dir, float x1, float y1, float z1) {
    //pontos
    write_point(f, x * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, x * dir, y, z);

    //normais
    add_point_normal(0, dir, 0);
    add_point_normal(0, dir, 0);
    add_point_normal(0, dir, 0);

    //texturas
    float spacex1 = ((x * dir + (x1 / 2)) / x1) / 4;
    float spacex2 = (((x + tamx) * dir + (x1 / 2)) / x1) / 4;
    float spacez1 = ((z + (z1 / 2)) / z1) / 3;
    float spacez2 = (((z + tamz) + (z1 / 2)) / z1) / 3;


    if (dir == REGULAR) {
        add_point_texture(0.25f + spacex1, 0.666666f + spacez2);
        add_point_texture(0.25f + spacex2, 0.666666f + spacez1);
        add_point_texture(0.25f + spacex1, 0.666666f + spacez1);
    } else {
        add_point_texture(0.25f + spacex1, spacez2);
        add_point_texture(0.25f + spacex2, spacez1);
        add_point_texture(0.25f + spacex1, spacez1);
    }

    write_point(f, x * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, z);

    add_point_normal(0, dir, 0);
    add_point_normal(0, dir, 0);
    add_point_normal(0, dir, 0);

    if (dir == REGULAR) {
        add_point_texture(0.25f + spacex1, 0.666666f + spacez2);
        add_point_texture(0.25f + spacex2, 0.666666f + spacez2);
        add_point_texture(0.25f + spacex2, 0.666666f + spacez1);
    } else {
        add_point_texture(0.25f + spacex1, spacez2);
        add_point_texture(0.25f + spacex2, spacez2);
        add_point_texture(0.25f + spacex2, spacez1);
    }
}

void planeXY(FILE *f, float x, float y, float z, float tamx, float tamy, int dir, float x1, float y1, float z1) {
    write_point(f, x * dir, y, z);
    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, x * dir, y + tamy, z);

    add_point_normal(0, 0, dir);
    add_point_normal(0, 0, dir);
    add_point_normal(0, 0, dir);

    //texturas
    float spacex1 = ((x * dir + (x1 / 2)) / x1) / 4;
    float spacex2 = (((x + tamx) * dir + (x1 / 2)) / x1) / 4;
    float spacey1 = ((y + (y1 / 2)) / y1) / 3;
    float spacey2 = (((y + tamy) + (y1 / 2)) / y1) / 3;

    if (dir == REGULAR) {
        add_point_texture(0.25f + spacex1, 0.333333f + spacey1);
        add_point_texture(0.25f + spacex2, 0.333333f + spacey1);
        add_point_texture(0.25f + spacex1, 0.333333f + spacey2);
    } else {
        add_point_texture(0.75f + spacex1, 0.333333f + spacey1);
        add_point_texture(0.75f + spacex2, 0.333333f + spacey1);
        add_point_texture(0.75f + spacex1, 0.333333f + spacey2);
    }

    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, (x + tamx) * dir, y + tamy, z);
    write_point(f, x * dir, y + tamy, z);

    add_point_normal(0, 0, dir);
    add_point_normal(0, 0, dir);
    add_point_normal(0, 0, dir);

    if (dir == REGULAR) {
        add_point_texture(0.25f + spacex2, 0.333333f + spacey1);
        add_point_texture(0.25f + spacex2, 0.333333f + spacey2);
        add_point_texture(0.25f + spacex1, 0.333333f + spacey2);
    } else {
        add_point_texture(0.75f + spacex2, 0.333333f + spacey1);
        add_point_texture(0.75f + spacex2, 0.333333f + spacey2);
        add_point_texture(0.75f + spacex1, 0.333333f + spacey2);
    }
}

void planeYZ(FILE *f, float x, float y, float z, float tamy, float tamz, int dir, float x1, float y1, float z1) {
    write_point(f, x, y * dir, z);
    write_point(f, x, (y + tamy) * dir, z);
    write_point(f, x, y * dir, z + tamz);

    add_point_normal(dir, 0, 0);
    add_point_normal(dir, 0, 0);
    add_point_normal(dir, 0, 0);

    //texturas
    float spacez1 = ((z + (z1 / 2)) / z1) / 4;
    float spacez2 = (((z + tamz) + (z1 / 2)) / z1) / 4;
    float spacey1 = ((y * dir + (y1 / 2)) / y1) / 3;
    float spacey2 = (((y + tamy) * dir + (y1 / 2)) / y1) / 3;

    if (dir == REGULAR) {
        add_point_texture(spacez1, 0.333333f + spacey1);
        add_point_texture(spacez1, 0.333333f + spacey2);
        add_point_texture(spacez2, 0.333333f + spacey1);
    } else {
        add_point_texture(0.5f + spacez1, 0.333333f + spacey1);
        add_point_texture(0.5f + spacez1, 0.333333f + spacey2);
        add_point_texture(0.5f + spacez2, 0.333333f + spacey1);
    }


    write_point(f, x, (y + tamy) * dir, z);
    write_point(f, x, (y + tamy) * dir, z + tamz);
    write_point(f, x, y * dir, z + tamz);

    add_point_normal(dir, 0, 0);
    add_point_normal(dir, 0, 0);
    add_point_normal(dir, 0, 0);

    if (dir == REGULAR) {
        add_point_texture(spacez1, 0.333333f + spacey2);
        add_point_texture(spacez2, 0.333333f + spacey2);
        add_point_texture(spacez2, 0.333333f + spacey1);
    } else {
        add_point_texture(0.5f + spacez1, 0.333333f + spacey2);
        add_point_texture(0.5f + spacez2, 0.333333f + spacey2);
        add_point_texture(0.5f + spacez2, 0.333333f + spacey1);
    }
}

int box(char *file_path, float x, float y, float z, int div) {
    float a, b, c;
    a = x / div;
    b = y / div;
    c = z / div;
    FILE *f = fopen(file_path, "w");

    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            //planos paralelos ao XZ
            //plano de cima
            planeXZ(f, -x / 2 + (a * i), y / 2, -z / 2 + (c * j), a, c, REGULAR, x, y, z);

            //plano de baixo
            planeXZ(f, -x / 2 + (a * i), -y / 2, -z / 2 + (c * j), a, c, INVERT, x, y, z);

            //planos paralelos ao XY
            //plano da frente
            planeXY(f, -x / 2 + (a * i), -y / 2 + (b * j), z / 2, a, b, REGULAR, x, y, z);
            //plano de trás
            planeXY(f, -x / 2 + (a * i), -y / 2 + (b * j), -z / 2, a, b, INVERT, x, y, z);

            //planos paralelos ao YZ
            //plano de direita
            planeYZ(f, x / 2, -y / 2 + (b * j), -z / 2 + (c * i), b, c, REGULAR, x, y, z);
            //plano da esquerda
            planeYZ(f, -x / 2, -y / 2 + (b * j), -z / 2 + (c * i), b, c, INVERT, x, y, z);
        }
    }
    write_normal(f, normal);
    write_texture(f, texture);
    fclose(f);
    return 0;
}

void add_cone_normal (std::vector<float> &normal_, float r1, float rp, float h1, float hp, float a, float angulo) {
    float p1[3], p2[3], p3[3], p4[3];

    p1[0] = r1 * cos(a-angulo);
    p1[1] = h1;
    p1[2] = r1 * sin(a-angulo);

    p2[0] = r1 * cos(a+angulo);
    p2[1] = h1;
    p2[2] = r1 * sin(a+angulo);

    p3[0] = (r1-rp) * cos(a);
    p3[1] = h1+hp;
    p3[2] = (r1-rp) * sin(a);

    p4[0] = (r1+rp) * cos(a);
    p4[1] = h1-hp;
    p4[2] = (r1+rp) * sin(a);

    bezier_add_normal(normal_, p1, p2, p3, p4);
}

void cone(char *file, float h, float r, float slices, float stacks) {
    FILE *f = fopen(file, "w");
    float a = 0;
    float h1 = -h / 2;
    float h2;
    float r1 = r;
    float r2 = 0;
    float angulo = (float) (2 * M_PI) / (slices);


    //base
    while (a < 2 * M_PI) {
        write_point(f, 0, h1, 0);
        write_point(f, r * cos(a), h1, r * sin(a));
        a += angulo;
        write_point(f, r * cos(a), h1, r * sin(a));

        add_point_normal( 0, h1, 0);
        add_point_normal( 0, h1, 0);
        add_point_normal( 0, h1, 0);
    }
    a = 0;

    //h-((r/h)*x)
    for (int i = 0; i < stacks; i++) {
        r2 = r1 - r / stacks;
        h2 = h1 + h / stacks;
        while (a < 2 * M_PI) {
            write_point(f, r1 * cos(a), h1, r1 * sin(a));
            write_point(f, r2 * cos(a), h2, r2 * sin(a));
            write_point(f, r1 * cos(a + angulo), h1, r1 * sin(a + angulo));

            add_cone_normal(normal, r1, r/stacks, h1, h/stacks, a, angulo);
            add_cone_normal(normal, r2, r/stacks, h2, h/stacks, a, angulo);
            add_cone_normal(normal, r1, r/stacks, h1, h/stacks, a+angulo, angulo);


            write_point(f, r2 * cos(a), h2, r2 * sin(a));
            write_point(f, r2 * cos(a + angulo), h2, r2 * sin(a + angulo));
            write_point(f, r1 * cos(a + angulo), h1, r1 * sin(a + angulo));

            add_cone_normal(normal, r2, r/stacks, h2, h/stacks, a, angulo);
            add_cone_normal(normal, r2, r/stacks, h2, h/stacks, a+angulo, angulo);
            add_cone_normal(normal, r1, r/stacks, h1, h/stacks, a+angulo, angulo);

            a += angulo;
        }
        h1 = h2;
        r1 = r2;
        a = 0;
    }

    write_normal(f,normal);
    write_texture(f,texture);

    fclose(f);
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
