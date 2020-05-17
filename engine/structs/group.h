#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H

#include "model.h"

typedef struct group * GROUP;


GROUP init_group();

void add_model(GROUP g, MODEL m_add);

void add_group(GROUP g, GROUP g_add);

void add_transformation(GROUP g, TRANSFORMACAO t_add);

void init_vbo_group (GROUP g);

void draw_group(GROUP g);

void load_textures(GROUP g);

#endif //ENGINE_GROUP_H
