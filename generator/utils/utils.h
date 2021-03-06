#include <iostream>
#include <vector>
#ifndef GENERATOR_UTILS_H
#define GENERATOR_UTILS_H

#define SEPARATOR "-\n"

void write_point(FILE * f, float x, float y, float z);

int isNumber(char * num);

void write_normal(FILE * f, std::vector<float> &normal);

void write_texture(FILE * f, std::vector<float> &texture);

void cross(float *a, float *b, float *res);

void normalize(float *a);

void bezier_add_normal(std::vector<float> &normal, float * p1, float * p2, float * p3, float * p4);

#endif //GENERATOR_UTILS_H
