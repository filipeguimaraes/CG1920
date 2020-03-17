#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "structs/auxiliar_engine.h"
#include "tinyxml/tinyxml.h"

#include <vector>
#include <iostream>

#include <math.h>

float closeup = 10;
float alt = 1;

float angleBETA = M_PI / 4;
float angleALFA = M_PI / 4;


std::vector<PONTO> pontos;


std::vector<TRANSFORMACAO> trans;
std::vector<int> hist;

TRANSFORMACAO trans_agreg = init_transform();


void read_file_points(const char *file) {
    printf("loading solid: %s\n", file);
    FILE *f;
    float x, y, z;
    f = fopen(file, "r");
    while (!feof(f) && fscanf(f, "%f, %f, %f\n", &x, &y, &z)) {
        PONTO p;
        set_ponto(&p, x, y, z);

        point_transforms_total(&p,trans_agreg);

        pontos.push_back(p);
    }
    fclose(f);
}


void file_atributos(TiXmlAttribute * pAttrib, char ** file) {
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "file")) *file = strdup(pAttrib->Value());
        pAttrib = pAttrib->Next();
    }
}


void scale_translate_atributos(TiXmlAttribute *pAttrib, double *x, double *y, double *z) {
    *x = *y = *z = 0;
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "X")) pAttrib->QueryDoubleValue(x); else
        if (!strcmp(pAttrib->Name(), "Y")) pAttrib->QueryDoubleValue(y); else
        if (!strcmp(pAttrib->Name(), "Z")) pAttrib->QueryDoubleValue(z);
        pAttrib = pAttrib->Next();
    }
}


void rotate_atributos(TiXmlAttribute *pAttrib, double *x, double *y, double *z, double *a) {
    *a = *x = *y = *z = 0;
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "axisX") && pAttrib->QueryDoubleValue(x) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisY") && pAttrib->QueryDoubleValue(y) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisZ") && pAttrib->QueryDoubleValue(z) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "angle") && pAttrib->QueryDoubleValue(a) == TIXML_SUCCESS);
        pAttrib = pAttrib->Next();
    }
}


void elemento_atributos(TiXmlElement *pElement, unsigned int indent) {
    if (!pElement) return;

    if (!strcmp(pElement->Value(), "model")) {
        char *file = NULL;
        file_atributos(pElement->FirstAttribute(), &file);
        read_file_points(file);

    } else if (!strcmp(pElement->Value(), "scale")) {
        double x, y, z;
        scale_translate_atributos(pElement->FirstAttribute(),&x,&y,&z);

        TRANSFORMACAO t = scale(x,y,z);
        add_transform(&trans,trans_agreg,t);

    } else if (!strcmp(pElement->Value(), "translate")) {
        double x, y, z;
        scale_translate_atributos(pElement->FirstAttribute(), &x, &y, &z);

        TRANSFORMACAO t = translate(x,y,z);
        add_transform(&trans,trans_agreg,t);

    } else if (!strcmp(pElement->Value(), "rotate")) {
        double x, y, z, angle;
        rotate_atributos(pElement->FirstAttribute(), &x, &y, &z, &angle);

        TRANSFORMACAO t;
        t = rotationVector(x,y,z,angle);
        add_transform(&trans,trans_agreg,t);
    }
}


void parse_xml_nodes(TiXmlNode *pParent, unsigned int indent = 0) {
    if (!pParent) return;

    TiXmlNode *pChild;
    if(!strcmp(pParent->Value(),"group")) open_group(&hist,&trans,trans_agreg);
    else{
        int t = pParent->Type();

        switch (t) {
            case TiXmlNode::NodeType::TINYXML_DOCUMENT :
                break;

            case TiXmlNode::NodeType::TINYXML_ELEMENT:
                elemento_atributos(pParent->ToElement(), indent + 1);
                break;

            case TiXmlNode::NodeType::TINYXML_COMMENT:
                break;

            case TiXmlNode::NodeType::TINYXML_UNKNOWN:
                break;

            case TiXmlNode::NodeType::TINYXML_TEXT:
                break;

            case TiXmlNode::NodeType::TINYXML_DECLARATION:
                break;
            default:
                break;
        }
    }

    for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
        parse_xml_nodes(pChild, indent + 1);
    }

    if(!strcmp(pParent->Value(),"group")) close_group(&hist,&trans,trans_agreg);
}


void dump_to_stdout(const char *pFilename) {
    TiXmlDocument doc(pFilename);
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("%s:\n", pFilename);
        parse_xml_nodes(&doc);
    } else {
        printf("Failed to load file \"%s\"\n", pFilename);
    }
}


void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
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
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void draw_from_vector() {
    int k = pontos.size();
    glColor3f(1, 1, 1);
    for (int j = 0; j < k; ++j) {
        glVertex3f(pontos[j].var[0], pontos[j].var[1], pontos[j].var[2]);
    }
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    float px = closeup * cos(angleBETA) * sin(angleALFA);
    float py = closeup * sin(angleBETA);
    float pz = closeup * cos(angleBETA) * cos(angleALFA);

    gluLookAt(px, py, pz,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);


    glBegin(GL_LINES);
    glColor3f(0, 0, 1.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0, 0);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glColor3f(0, 1.0f, 0);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
    //para não ir para baixo
    if (alt < 0) alt = 0;
    glScalef(1, alt, 1);

    //drawing instructions
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_TRIANGLES);

    draw_from_vector();

    glEnd();

    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events


void keyboardIsPressed(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
            closeup -= 0.25;
            glutPostRedisplay();
            break;
        case 'z':
            closeup += 0.25;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


void processSpecialKeys(int key_code, int xx, int yy) {
    //permite ter explorer mode camera
    if (key_code == GLUT_KEY_LEFT) angleALFA += -0.1;
    if (key_code == GLUT_KEY_RIGHT) angleALFA += 0.1;
    if (key_code == GLUT_KEY_DOWN && (angleBETA - 0.1) > -M_PI / 2) angleBETA += -0.1;
    if (key_code == GLUT_KEY_UP && (angleBETA + 0.1) < M_PI / 2) angleBETA += 0.1;

    glutPostRedisplay();
}

void load_file(const char *file) {
    if (pontos.empty()) {
        dump_to_stdout(file);
    }
}

int main(int argc, char **argv) {
    if (argc > 1) load_file(argv[1]);

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardIsPressed);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
