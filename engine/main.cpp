#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <structs/ponto_3d.h>
#include <stdio.h>

float myanglex = 0;
float myangley = 0;
float myanglez = 0;
float alt = 1;
float myx = 0;
float myz = 0;
std::vector<PONTO> pontos;

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


void draw_from_file(char *file) {
    if(pontos.empty()){
        FILE *f;
        float x,y,z;
        f = fopen(file, "r");
        while(!feof(f)){
            fscanf_s(f,"%f, %f, %f\n",&x,&y,&z);
            PONTO p; p.x=x; p.y=y; p.z=z;
            pontos.push_back(p);
        }
        fclose(f);
    }
    int k =  pontos.size();
    for (int j = 0; j < k; ++j) {
        float cor=0.0f,cor1=0.0f,cor2=0.0f;
        if (j%3==0)cor=cos(j),cor1=sin(j),cor2=sin(j)*cos(j),glColor3f(cor2, cor1, cor);
        glVertex3f(pontos[j].x,pontos[j].y,pontos[j].z);
    }
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);


    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f( 5.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
    //geometric transformations
    glTranslatef(myx,0,myz);
    glRotatef(myanglex,1,0,0);
    glRotatef(myangley,0,1,0);
    glRotatef(myanglez,0,0,1);
    //para não ir para baixo
    if(alt<0) alt=0;
    glScalef(1,alt,1);

    //drawing instructions
    glBegin(GL_TRIANGLES);

    draw_from_file("new_box");

    glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

void keyboardIsPressed(unsigned char key, int x, int y){
    switch (key){
        case 'a':
            myx=myx-0.05;
            glutPostRedisplay();
            break;
        case 'd':
            myx+=0.05;
            glutPostRedisplay();
            break;
        case 'w':
            myz-=0.05;
            glutPostRedisplay();
            break;
        case 's':
            myz+=0.05;
            glutPostRedisplay();
            break;
        case 'x':
            alt+=0.05;
            glutPostRedisplay();
            break;
        case 'z':
            alt-=0.05;
            glutPostRedisplay();
            break;
        case 'm':
            myanglex+=2;
            glutPostRedisplay();
            break;
        case 'n':
            myanglex-=2;
            glutPostRedisplay();
            break;
        case 'v':
            myangley+=2;
            glutPostRedisplay();
            break;
        case 'b':
            myangley-=2;
            glutPostRedisplay();
            break;
        case 'j':
            myanglez+=2;
            glutPostRedisplay();
            break;
        case 'k':
            myanglez-=2;
            glutPostRedisplay();
            break;
        default:
            break;
    }
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

	
// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardIsPressed);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
