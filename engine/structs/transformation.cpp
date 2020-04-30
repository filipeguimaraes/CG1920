#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "transformation.h"
#include "catmull.h"

struct transformacao_3d {
    float var[4][4];
    float time;
    std::vector<float> * pontos;
};



float * invert_order_matrix(float m[4][4]){
    static float r[4*4];

    for (int i = 0; i < 4*4; ++i) {
        r[i] = m[i%4][i/4];
    }

    return r;
}

float to_radial(float angle) {
    return angle / 360.f * M_PI * 2;
}


float * calc_rotation_time(TRANSFORMACAO t) {
    float x = t->var[0][0];
    float y = t->var[0][1];
    float z = t->var[0][2];
    float angle = to_radial(glutGet(GLUT_ELAPSED_TIME) * 360.f / t->time);
    float aux[4][4];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            aux[i][j] = i == j ? 1 : 0;

    aux[0][0] = pow(x,2) + (1 - pow(x,2)) * cos(angle);
    aux[0][1] = x * y * (1 - cos(angle)) - z * sin(angle);
    aux[0][2] = x * z * (1 -  cos(angle)) + y * sin(angle);

    aux[1][0] = x * y * (1 - cos(angle)) + z * sin(angle);
    aux[1][1] = pow(y,2) + (1 - pow(y,2)) * cos(angle);
    aux[1][2] = y * z * (1 -  cos(angle)) - x * sin(angle);

    aux[2][0] = x * z * (1 -  cos(angle)) - y * sin(angle);
    aux[2][1] = y * z * (1 -  cos(angle)) + x * sin(angle);
    aux[2][2] = pow(z,2) + (1 - pow(z,2)) * cos(angle);

    return invert_order_matrix(aux);
}

float * calc_curve(TRANSFORMACAO t) {
    float * r;

    if (t->pontos) r = calc_catmull(t->time,t->pontos);
    else r = calc_rotation_time(t);

    return r;
}



float * get_matrix(TRANSFORMACAO t) {
    if (t->time > 0) return calc_curve(t);
    else return invert_order_matrix(t->var);
}


void add_vertice_translate(TRANSFORMACAO t, double x, double y, double z){
    t->pontos->push_back(x);
    t->pontos->push_back(y);
    t->pontos->push_back(z);
}


void set_matriz_id(TRANSFORMACAO mat) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat->var[i][j] = i == j ? 1 : 0;
}


TRANSFORMACAO init_transform(){
    TRANSFORMACAO t = static_cast<TRANSFORMACAO>(malloc(sizeof(struct transformacao_3d)));
    set_matriz_id(t);
    t->time = 0;
    t->pontos = nullptr;
    return t;
}


TRANSFORMACAO scale(double x, double y, double z){
    TRANSFORMACAO t = init_transform();
    t->var[0][0] = x;
    t->var[1][1] = y;
    t->var[2][2] = z;
    return t;
}

TRANSFORMACAO rotation_time(double x, double y, double z, double time){
    TRANSFORMACAO t = init_transform();
    t->time = time;
    t->var[0][0] = x;
    t->var[0][1] = y;
    t->var[0][2] = z;
    return t;
}


TRANSFORMACAO rotation(double x, double y, double z, double alfa){
    float angle = to_radial(alfa);
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


TRANSFORMACAO translate_time(double time){
    TRANSFORMACAO t = init_transform();
    t->time = time;
    t->pontos = new std::vector<float>();
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


void point_transforms_total(PONTO * p, TRANSFORMACAO agregado) {
    PONTO np;
    np.var[0] = np.var[1] = np.var[2] = np.var[3] = 0;
    for (int l = 0; l < 4; ++l)
        for (int c = 0; c < 4; ++c)
            np.var[l] += agregado->var[l][c] * p->var[c];

    for (int i = 0; i < 4; ++i)
        p->var[i] = np.var[i];
}