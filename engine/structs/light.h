//
// Created by gonca on 17/05/20.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include <GL/glew.h>

typedef struct light * LIGHT;

LIGHT init_light(GLenum i, double *pos, double *amb, double *dif, double *spec, double *sD, double sE, double sC);

void draw_light(LIGHT l);

void enable_light(LIGHT l);

#endif //ENGINE_LIGHT_H
