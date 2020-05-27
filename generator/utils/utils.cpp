#include "utils.h"
#include <cstring>
#include <math.h>

void write_point(FILE * f, float x, float y, float z){
    fprintf(f,"%f, %f, %f\n",x,y,z);
}

int isNumber(char * num){
    int i;
    for (i = 0; i < strlen(num) && isdigit(num[i]); ++i);
    return i==strlen(num);
}

void write_normal(FILE * f, std::vector<float> &normal){
    fprintf(f, SEPARATOR);
    float x;
    float y;
    float z;
    for (int i = 0; i < normal.size(); i+=3){
        x = normal[i];
        y = normal[i+1];
        z = normal[i+2];
        write_point(f,x,y,z);
    }
}


void write_texture(FILE * f, std::vector<float> &texture) {
    fprintf(f, SEPARATOR);
    int i = 0;
    float x;
    float z;
    while (i < texture.size()) {
        x = texture[i];
        z = texture[i + 1];
        i += 2;
        fprintf(f,"%f, %f\n",x,z);
    }
}

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


void bezier_add_normal(std::vector<float> &normal, float * p1, float * p2, float * p3, float * p4) {
    // fill the normal vector with the normal for vertex at grid location (i,j)

    //ponto 1 (i, j - 1)
    float p1x = p1[0];
    float p1y = p1[1];
    float p1z = p1[2];

    //ponto 2 (i, j + 1)
    float p2x = p2[0];
    float p2y = p2[1];
    float p2z = p2[2];

    //ponto 3 (i - 1, j)
    float p3x = p3[0];
    float p3y = p3[1];
    float p3z = p3[2];

    //ponto 4 (i + 1, j)
    float p4x = p4[0];
    float p4y = p4[1];
    float p4z = p4[2];

    //vetor entre 1 e 2
    float v1_2[3] = {p1x - p2x, p1y - p2y, p1z - p2z};
    normalize(v1_2);

    //vetor entre 3 e 4
    float v3_4[3] = {p3x - p4x, p3y - p4y, p3z - p4z};
    normalize(v3_4);

    //vetor final
    float v[3];
    cross(v1_2, v3_4, v);
    normalize(v);

    //adicionar ao vetor das normais
    normal.push_back(v[0]);//x
    normal.push_back(v[1]);//y
    normal.push_back(v[2]);//z
}


