#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include "transformation.h"

typedef struct model * MODEL;


MODEL init_model();

void add_vertice(MODEL m, float v);

void init_vbo_model(MODEL m);

void draw_model(MODEL m, TRANSFORMACAO t);

#endif //ENGINE_MODEL_H
