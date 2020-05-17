#include <vector>
#include <GL/glew.h>
#include <cstdlib>
#include <string>
#include <il.h>
#include "model.h"

struct model {
    std::vector<float> * pontos;
    std::vector<float> * pontos_textura;
    std::vector<float> * pontos_normais;
    GLuint vertexBuffer[1];
    GLuint normalBuffer[1];
    GLuint textureBuffer[1];


    std::string * textura_file;
    GLuint idTextura;
    bool temTextura;
    bool temCor;

    float diffuse[4];
    float specular[4];
    float emissive[4];
    float ambient[4];
};


MODEL init_model(){
    MODEL m = (MODEL) malloc(sizeof(struct model));
    m->pontos = new std::vector<float>();
    m->pontos_textura = new std::vector<float>();
    m->pontos_normais = new std::vector<float>();


    m->temTextura = false;
    m->temCor = false;


    for(int i = 0; i < 4; i++) {
        if (i != 3) {
            m->diffuse[i] = 0.8f;
            m->specular[i] = 0.0f;
            m->emissive[i] = 0.0f;
            m->ambient[i] = 0.2f;
        }
        else {
            m->diffuse[i] = 1.0f;
            m->specular[i] = 1.0f;
            m->emissive[i] = 1.0f;
            m->ambient[i] = 1.0f;
        }
    }
    return m;
}


void set_diffuse(MODEL m, double * dif) {
    if (!m)
        return;
    for(int i = 0; i < 3; i++)
        m->diffuse[i] = dif[i];

    m->temCor = true;
}


void set_specular(MODEL m, double * spec) {
    if (!m)
        return;
    for(int i = 0; i < 3; i++)
        m->specular[i] = spec[i];

    m->temCor = true;
}


void set_emissive(MODEL m, double * em) {
    if (!m)
        return;
    for(int i = 0; i < 3; i++)
        m->emissive[i] = em[i];

    m->temCor = true;
}


void set_ambient(MODEL m, double * am) {
    if (!m)
        return;
    for(int i = 0; i < 3; i++)
        m->ambient[i] = am[i];

    m->temCor = true;
}


void set_textura(MODEL m, std::string texture) {
    if (m) {
        m->textura_file = new std::string(std::move(texture));
        m->temTextura = true;
        m->temCor = false;
    }
}


void add_vertice(MODEL m, float v) {
    if (m) {
        m->pontos->push_back(v);
    }
}


void add_normal(MODEL m, float v) {
    if (m) {
        m->pontos_normais->push_back(v);
    }
}


void add_textura(MODEL m, float v) {
    if (m) {
        m->pontos_textura->push_back(v);
    }
}


void init_vbo_model(MODEL m) {
    if (m) {
        std::vector<float> vertices = *m->pontos;
        std::vector<float> normais = *m->pontos_normais;
        std::vector<float> pTextura = *m->pontos_textura;

        float * aux = &vertices[0];
        float * norm = &normais[0];
        float * tex = &pTextura[0];


        glGenBuffers(1, m->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, m->pontos->size() * sizeof(float), aux, GL_STATIC_DRAW);

        glGenBuffers(1,m->normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m->normalBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, m->pontos_normais->size() * sizeof(float), norm, GL_STATIC_DRAW);

        if (m->temTextura) {
            glGenBuffers(1, m->textureBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m->textureBuffer[0]);
            glBufferData(GL_ARRAY_BUFFER, m->pontos_textura->size() * sizeof(float), tex, GL_STATIC_DRAW);
        }
    }
}


void draw_model(MODEL m) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m->emissive);
    glMaterialfv(GL_FRONT, GL_AMBIENT, m->ambient);

    glBindBuffer(GL_ARRAY_BUFFER,m->vertexBuffer[0]);
    glVertexPointer(3,GL_FLOAT,0, 0);

    glBindBuffer(GL_ARRAY_BUFFER,m->normalBuffer[0]);
    glNormalPointer(GL_FLOAT,0,0);

    if (m->temTextura) {
        glBindBuffer(GL_ARRAY_BUFFER,m->textureBuffer[0]);
        glTexCoordPointer(2,GL_FLOAT,0,0);
        glBindTexture(GL_TEXTURE_2D,m->idTextura);
    }

    glDrawArrays(GL_TRIANGLES, 0, m->pontos->size());

    glClearColor(0,0,0,0);
    if (m->temTextura)
        glBindTexture(GL_TEXTURE_2D,0);
}


void load_texture (MODEL m) {
    if (m && m->temTextura) {
        unsigned int t, tw, th;
        unsigned char *texData;

        ilInit();
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        ilGenImages(1, &t);
        ilBindImage(t);
        ilLoadImage((ILstring) m->textura_file->c_str());
        tw = ilGetInteger(IL_IMAGE_WIDTH);
        th = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        texData = ilGetData();

        glGenTextures(1, &m->idTextura);

        glBindTexture(GL_TEXTURE_2D, m->idTextura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}