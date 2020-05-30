#include "../utils/utils.h"

#include "box.h"

std::vector<float> normalbox, texturebox;

void add_point_normalbox(float x, float y, float z) {
    normalbox.push_back(x);
    normalbox.push_back(y);
    normalbox.push_back(z);
}

void add_point_texturebox(float f1, float f2) {
    texturebox.push_back(f1);
    texturebox.push_back(f2);
}

void planeXZ(FILE *f, float x, float y, float z, float tamx, float tamz, int dir, float x1, float y1, float z1) {
    //pontos
    write_point(f, x * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, x * dir, y, z);

    //normais
    add_point_normalbox(0, dir, 0);
    add_point_normalbox(0, dir, 0);
    add_point_normalbox(0, dir, 0);

    //texturas
    float spacex1 = ((x * dir + (x1 / 2)) / x1) / 4;
    float spacex2 = (((x + tamx) * dir + (x1 / 2)) / x1) / 4;
    float spacez1 = ((z + (z1 / 2)) / z1) / 3;
    float spacez2 = (((z + tamz) + (z1 / 2)) / z1) / 3;


    if (dir == REGULAR) {
        add_point_texturebox(0.25f + spacex1, 0.666666f + spacez2);
        add_point_texturebox(0.25f + spacex2, 0.666666f + spacez1);
        add_point_texturebox(0.25f + spacex1, 0.666666f + spacez1);
    } else {
        add_point_texturebox(0.25f + spacex1, spacez2);
        add_point_texturebox(0.25f + spacex2, spacez1);
        add_point_texturebox(0.25f + spacex1, spacez1);
    }

    write_point(f, x * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, (z + tamz));
    write_point(f, (x + tamx) * dir, y, z);

    add_point_normalbox(0, dir, 0);
    add_point_normalbox(0, dir, 0);
    add_point_normalbox(0, dir, 0);

    if (dir == REGULAR) {
        add_point_texturebox(0.25f + spacex1, 0.666666f + spacez2);
        add_point_texturebox(0.25f + spacex2, 0.666666f + spacez2);
        add_point_texturebox(0.25f + spacex2, 0.666666f + spacez1);
    } else {
        add_point_texturebox(0.25f + spacex1, spacez2);
        add_point_texturebox(0.25f + spacex2, spacez2);
        add_point_texturebox(0.25f + spacex2, spacez1);
    }
}

void planeXY(FILE *f, float x, float y, float z, float tamx, float tamy, int dir, float x1, float y1, float z1) {
    write_point(f, x * dir, y, z);
    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, x * dir, y + tamy, z);

    add_point_normalbox(0, 0, dir);
    add_point_normalbox(0, 0, dir);
    add_point_normalbox(0, 0, dir);

    //texturas
    float spacex1 = ((x * dir + (x1 / 2)) / x1) / 4;
    float spacex2 = (((x + tamx) * dir + (x1 / 2)) / x1) / 4;
    float spacey1 = ((y + (y1 / 2)) / y1) / 3;
    float spacey2 = (((y + tamy) + (y1 / 2)) / y1) / 3;

    if (dir == REGULAR) {
        add_point_texturebox(0.25f + spacex1, 0.333333f + spacey1);
        add_point_texturebox(0.25f + spacex2, 0.333333f + spacey1);
        add_point_texturebox(0.25f + spacex1, 0.333333f + spacey2);
    } else {
        add_point_texturebox(0.75f + spacex1, 0.333333f + spacey1);
        add_point_texturebox(0.75f + spacex2, 0.333333f + spacey1);
        add_point_texturebox(0.75f + spacex1, 0.333333f + spacey2);
    }

    write_point(f, (x + tamx) * dir, y, z);
    write_point(f, (x + tamx) * dir, y + tamy, z);
    write_point(f, x * dir, y + tamy, z);

    add_point_normalbox(0, 0, dir);
    add_point_normalbox(0, 0, dir);
    add_point_normalbox(0, 0, dir);

    if (dir == REGULAR) {
        add_point_texturebox(0.25f + spacex2, 0.333333f + spacey1);
        add_point_texturebox(0.25f + spacex2, 0.333333f + spacey2);
        add_point_texturebox(0.25f + spacex1, 0.333333f + spacey2);
    } else {
        add_point_texturebox(0.75f + spacex2, 0.333333f + spacey1);
        add_point_texturebox(0.75f + spacex2, 0.333333f + spacey2);
        add_point_texturebox(0.75f + spacex1, 0.333333f + spacey2);
    }
}

void planeYZ(FILE *f, float x, float y, float z, float tamy, float tamz, int dir, float x1, float y1, float z1) {
    write_point(f, x, y * dir, z);
    write_point(f, x, (y + tamy) * dir, z);
    write_point(f, x, y * dir, z + tamz);

    add_point_normalbox(dir, 0, 0);
    add_point_normalbox(dir, 0, 0);
    add_point_normalbox(dir, 0, 0);

    //texturas
    float spacez1 = ((z + (z1 / 2)) / z1) / 4;
    float spacez2 = (((z + tamz) + (z1 / 2)) / z1) / 4;
    float spacey1 = ((y * dir + (y1 / 2)) / y1) / 3;
    float spacey2 = (((y + tamy) * dir + (y1 / 2)) / y1) / 3;

    if (dir == REGULAR) {
        add_point_texturebox(spacez1, 0.333333f + spacey1);
        add_point_texturebox(spacez1, 0.333333f + spacey2);
        add_point_texturebox(spacez2, 0.333333f + spacey1);
    } else {
        add_point_texturebox(0.5f + spacez1, 0.333333f + spacey1);
        add_point_texturebox(0.5f + spacez1, 0.333333f + spacey2);
        add_point_texturebox(0.5f + spacez2, 0.333333f + spacey1);
    }


    write_point(f, x, (y + tamy) * dir, z);
    write_point(f, x, (y + tamy) * dir, z + tamz);
    write_point(f, x, y * dir, z + tamz);

    add_point_normalbox(dir, 0, 0);
    add_point_normalbox(dir, 0, 0);
    add_point_normalbox(dir, 0, 0);

    if (dir == REGULAR) {
        add_point_texturebox(spacez1, 0.333333f + spacey2);
        add_point_texturebox(spacez2, 0.333333f + spacey2);
        add_point_texturebox(spacez2, 0.333333f + spacey1);
    } else {
        add_point_texturebox(0.5f + spacez1, 0.333333f + spacey2);
        add_point_texturebox(0.5f + spacez2, 0.333333f + spacey2);
        add_point_texturebox(0.5f + spacez2, 0.333333f + spacey1);
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
    write_normal(f, normalbox);
    write_texture(f, texturebox);
    fclose(f);
    return 0;
}

