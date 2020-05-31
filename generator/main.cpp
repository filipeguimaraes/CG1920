#include <iostream>
#include <cstring>
#include <math.h>
#include "utils/utils.h"
#include "bezier/bezier.h"
#include "primitives/plane.h"
#include "primitives/box.h"
#include "primitives/cone.h"
#include "primitives/sphere.h"

int main(int argc, char ** argv) {

    if(argc > 3 && !strcmp(argv[1],"plane") &&
       isNumber(argv[2])){
        plane(argv[3],atof(argv[2]));
    }
    else if(argc > 6 &&
            !strcmp(argv[1],"box") &&
            isNumber(argv[2]) &&
            isNumber(argv[3]) &&
            isNumber(argv[4]) &&
            isNumber(argv[5])){
        box(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atoi(argv[5]));
    }
    else if(argc > 6 && !strcmp(argv[1],"cone") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4]) && isNumber(argv[5])){
        cone(argv[6],atof(argv[2]),atof(argv[3])
                ,atof(argv[4]),atof(argv[5]));
    }
    else if(argc > 5 && !strcmp(argv[1],"sphere") && isNumber(argv[2]) && isNumber(argv[3])
            && isNumber(argv[4])){
        sphere(argv[5],atof(argv[2]),atoi(argv[3])
                ,atoi(argv[4]));
    }
    else if(argc == 5 && !strcmp(argv[1],"bezierPatch") && isNumber(argv[3])){
        BezierPatchTXT bp = read_Bezier_Patches(argv[2]);
        bezierPatches(bp,argv[4],atof(argv[3]));
    }
    else {
        puts("\e[1m");
        puts("---------------------------------   GENERATOR MANUAL   ----------------------------------");
        puts("-----------------------------------------------------------------------------------------");
        puts("-- Plane:                                                                              --");
        puts("-- ./generator plane [plane size] [output file name]                                   --");
        puts("-----------------------------------------------------------------------------------------");
        puts("-- Box:                                                                                --");
        puts("-- ./generator box [X value] [Y value] [Z value] [divisions number] [output file name] --");
        puts("-----------------------------------------------------------------------------------------");
        puts("-- Cone:                                                                               --");
        puts("-- ./generator cone [height] [radius] [slices] [stacks] [output file name]             --");
        puts("-----------------------------------------------------------------------------------------");
        puts("-- Sphere:                                                                             --");
        puts("-- ./generator sphere [radius] [slices] [stacks] [output file name]                    --");
        puts("-----------------------------------------------------------------------------------------");
        puts("-- Bezier Patch:                                                                       --");
        puts("-- ./generator bezierPatch [path to patch file] [teselation level] [output file name]  --");
        puts("-----------------------------------------------------------------------------------------");
        puts("-----------------------------------------------------------------------------------------");
    }
    return 0;
}
