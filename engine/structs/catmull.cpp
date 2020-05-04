#include <stdlib.h>

#define _USE_MATH_DEFINES

#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>
#include <cstdio>
#include <vector>

#endif



void cross(float *a, float *b, float *res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float *a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}


void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f,  -0.5f},
                     {-0.5f, 0.0f,  0.5f,  0.0f},
                     {0.0f,  1.0f,  0.0f,  0.0f}};

    float a[3][4];

    // Compute A = M * P
    for (int i = 0; i < 3; i++) {
        float auxp[4];
         auxp[0]= p0[i];
         auxp[1]= p1[i];
         auxp[2]= p2[i];
         auxp[3]= p3[i];


        multMatrixVector((float *) m, auxp, a[i]);
    }

    // Compute pos = T * A
    // function t=t³+t²+t+1
    float T[4] = {t * t * t, t * t, t, 1};

    for (int i = 0; i < 3; i++)
        pos[i] = T[0] * a[i][0] + T[1] * a[i][1] + T[2] * a[i][2] + T[3] * a[i][3];

    // compute deriv = T' * A
    float Td[4] = {3 * t * t, 2 * t, 1, 0};

    for (int i = 0; i < 3; i++)
        deriv[i] = Td[0] * a[i][0] + Td[1] * a[i][1] + Td[2] * a[i][2] + Td[3] * a[i][3];

}


void getGlobalCatmullRomPoint(float gt, std::vector<float> * v, float *pos, float *deriv) {

    int num_vertices = v->size() / 3;

    float t = gt * num_vertices; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + num_vertices - 1) % num_vertices;
    indices[1] = (indices[0] + 1) % num_vertices;
    indices[2] = (indices[1] + 1) % num_vertices;
    indices[3] = (indices[2] + 1) % num_vertices;

    float *p0,*p1,*p2,*p3;

    p0 = &((*v)[indices[0]*3]);
    p1 = &((*v)[indices[1]*3]);
    p2 = &((*v)[indices[2]*3]);
    p3 = &((*v)[indices[3]*3]);


    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);
}




float up[3] = {0, 1, 0};


void renderCatmullRomCurve(std::vector<float> * v ) {
// draw curve using line segments with GL_LINE_LOOP
    float pos[3];
    float deriv[3];
    glBegin(GL_POINTS);
    //gt in [0,1[
    for (float gt = 0; gt < 1; gt += 0.01) {
        getGlobalCatmullRomPoint(gt, v, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}


float * calc_catmull(float time, std::vector<float> * v) {

    renderCatmullRomCurve(v);

    // apply transformations here
    float pos[3];
    float deriv[3];
    getGlobalCatmullRomPoint(glutGet(GLUT_ELAPSED_TIME) * 360.f / time, v, pos, deriv);

    normalize(deriv);

    float derivCross[3];
    cross(deriv, up, derivCross);
    normalize(derivCross);
    cross(derivCross, deriv, up);
    normalize(up);

    float m[4][4] = {{deriv[0],      deriv[1],      deriv[2],      0},
                     {up[0],         up[1],         up[2],         0},
                     {derivCross[0], derivCross[1], derivCross[2], 0},
                     {pos[0],        pos[1],        pos[2],        1}};

    glMultMatrixf((float *) (m));

    return (float *) (m);
}

