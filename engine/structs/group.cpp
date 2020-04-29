

#include <vector>
#include <cstdlib>
#include <GL/gl.h>
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

TRANSFORMACAO agreg_tranforms(GROUP g, TRANSFORMACAO ta) {
    TRANSFORMACAO t = init_transform();
    update_transform(t,ta);
    for (TRANSFORMACAO trans: *(g->transforms))
        update_transform(t, trans);
    return t;
}

void init_vbo_group (GROUP g) {
    for(MODEL m : *(g->models)) {
        init_vbo_model(m);
    }

    for(GROUP child_group : *(g->sub_group)) {
        init_vbo_group(child_group);
    }
}

void draw_group (GROUP g, TRANSFORMACAO ta) {
    TRANSFORMACAO t;

    t = ta == nullptr ? init_transform() : agreg_tranforms(g, ta);

    glPushMatrix();

    glMultMatrixf(get_matrix(t));

    for(MODEL m : *(g->models)) {
        draw_model(m, t);
    }

    for(GROUP child_group : *(g->sub_group)) {
        draw_group(child_group, t);
    }

    glPopMatrix();
}

