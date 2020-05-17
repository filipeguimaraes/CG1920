#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include "transformation.h"

typedef struct model * MODEL;


MODEL init_model();

void add_vertice(MODEL m, float v);

void init_vbo_model(MODEL m);

void draw_model(MODEL m);

void load_texture (MODEL m);

void set_diffuse(MODEL m, double * dif);

void set_specular(MODEL m, double * spec);

void set_emissive(MODEL m, double * em);

void set_ambient(MODEL m, double * am);

void set_textura(MODEL m, std::string texture);

#endif //ENGINE_MODEL_H
