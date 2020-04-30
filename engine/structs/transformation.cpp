#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "transformation.h"

struct transformacao_3d {
    float var[4][4];
};


void update_transform(TRANSFORMACAO agregado, TRANSFORMACAO transform) {
    float agreg[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            agreg[i][j] = 0;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                agreg[i][j] += agregado->var[i][k] * transform->var[k][j];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            agregado->var[i][j] = agreg[i][j];
}


void point_transforms_total(PONTO * p, TRANSFORMACAO agregado) {
    PONTO np;
    np.var[0] = np.var[1] = np.var[2] = np.var[3] = 0;
    for (int l = 0; l < 4; ++l)
        for (int c = 0; c < 4; ++c)
            np.var[l] += agregado->var[l][c] * p->var[c];

    for (int i = 0; i < 4; ++i)
        p->var[i] = np.var[i];
}

float * get_matrix(TRANSFORMACAO t){
    static float r[4*4];

    for (int i = 0; i < 4*4; ++i) {
        r[i] = t->var[i%4][i/4];
    }

    return r;
}


void set_matriz_id(TRANSFORMACAO mat) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat->var[i][j] = i == j ? 1 : 0;
}


void set_ponto(PONTO * p, float x, float y, float z) {
    p->var[0] = x;
    p->var[1] = y;
    p->var[2] = z;
    p->var[3] = 1;
}


void reset_transfromations(std::vector<TRANSFORMACAO> * transformacoes, TRANSFORMACAO agregado) {
    set_matriz_id(agregado);
    for (int i = 0; i < transformacoes->size(); ++i)
        update_transform(agregado,(*transformacoes)[i]);
}


void open_group(std::vector<int> * historico, std::vector<TRANSFORMACAO> * transformacoes, TRANSFORMACAO agregado) {
    if(transformacoes->empty()) set_matriz_id(agregado);
    historico->push_back(transformacoes->size());
}


void close_group(std::vector<int> * historico, std::vector<TRANSFORMACAO> * transformacoes, TRANSFORMACAO agregado) {
    while (!historico->empty() && (*historico)[historico->size() - 1] < transformacoes->size()) transformacoes->pop_back();
    historico->pop_back();
    reset_transfromations(transformacoes,agregado);
}


void add_transform(std::vector<TRANSFORMACAO> * transformacoes, TRANSFORMACAO agregado, TRANSFORMACAO transformacao) {
    transformacoes->push_back(transformacao);
    update_transform(agregado,transformacao);
}


TRANSFORMACAO init_transform(){
    TRANSFORMACAO t = static_cast<TRANSFORMACAO>(malloc(sizeof(struct transformacao_3d)));
    set_matriz_id(t);
    return t;
}


float to_radial(float angle) {
    return angle / 360.f * M_PI * 2;
}


TRANSFORMACAO scale(double x, double y, double z){
    TRANSFORMACAO t = init_transform();
    t->var[0][0] = x;
    t->var[1][1] = y;
    t->var[2][2] = z;
    return t;
}


TRANSFORMACAO rotationVector(double x, double y, double z, double alfa){
    double angle = to_radial(alfa);
    TRANSFORMACAO t = init_transform();
    t->var[0][0] = pow(x,2) + (1 - pow(x,2)) * cos(angle);
    t->var[0][1] = x * y * (1 - cos(angle)) - z * sin(angle);
    t->var[0][2] = x * z * (1 -  cos(angle)) + y * sin(angle);

    t->var[1][0] = x * y * (1 - cos(angle)) + z * sin(angle);
    t->var[1][1] = pow(y,2) + (1 - pow(y,2)) * cos(angle);
    t->var[1][2] = y * z * (1 -  cos(angle)) - x * sin(angle);

    t->var[2][0] = x * z * (1 -  cos(angle)) - y * sin(angle);
    t->var[2][1] = y * z * (1 -  cos(angle)) + x * sin(angle);
    t->var[2][2] = pow(z,2) + (1 - pow(z,2)) * cos(angle);
    return t;
}


TRANSFORMACAO translate(double x, double y, double z){
    TRANSFORMACAO t = init_transform();
    t->var[0][3] = x;
    t->var[1][3] = y;
    t->var[2][3] = z;
    return t;
}


//DEBUG PRINTS
void print_vectors(std::vector<int> * historico, std::vector<TRANSFORMACAO> * transformacoes) {
    printf("|||||  trans: %zu    ---     hist: %zu     |||||", transformacoes->size(), historico->size());
    printf("\n");
}

void print_matriz(TRANSFORMACAO t){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ||",t->var[i][j]);
        }
        puts(" ");
    }
}
