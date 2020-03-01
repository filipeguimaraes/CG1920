#include <iostream>
#include <cstring>
#include <math.h>

#define REGULAR 1
#define INVERT -(REGULAR)

void write_point(FILE * f, float x, float y, float z){
    fprintf(f,"%f, %f, %f\n",x,y,z);
}

int isNumber(char * num){
    int i;
    for (i = 0; i < strlen(num) && isdigit(num[i]); ++i);
    return i==strlen(num);
}

int plane(char * file_path, float a){
    FILE * f = fopen(file_path,"w");
    write_point(f,  a/2,  0.0f,  a/2);
    write_point(f,  a/2,  0.0f, -a/2);
    write_point(f, -a/2,  0.0f, -a/2);
    write_point(f,  a/2,  0.0f,  a/2);
    write_point(f, -a/2,  0.0f, -a/2);
    write_point(f, -a/2,  0.0f,  a/2);
    fclose(f);
    return 0;
}

void planeXZ(FILE * f,  float x, float y, float z, float tamx, float tamz, int dir){
    write_point(f, x * dir          , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, x * dir          , y , z );

    write_point(f, x * dir          , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , (z + tamz) );
    write_point(f, (x + tamx) * dir , y , z );
}

void planeXY(FILE * f,  float x, float y, float z, float tamx, float tamy, int dir){
    write_point(f, x * dir          , y , z );
    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, x * dir          , y + tamy , z );

    write_point(f, (x + tamx) * dir , y , z );
    write_point(f, (x + tamx) * dir , y + tamy , z );
    write_point(f, x * dir          , y + tamy , z );
}

void planeYZ(FILE * f,  float x, float y, float z, float tamy, float tamz, int dir){
    write_point(f, x , y * dir           , z );
    write_point(f, x , (y + tamy) * dir  , z );
    write_point(f, x , y * dir           , z + tamz );

    write_point(f, x , (y + tamy) * dir , z );
    write_point(f, x ,(y + tamy) * dir  , z + tamz );
    write_point(f, x , y * dir          , z + tamz );
}

int box(char * file_path, float x, float y, float z, int div){
    float a,b,c;
    a = x/div;
    b = y/div;
    c = z/div;
    FILE * f = fopen(file_path,"w");

    //planos paralelos ao XZ
    //plano de cima
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXZ(f,-x/2+(a*i),y/2,-z/2+(c*j),a,c,REGULAR);
        }
    }
    //plano de baixo
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXZ(f,-x/2+(a*i),-y/2,-z/2+(c*j),a,c,INVERT);
        }
    }

    //planos paralelos ao XY
    //plano da frente
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXY(f,-x/2+(a*i),-y/2+(b*j),z/2,a,b,REGULAR);
        }
    }
    //plano de trás
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXY(f,-x/2+(a*i),-y/2+(b*j),-z/2,a,b,INVERT);
        }
    }

    //planos paralelos ao YZ
    //plano de direita
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeYZ(f,x/2,-y/2+(b*j),-z/2+(c*i),b,c,REGULAR);
        }
    }
    //plano da esquerda
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeYZ(f,-x/2,-y/2+(b*j),-z/2+(c*i),b,c,INVERT);
        }
    }

    fclose(f);
    return 0;
}

void cone(char * file, float h, float r, float slices, float stacks){
    FILE * f = fopen(file,"w");
    float a = 0;
    float h1 = -h / 2;
    float h2;
    float r1 = r;
    float r2 = 0;
    float angulo = (float)(2 * M_PI) / (slices+1);


    //base
    while (a < 2 * M_PI) {
        write_point(f,0,h1, 0);
        write_point(f,r * cos(a), h1, r * sin(a));
        a += angulo;
        write_point(f,r * cos(a), h1, r * sin(a));
    }
    a=0;

    //h-((r/h)*x)
    for (int i = 0; i < stacks; i++) {
        r2 = r1 - r / stacks;
        h2 = h1 + h / stacks;
        while (a < 2 * M_PI) {
            write_point(f,r1 * cos(a), h1, r1 * sin(a));
            write_point(f,r2 * cos(a), h2, r2 * sin(a));
            write_point(f,r1 * cos(a+ angulo), h1, r1 * sin(a+angulo));

            write_point(f,r2 * cos(a), h2, r2 * sin(a));
            write_point(f,r2 * cos(a+angulo), h2, r2 * sin(a+angulo));
            write_point(f,r1 * cos(a+angulo), h1, r1 * sin(a+angulo));
            a += angulo;
        }
        h1 = h2;
        r1 = r2;
        a = 0;
    }
    fclose(f);
}


int main(int argc, char ** argv) {
    if(argc > 3 && !strcmp(argv[1],"plane") && isNumber(argv[2])){
        plane(argv[3],atof(argv[2]));
    }
    else if(argc > 6 && !strcmp(argv[1],"box") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4]) && isNumber(argv[5])){
        box(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atoi(argv[5]));
    }
    else if(argc > 6 && !strcmp(argv[1],"cone") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4]) && isNumber(argv[5])){
        cone(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atof(argv[5]));
    }
    else puts("Invalid arguments.");
    return 0;
}
