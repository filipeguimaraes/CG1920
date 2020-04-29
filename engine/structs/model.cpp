#include <vector>
#include <GL/glew.h>
#include <cstdlib>
#include <cstdio>
#include "model.h"

struct model {
    std::vector<float> * pontos;
    GLuint vertexBuffer[1];
};


MODEL init_model(){
    MODEL m = (MODEL) malloc(sizeof(struct model));
    m->pontos = new std::vector<float>();
    return m;
}

void add_vertice(MODEL m, float v) {
    if (m) {
        m->pontos->push_back(v);
    }
}

void init_vbo_model(MODEL m) {
    if (m) {
        std::vector<float> vertices = *m->pontos;
        float * aux = &vertices[0];

//        for (int i = 0; i < vertices.size() ; ++i) {
//            printf("%f\n",aux[i]);
//        }

        glGenBuffers(1, m->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, m->pontos->size() * sizeof(float), aux, GL_STATIC_DRAW);
    }
}


void draw_model(MODEL m, TRANSFORMACAO t) {
    /*int k = m->pontos->size();

    for (int j = 0; j < k; j+=3) {
        PONTO p;
        set_ponto(&p, (*(m->pontos))[j], (*(m->pontos))[j+1], (*(m->pontos))[j+2]);
        point_transforms_total(&p, t);
        glVertex3f(p.var[0],p.var[1],p.var[2]);
    }
    */

    glBindBuffer(GL_ARRAY_BUFFER,m->vertexBuffer[0]);
    glVertexPointer(3,GL_FLOAT,0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, m->pontos->size());
}