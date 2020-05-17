#include "light.h"
#include <GL/glew.h>
#include <malloc.h>

struct light {
    GLenum number; // number of the light
    float pos[4]; // position
    float amb[4]; // ambient component
    float dif[4]; // diffuse component
    float spec[4]; // specular component
    float spotD[3]; // direction
    float spotExp;
    float spotCut;
};


LIGHT init_light(GLenum i, double *pos, double *amb, double *dif, double *spec, double *sD, double sE, double sC) {
    LIGHT result = (LIGHT) malloc(sizeof(struct light));
    if (!result)
        return NULL;

    result->number = i;
    for(int i = 0; i < 4; i++) {
        result->pos[i] = pos[i];
        result->amb[i] = amb[i];
        result->dif[i] = dif[i];
        result->spec[i] = spec[i];
        if (i < 3)
            result->spotD[i] = sD[i];
    }
    result->spotExp = sE;
    result->spotCut = sC;
    return result;
}

void draw_light(LIGHT l) {
    if (!l)
        return;
    glClearColor(0, 0, 0, 0);
    glLightfv(l->number,GL_POSITION,l->pos);
    glLightfv(l->number,GL_AMBIENT,l->amb);
    glLightfv(l->number,GL_DIFFUSE,l->dif);
    glLightfv(l->number,GL_SPECULAR,l->spec);
    glLightfv(l->number,GL_SPOT_DIRECTION,l->spotD);
    glLightf(l->number,GL_SPOT_EXPONENT,l->spotExp);
    glLightf(l->number,GL_SPOT_CUTOFF,l->spotCut);
}

void enable_light(LIGHT l) {
    if (!l)
        return;
    glEnable(l->number);
}