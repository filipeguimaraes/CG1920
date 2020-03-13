#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "structs/ponto_3d.h"
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

TRANSFORMACAO trans_agreg;

void update_transform(TRANSFORMACAO transform) {
    float agreg[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            agreg[i][j] = 0;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                agreg[i][j] += trans_agreg.var[i][k] * transform.var[k][j];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            trans_agreg.var[i][j] = agreg[i][j];
}

void point_transforms_total(PONTO *p) {
    if(trans.empty()) return;
    PONTO np;
    np.var[0] = np.var[1] = np.var[2] = np.var[3] = 0;
    for (int l = 0; l < 4; ++l)
        for (int c = 0; c < 4; ++c)
            np.var[l] += trans_agreg.var[l][c] * p->var[c];

    for (int i = 0; i < 4; ++i)
        p->var[i] = np.var[i];
}

void set_matriz_id(TRANSFORMACAO *mat) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            (*mat).var[i][j] = i == j ? 1 : 0;
}

void set_ponto(PONTO *p, float x, float y, float z) {
    p->var[0] = x;
    p->var[1] = y;
    p->var[2] = z;
    p->var[3] = 1;
}

void reset_transfromations() {
    set_matriz_id(&trans_agreg);

    for (int i = 0; i < trans.size(); ++i) {
        update_transform(trans[i]);
    }
}

float to_radial(float angle) {
    float perc = angle / 360.f;
    return perc * M_PI * 2;
}

TRANSFORMACAO rotarionX(float angle) {
    TRANSFORMACAO t;
    set_matriz_id(&t);
    t.var[1][1] = cos(to_radial(angle));
    t.var[1][2] = -sin(to_radial(angle));
    t.var[2][1] = sin(to_radial(angle));
    t.var[2][2] = cos(to_radial(angle));
    return t;
}

TRANSFORMACAO rotarionY(float angle) {
    TRANSFORMACAO t;
    set_matriz_id(&t);
    t.var[0][0] = cos(to_radial(angle));
    t.var[0][2] = sin(to_radial(angle));
    t.var[2][0] = -sin(to_radial(angle));
    t.var[2][2] = cos(to_radial(angle));
    return t;
}

TRANSFORMACAO rotarionZ(float angle) {
    TRANSFORMACAO t;
    set_matriz_id(&t);
    t.var[0][0] = cos(to_radial(angle));
    t.var[0][1] = -sin(to_radial(angle));
    t.var[1][0] = sin(to_radial(angle));
    t.var[1][1] = cos(to_radial(angle));
    return t;
}

TRANSFORMACAO scale(float x, float y, float z) {
    TRANSFORMACAO t;
    set_matriz_id(&t);
    t.var[0][0] = x;
    t.var[1][1] = y;
    t.var[2][2] = z;
    return t;
}

TRANSFORMACAO translate(float x, float y, float z) {
    TRANSFORMACAO t;
    set_matriz_id(&t);
    t.var[0][3] = x;
    t.var[1][3] = y;
    t.var[2][3] = z;
    return t;
}

void open_group() {
    if(trans.empty()) set_matriz_id(&trans_agreg);
    hist.push_back(trans.size());
}


//DEBUG PRINTS
void print_vectors() {
    printf("|||||  trans: %zu    ---     hist: %zu     |||||", trans.size(), hist.size());
    printf("\n");
}

void print_matriz(TRANSFORMACAO * t){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ||",t->var[i][j]);
        }
        puts(" ");
    }
}

void close_group() {
    while (!hist.empty() && hist[hist.size() - 1] < trans.size()) trans.pop_back();
    hist.pop_back();
    reset_transfromations();
}

void add_transform(TRANSFORMACAO t) {
    trans.push_back(t);
    update_transform(t);
}


TiXmlDocument doc;

// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------
const unsigned int NUM_INDENTS_PER_SPACE = 2;

const char *getIndent(unsigned int numIndents) {
    static const char *pINDENT = "                                      + ";
    static const unsigned int LENGTH = strlen(pINDENT);
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTH) n = LENGTH;

    return &pINDENT[LENGTH - n];
}

// same as getIndent but no "+" at the end
const char *getIndentAlt(unsigned int numIndents) {
    static const char *pINDENT = "                                        ";
    static const unsigned int LENGTH = strlen(pINDENT);
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTH) n = LENGTH;

    return &pINDENT[LENGTH - n];
}


void read_file_points(const char *file) {
    printf("loading solid: %s\n", file);
    FILE *f;
    float x, y, z;
    f = fopen(file, "r");
    while (!feof(f) && fscanf(f, "%f, %f, %f\n", &x, &y, &z)) {
        PONTO p;
        set_ponto(&p, x, y, z);

        point_transforms_total(&p);

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

void rotate_atributos(TiXmlAttribute *pAttrib, double *x, double *y, double *z, double *alfa) {
    *alfa = *x = *y = *z = 0;
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "axisX") && pAttrib->QueryDoubleValue(x) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisY") && pAttrib->QueryDoubleValue(y) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisZ") && pAttrib->QueryDoubleValue(z) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "angle") && pAttrib->QueryDoubleValue(alfa) == TIXML_SUCCESS);
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

        add_transform(scale(x,y,z));

    } else if (!strcmp(pElement->Value(), "translate")) {
        double x, y, z;
        scale_translate_atributos(pElement->FirstAttribute(), &x, &y, &z);

        add_transform(translate(x,y,z));

    } else if (!strcmp(pElement->Value(), "rotate")) {
        double x, y, z, angle;
        rotate_atributos(pElement->FirstAttribute(), &x, &y, &z, &angle);

        if (x==1) add_transform(rotarionX(angle));
        if (y==1) add_transform(rotarionY(angle));
        if (z==1) add_transform(rotarionZ(angle));
    }


//    TiXmlAttribute *pAttrib = pElement->FirstAttribute();
//    int i = 0;
//    int ival;
//    double dval;
//    const char *pIndent = getIndent(indent);
//    printf("\n");
//    while (pAttrib) {
//        printf("%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

//        if (!strcmp(pAttrib->Name(), "file")) read_file_points(pAttrib->Value());

//        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) printf(" int=%d", ival);
//        if (pAttrib->QueryDoubleValue(&dval) == TIXML_SUCCESS) printf(" d=%1.1f", dval);
//        printf("\n");
//        i++;
//        pAttrib = pAttrib->Next();
//    }
//    return i;
}


void parse_xml_nodes(TiXmlNode *pParent, unsigned int indent = 0) {
    if (!pParent) return;

    TiXmlNode *pChild;
//    TiXmlText *pText;
//    if(!strcmp(pParent->Value(),"scale") || !strcmp(pParent->Value(),"translate") || !strcmp(pParent->Value(),"rotate")) add_trans();
    if(!strcmp(pParent->Value(),"group")) open_group();
    else{
        int t = pParent->Type();
//        printf("%s", getIndent(indent));
//        int num;

        switch (t) {
            case TiXmlNode::NodeType::TINYXML_DOCUMENT :
//                printf("Document");
                break;

            case TiXmlNode::NodeType::TINYXML_ELEMENT:
//                printf("Element [%s]", pParent->Value());
//                num =
                elemento_atributos(pParent->ToElement(), indent + 1);
/*                switch (num) {
                    case 0:
                        printf(" (No attributes)");
                        break;
                    case 1:
                        printf("%s1 attribute", getIndentAlt(indent));
                        break;
                    default:
                        printf("%s%d attributes", getIndentAlt(indent), num);
                        break;
                }*/
                break;

            case TiXmlNode::NodeType::TINYXML_COMMENT:
//                printf("Comment: [%s]", pParent->Value());
                break;

            case TiXmlNode::NodeType::TINYXML_UNKNOWN:
//                printf("Unknown");
                break;

            case TiXmlNode::NodeType::TINYXML_TEXT:
//                pText = pParent->ToText();
//                printf("Text: [%s]", pText->Value());
                break;

            case TiXmlNode::NodeType::TINYXML_DECLARATION:
//                printf("Declaration");
                break;
            default:
                break;
        }
//        printf("\n");
    }

    for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
        parse_xml_nodes(pChild, indent + 1);
    }
    if(!strcmp(pParent->Value(),"group")) close_group();
}

// load the named file and dump its structure to STDOUT
void dump_to_stdout(const char *pFilename) {
    TiXmlDocument doc(pFilename);
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("%s:\n", pFilename);
        parse_xml_nodes(&doc); // defined later in the tutorial
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

float color = 0;

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
