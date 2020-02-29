#include <iostream>
#include <cstring>

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
            planeXZ(f,-x/2+(a*i),y/2,-z/2+(c*j),a,c,1);
        }
    }
    //plano de baixo
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXZ(f,-x/2+(a*i),-y/2,-z/2+(c*j),a,c,-1);
        }
    }

    //planos paralelos ao XY
    //plano da frente
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXY(f,-x/2+(a*i),-y/2+(b*j),z/2,a,b,1);
        }
    }
    //plano de trás
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeXY(f,-x/2+(a*i),-y/2+(b*j),-z/2,a,b,-1);
        }
    }

    //planos paralelos ao YZ
    //plano de direita
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeYZ(f,x/2,-y/2+(b*j),-z/2+(c*i),b,c,1);
        }
    }
    //plano da esquerda
    for (int i = 0; i < div; ++i) {
        for (int j = 0; j < div; ++j) {
            planeYZ(f,-x/2,-y/2+(b*j),-z/2+(c*i),b,c,-1);
        }
    }

    fclose(f);
    return 0;
}


int main(int argc, char ** argv) {
    if(argc > 3 && !strcmp(argv[1],"plane") && isNumber(argv[2])){
        plane(argv[3],atof(argv[2]));
    }
    else if(argc > 6 && !strcmp(argv[1],"box") && isNumber(argv[2]) && isNumber(argv[3]) && isNumber(argv[4])){
        box(argv[6],atof(argv[2]),atof(argv[3]),atof(argv[4]),atoi(argv[5]));
    }
    else puts("Invalid arguments.");
    return 0;
}
