#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define _USE_MATH_DEFINES // always before the include
#include <math.h>
#else
#include <GL/glut.h>
#endif

struct Vertice{
    float x;
    float y;
    float z;
};

float angleBETA = M_PI/4;
float angleALFA = M_PI/4;

#define _USE_MATH_DEFINES
#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void drawSphere() {
    int fd = open("sphere.3d", O_RDONLY);

    struct Vertice readVertice1;
    struct Vertice readVertice2;
    struct Vertice readVertice3;

    glPolygonMode(GL_FRONT,GL_LINE);
    glBegin(GL_TRIANGLES);
        while(read(fd,&readVertice1, sizeof(struct Vertice)) != 0 &&
              read(fd,&readVertice2, sizeof(struct Vertice)) != 0 &&
              read(fd,&readVertice3, sizeof(struct Vertice))){
            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(readVertice1.x, readVertice1.y+0.5f, readVertice1.z);
            glVertex3f(readVertice2.x, readVertice2.y+0.5f, readVertice2.z);
            glVertex3f(readVertice3.x, readVertice3.y+0.5f, readVertice3.z);
            printf("%f,%f,%f\n", readVertice1.x,readVertice1.y,readVertice1.z);
            printf("%f,%f,%f\n", readVertice2.x,readVertice2.y,readVertice2.z);
            printf("%f,%f,%f\n", readVertice3.x,readVertice3.y,readVertice3.z);
        }
    glEnd();
    close(fd);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

    float px = 6 * cos(angleBETA) * sin(angleALFA);
    float py = 6 * sin(angleBETA);
    float pz = 6 * cos(angleBETA) * cos(angleALFA);

    gluLookAt(px,py,pz,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);


    glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f( 100.0f, 0.0f, 0.0f);

        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

	drawSphere();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key_code, int xx, int yy) {
    //permite ter explorer mode camera
    if(key_code==GLUT_KEY_LEFT) angleALFA += -0.1;
    if(key_code==GLUT_KEY_RIGHT) angleALFA += 0.1;
    if(key_code==GLUT_KEY_DOWN && (angleBETA - 0.1) > -M_PI/2) angleBETA += -0.1;
    if(key_code==GLUT_KEY_UP && (angleBETA + 0.1) < M_PI/2) angleBETA += 0.1;

    glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
