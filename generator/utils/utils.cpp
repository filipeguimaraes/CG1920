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
