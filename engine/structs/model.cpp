#include <vector>
#include <GL/glew.h>
#include <cstdlib>
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

        glGenBuffers(1, m->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, m->pontos->size() * sizeof(float), aux, GL_STATIC_DRAW);
    }
}


void draw_model(MODEL m) {
    glBindBuffer(GL_ARRAY_BUFFER,m->vertexBuffer[0]);
    glVertexPointer(3,GL_FLOAT,0, 0);

    glDrawArrays(GL_TRIANGLES, 0, m->pontos->size());
}