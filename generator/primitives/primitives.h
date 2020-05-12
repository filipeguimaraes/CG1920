#include "../utils/utils.h"
#ifndef GENERATOR_PRIMITIVES_H
#define GENERATOR_PRIMITIVES_H

#define REGULAR 1
#define INVERT -(REGULAR)

int plane(char * file_path, float a);

int box(char * file_path, float x, float y, float z, int div);

void cone(char * file, float h, float r, float slices, float stacks);

void sphere(char * file, float raio, int slices, int stacks);

#endif //GENERATOR_PRIMITIVES_H
