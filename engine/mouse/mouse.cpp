
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float camX = 00, camY = 30, camZ = 40;
float lookX=0, lookY=0,  lookZ=0;
float upX=0, upY=1, upZ=0;
int startX, startY, tracking = 0;


int alpha = 0, beta = 45, r = 50;



float getCamX(){
    return camX;
}

float getCamY(){
    return camY;
}

float getCamZ(){
    return camZ;
}


float getlookX(){
    return lookX;
}

float getlookY(){
    return lookY;
}

float getlookZ(){
    return lookZ;
}


float getupX(){
    return upX;
}

float getupY(){
    return upY;
}

float getupZ(){
    return upZ;
}

void spherical2Cartesian() {

    camX = r * cos(beta) * sin(alpha);
    camY = r * sin(beta);
    camZ = r * cos(beta) * cos(alpha);
}


void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    } else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        } else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {
        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    } else if (tracking == 2) {
        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }

    camX = rAux * sin(alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
    camZ = rAux * cos(alphaAux * M_PI/ 180.0) * cos(betaAux * M_PI / 180.0);
    camY = rAux * sin(betaAux * M_PI / 180.0);
}