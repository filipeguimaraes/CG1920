#include "plane.h"
#include "../utils/utils.h"

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