
#ifndef ENGINE_MOUSE_H
#define ENGINE_MOUSE_H


void processMouseButtons(int button, int state, int xx, int yy);

void processMouseMotion(int xx, int yy);

float getCamX();

float getCamY();

float getCamZ();

#endif //ENGINE_MOUSE_H
