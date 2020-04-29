#ifndef __AUXILIAR_ENGINE_H__
#define __AUXILIAR_ENGINE_H__

#include <vector>

typedef struct ponto_3d {
    float var[4];
} PONTO;

typedef struct transformacao_3d * TRANSFORMACAO;


float * get_matrix(TRANSFORMACAO t);

void set_ponto(PONTO * p, float x, float y, float z);

void point_transforms_total(PONTO *p, TRANSFORMACAO pt);

void update_transform(TRANSFORMACAO agregado, TRANSFORMACAO transform);

void add_transform(std::vector<TRANSFORMACAO> * transformacoes, TRANSFORMACAO agregado, TRANSFORMACAO transformacao);

void close_group(std::vector<int> *historico, std::vector<TRANSFORMACAO> *transformacoes, TRANSFORMACAO agregado);

void open_group(std::vector<int> *historico, std::vector<TRANSFORMACAO> *transformacoes, TRANSFORMACAO agregado);

TRANSFORMACAO init_transform();

TRANSFORMACAO scale(double x, double y, double z);

TRANSFORMACAO rotationVector(double x, double y, double z, double angle);

TRANSFORMACAO translate(double x, double y, double z);

#endif //__AUXILIAR_ENGINE_H__
