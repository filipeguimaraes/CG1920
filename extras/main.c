#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float mercurio[3] = {87969.0, 6.9816900, 4.6001200};
float venus[3] = {224701, 10.8942000, 10.7476000};
float terra[3] = {365256.363004, 15.2098232, 14.7098290};
float marte[3] = {686971, 24.9209300, 20.6669000};

float jupiter[3] = {4331572, 81.6520800, 74.0573600};
float saturno[3] = {10759220, 151.3325783, 135.3572956};
float urano[3] = {30799095, 300.4419704 , 274.8938461};
float neptuno[3] = {60190030, 455.3946490, 445.2940833};


float less(float p){
    return p / 1.5;

}

void pontos(float tamanho1, float tamanho2)
{
    float x1;
    float x2;
    float y = 0.0;
    float z1;
    float z2;
    float declive = 1;
    //float declive2 = 2;
    x1 = tamanho1 * tamanho2 / sqrt(pow(tamanho2, 2) + pow(tamanho1, 2) * pow(declive, 2));
    z1 = sqrt(pow(tamanho2, 2) * (1 - (pow(x1, 2) / pow(tamanho1, 2))));
    /*
    x2 = tamanho1*tamanho2 / sqrt( pow(tamanho2,2) + pow(tamanho1,2) *pow(declive2,2));
    z2 = sqrt(pow(tamanho2,2) * (1 - ( pow(x2,2) / pow(tamanho1,2) ) ));
*/
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", tamanho1, 0.0, 0.0);

    //printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n",x2,0.0,-z2);
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", x1, 0.0, -z1);
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", 0.0, 0.0, -tamanho2);

    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", -x1, 0.0, -z1);
    //printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n",-x2,0.0,-z2);
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", -tamanho1, 0.0, 0.0);

    //printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n",-x2,0.0,z2);
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", -x1, 0.0, z1);
    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", 0.0, 0.0, tamanho2);

    printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n", x1, 0.0, z1);
    //printf("<point X=\"%f\" Y=\"%f\" Z=\"%f\" />\n",x2,0.0,z2);
}

void imprime()
{

    printf("mercurio\n");
    printf("<translate time=\"%f\">\n", mercurio[0]);
    pontos(mercurio[1], mercurio[2]);
    printf("</translate >\n");

    printf("venus\n");
    printf("<translate time=\"%f\">\n", venus[0]);
    pontos(venus[1], venus[2]);
    printf("</translate >\n");

    printf("terra\n");
    printf("<translate time=\"%f\">\n", terra[0]);
    pontos(terra[1], terra[2]);
    printf("</translate >\n");

    printf("marte\n");
    printf("<translate time=\"%f\">\n", marte[0]);
    pontos(marte[1], marte[2]);
    printf("</translate >\n");

    printf("jupiter\n");
    printf("<translate time=\"%f\">\n", jupiter[0]);
    pontos(less(jupiter[1]), less(jupiter[2]));
    printf("</translate >\n");

    printf("saturno\n");
    printf("<translate time=\"%f\">\n", saturno[0]);
    pontos(less(saturno[1]), less(saturno[2]));
    printf("</translate >\n");

    printf("urano\n");
    printf("<translate time=\"%f\">\n", urano[0]);
    pontos(less(urano[1]), less(urano[2]));
    printf("</translate >\n");

    printf("neptuno\n");
    printf("<translate time=\"%f\">\n", neptuno[0]);
    pontos(less(neptuno[1]), less(neptuno[2]));
    printf("</translate >\n");
}

int main()
{

    imprime();

    return 0;
}