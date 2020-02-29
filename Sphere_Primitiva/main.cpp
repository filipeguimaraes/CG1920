#include <iostream>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <errno.h>
#include <string.h>
#include <math.h>

struct Vertice{
    float x;
    float y;
    float z;
};

int main() {

    int fd = open("sphere.3d",O_CREAT | O_RDWR, 0666);

    if(fd == -1){
        errno;
        strerror(errno);
        return -1;
    }

    int slices = 9;
    int stacks = 6;
    float raio = 0.5f;
    float alfa,beta;
    struct Vertice vert;
    int alfa_j = 0, beta_i = 0;

    for(int j = 0; j < slices;j++){ // percorrer todas as fatias da esfera
        for(int i = stacks + 1; i > 0;i--){ // desenhar todos os triangulos de uma fatia da esfera
            if(i == (stacks + 1)){
                // 1 triangulo da stack do topo da fatia
                for(int k = 1; k <= 3; k++){ // Construir cada vértice
                    switch(k){
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i - 1; break;
                    }
                    alfa = (float)(2 * M_PI) * ((float)alfa_j / (float)slices);
                    beta = M_PI * ((float)beta_i / (float)(stacks + 1)) - ((float)M_PI/(float)2);
                    vert.x = (float)raio * cos(beta) * sin(alfa);
                    vert.y = (float)raio * sin(beta);
                    vert.z = (float)raio * cos(beta) * cos(alfa);
                    write(fd,&vert,sizeof(struct Vertice));
                }
            }
            else if(i == 1){
                // 1 triangulo da stack da base da fatia
                for(int k = 1; k <= 3; k++){ // Construir cada vértice
                    switch(k){
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i; break;
                    }
                    alfa = (float)(2 * M_PI) * ((float)alfa_j / (float)slices);
                    beta = M_PI * ((float)beta_i / (float)(stacks + 1)) - ((float)M_PI/(float)2);
                    vert.x = (float)raio * cos(beta) * sin(alfa);
                    vert.y = (float)raio * sin(beta);
                    vert.z = (float)raio * cos(beta) * cos(alfa);
                    write(fd,&vert,sizeof(struct Vertice));
                }
            }
            else{// 2 triangulos da stack i da fatia que juntos formam um quadrilátero
                for(int k = 1; k <= 6; k++){ // Construir cada vértice
                    switch(k){
                        //Vertices correspondentes ao Triangulo 1
                        case 1: alfa_j = j; beta_i = i; break;
                        case 2: alfa_j = j; beta_i = i - 1; break;
                        case 3: alfa_j = j + 1; beta_i = i; break;
                            //Vertices correspondentes ao Triangulo 2
                        case 4: alfa_j = j; beta_i = i - 1; break;
                        case 5: alfa_j = j + 1; beta_i = i - 1; break;
                        case 6: alfa_j = j + 1; beta_i = i; break;
                    }
                    alfa = (float)(2 * M_PI) * ((float)alfa_j / (float)slices);
                    beta = M_PI * ((float)beta_i / (float)(stacks + 1)) - ((float)M_PI/(float)2);
                    vert.x = (float)raio * cos(beta) * sin(alfa);
                    vert.y = (float)raio * sin(beta);
                    vert.z = (float)raio * cos(beta) * cos(alfa);
                    write(fd,&vert,sizeof(struct Vertice));
                }
            }
        }
    }

    lseek(fd,0,SEEK_SET);
    struct Vertice readVertice;
    int totalVertices = 0;
    while(read(fd,&readVertice, sizeof(struct Vertice)) != 0){
        printf(" V1: %f | V2 : %f | V3: %f\n",readVertice.x,readVertice.y,readVertice.z);
        totalVertices++;
    }
    printf("Vertices -> %d", totalVertices);

    close(fd);
    return 0;
}
