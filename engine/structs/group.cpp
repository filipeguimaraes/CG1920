

#include <vector>
#include <cstdlib>
#include <GL/gl.h>
#include <cstdio>
#include "group.h"
#include "model.h"
#include "transformation.h"

struct group {
    std::vector<MODEL> * models;
    std::vector<GROUP> * sub_group;
    std::vector<TRANSFORMACAO> * transforms;
};



GROUP init_group() {
    GROUP g = (GROUP) malloc(sizeof(struct group));
    if (g) {
        g->models = new std::vector<MODEL>();
        g->sub_group = new std::vector<GROUP>();
        g->transforms = new std::vector<TRANSFORMACAO>();
    }
    return g;
}


void add_model(GROUP g, MODEL m_add) {
    if (g) {
        g->models->push_back(m_add);
    }
}


void add_group(GROUP g, GROUP g_add) {
    if (g) {
        g->sub_group->push_back(g_add);
    }
}


void add_transformation(GROUP g, TRANSFORMACAO t_add) {
    if (g) {
        g->transforms->push_back(t_add);
    }
}


void init_vbo_group (GROUP g) {
    for(MODEL m : *(g->models)) {
        init_vbo_model(m);
    }

    for(GROUP child_group : *(g->sub_group)) {
        init_vbo_group(child_group);
    }
}


void apply_transforms(GROUP g){
    for (TRANSFORMACAO t: *(g->transforms)) {
        glMultMatrixf(get_matrix(t));
    }
}


void draw_group (GROUP g) {
    glPushMatrix();

    apply_transforms(g);


    for(MODEL m : *(g->models)) {
        draw_model(m);
    }

    for(GROUP child_group : *(g->sub_group)) {
        draw_group(child_group);
    }

    glPopMatrix();
}

