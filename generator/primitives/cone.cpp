#include "cone.h"
#include "../utils/utils.h"
#include <math.h>

std::vector<float> normalcone, texturecone;

void add_point_normalcone(float x, float y, float z) {
    normalcone.push_back(x);
    normalcone.push_back(y);
    normalcone.push_back(z);
}

void add_point_texturecone(float f1, float f2) {
    texturecone.push_back(f1);
    texturecone.push_back(f2);
}


void add_cone_normalcone(std::vector<float> &normalcone_, float r1, float rp, float h1, float hp, float a, float angulo) {
    float p1[3], p2[3], p3[3], p4[3];

    p1[0] = r1 * cos(a - angulo);
    p1[1] = h1;
    p1[2] = r1 * sin(a - angulo);

    p2[0] = r1 * cos(a + angulo);
    p2[1] = h1;
    p2[2] = r1 * sin(a + angulo);

    p3[0] = (r1 - rp) * cos(a);
    p3[1] = h1 + hp;
    p3[2] = (r1 - rp) * sin(a);

    p4[0] = (r1 + rp) * cos(a);
    p4[1] = h1 - hp;
    p4[2] = (r1 + rp) * sin(a);

    bezier_add_normal(normalcone_, p1, p2, p3, p4);
}

void add_texturecone(float a, float h, float altura) {
    float h1 = (h + (altura / 2)) / altura;
    float angulo = a / (2 * M_PI);
    add_point_texturecone(angulo, h1);
}

void cone(char *file, float h, float r, float slices, float stacks) {
    FILE *f = fopen(file, "w");
    float a = 0;
    float h1 = -h / 2;
    float h2;
    float r1 = r;
    float r2 = 0;
    float angulo = (float) (2 * M_PI) / (slices);


    //base
    while (a < 2 * M_PI) {
        write_point(f, 0, h1, 0);
        write_point(f, r * cos(a), h1, r * sin(a));
        a += angulo;
        write_point(f, r * cos(a), h1, r * sin(a));

        add_point_normalcone(0, h1, 0);
        add_point_normalcone(0, h1, 0);
        add_point_normalcone(0, h1, 0);

        add_point_texturecone(0, 0);
        add_point_texturecone(0, 0);
        add_point_texturecone(0, 0);
    }
    a = 0;

    //h-((r/h)*x)
    for (int i = 0; i < stacks; i++) {
        r2 = r1 - r / stacks;
        h2 = h1 + h / stacks;
        while (a < 2 * M_PI) {
            write_point(f, r1 * cos(a), h1, r1 * sin(a));
            write_point(f, r2 * cos(a), h2, r2 * sin(a));
            write_point(f, r1 * cos(a + angulo), h1, r1 * sin(a + angulo));

            add_cone_normalcone(normalcone, r1, r / stacks, h1, h / stacks, a, angulo);
            add_cone_normalcone(normalcone, r2, r / stacks, h2, h / stacks, a, angulo);
            add_cone_normalcone(normalcone, r1, r / stacks, h1, h / stacks, a + angulo, angulo);

            add_texturecone(a, h1, h);
            add_texturecone(a, h2, h);
            add_texturecone(a + angulo, h1, h);

            write_point(f, r2 * cos(a), h2, r2 * sin(a));
            write_point(f, r2 * cos(a + angulo), h2, r2 * sin(a + angulo));
            write_point(f, r1 * cos(a + angulo), h1, r1 * sin(a + angulo));

            add_cone_normalcone(normalcone, r2, r / stacks, h2, h / stacks, a, angulo);
            add_cone_normalcone(normalcone, r2, r / stacks, h2, h / stacks, a + angulo, angulo);
            add_cone_normalcone(normalcone, r1, r / stacks, h1, h / stacks, a + angulo, angulo);

            add_texturecone(a, h2, h);
            add_texturecone(a + angulo, h2, h);
            add_texturecone(a + angulo, h1, h);


            a += angulo;
        }
        h1 = h2;
        r1 = r2;
        a = 0;
    }

    write_normal(f, normalcone);
    write_texture(f, texturecone);

    fclose(f);
}