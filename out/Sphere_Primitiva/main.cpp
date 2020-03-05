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

//encontrar a posição do vertice em coordenadas cartesianas a partir das coordenadas polares
void findPosition(float raio, int stacks, int slices, float alfa_j,float beta_i,struct Vertice *v){
    float alfa = (float)(2 * M_PI) * ((float)alfa_j / (float)slices);
    float beta = M_PI * ((float)beta_i / (float)(stacks + 1)) - ((float)M_PI/(float)2);
    v -> x = (float)raio * cos(beta) * sin(alfa);
    v -> y = (float)raio * sin(beta);
    v -> z = (float)raio * cos(beta) * cos(alfa);
}

int main(int argc, char *argv[]) {
    // O numero de argumentos do programa generator difere consoante a primitiva
    // sphere -> 5 argumentos: 1|nome da primitiva; 2|raio; 3|slices; 4|stacks; 5|nome do ficheiro que vai conter os vértices
    // exemplo para criar ficheiro do modelo, com nome sphere.3d, para uma esfera com 0.5 de raio, 8 slices, 9 stacks: ./generator sphere 0.5 8 9 sphere.3d

    if (strcmp(argv[1], "sphere") == 0) {

        int fd = open(argv[5], O_CREAT | O_RDWR, 0666);
        if (fd == -1) {
            errno;
            strerror(errno);
            return -1;
        }

        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        float raio = (float)atof(argv[2]);
        struct Vertice vert;
        int alfa_j = 0, beta_i = 0;

        for (int j = 0; j < slices; j++) { // percorrer todas as fatias da esfera
            for (int i = stacks + 1; i > 0; i--) { // desenhar todos os triangulos de uma fatia da esfera
                if (i == (stacks + 1)) {
                    // 1 triangulo da stack do topo da fatia
                    for (int k = 1; k <= 3; k++) { // Construir cada vértice
                        switch (k) {
                            case 1: alfa_j = j; beta_i = i; break;
                            case 2: alfa_j = j; beta_i = i - 1; break;
                            case 3: alfa_j = j + 1; beta_i = i - 1; break;
                        }
                        findPosition(raio, stacks, slices, alfa_j, beta_i, &vert);
                        write(fd, &vert, sizeof(struct Vertice));
                    }
                } else if (i == 1) {
                    // 1 triangulo da stack da base da fatia
                    for (int k = 1; k <= 3; k++) { // Construir cada vértice
                        switch (k) {
                            case 1: alfa_j = j; beta_i = i; break;
                            case 2: alfa_j = j; beta_i = i - 1; break;
                            case 3: alfa_j = j + 1; beta_i = i; break;
                        }
                        findPosition(raio, stacks, slices, alfa_j, beta_i, &vert);
                        write(fd, &vert, sizeof(struct Vertice));
                    }
                } else {// 2 triangulos da stack i da fatia que juntos formam um quadrilátero
                    for (int k = 1; k <= 6; k++) { // Construir cada vértice
                        switch (k) {
                            //Vertices correspondentes ao Triangulo 1
                            case 1: alfa_j = j; beta_i = i; break;
                            case 2: alfa_j = j; beta_i = i - 1; break;
                            case 3: alfa_j = j + 1; beta_i = i; break;
                                //Vertices correspondentes ao Triangulo 2
                            case 4: alfa_j = j; beta_i = i - 1; break;
                            case 5: alfa_j = j + 1; beta_i = i - 1; break;
                            case 6: alfa_j = j + 1; beta_i = i; break;
                        }
                        findPosition(raio, stacks, slices, alfa_j, beta_i, &vert);
                        write(fd, &vert, sizeof(struct Vertice));
                    }
                }
            }
        }

        lseek(fd,0,SEEK_SET);
        struct Vertice readVertice;
        int totalVertices = 0;
        while(read(fd,&readVertice, sizeof(struct Vertice)) != 0){
            printf("V1: %f | V2 : %f | V3: %f\n",readVertice.x,readVertice.y,readVertice.z);
            totalVertices++;
        }
        printf("Numero de Vertices -> %d\n", totalVertices);

        close(fd);
        return 0;
    }
}
