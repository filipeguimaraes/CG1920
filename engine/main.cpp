#include <stdlib.h>
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "structs/transformation.h"
#include "tinyxml/tinyxml.h"
#include "structs/group.h"
#include "mouse/mouse.h"
#include "structs/light.h"
#include <iostream>

std::vector<LIGHT> * luzes = NULL;

GROUP global_group = NULL;

GROUP ps_group = NULL;

TRANSFORMACAO ps_translate = NULL;


MODEL read_file_points(const char *file) {
    MODEL m = init_model();
    add_model(ps_group, m);


    printf("loading solid: %s\n", file);
    FILE *f;
    float x, y, z;
    f = fopen(file, "r");
    int r = 0;
    char buff[256];

    while (!feof(f) && fgets(buff,256,f)) {
        switch (r){
            case 0 :
                if (sscanf(buff, "%f, %f, %f\n", &x, &y, &z) == 3) {
                    add_vertice(m, x);
                    add_vertice(m, y);
                    add_vertice(m, z);
                }
                else r = 1;
                break;

            case 1:
                if (sscanf(buff, "%f, %f, %f\n", &x, &y, &z) == 3) {
                    add_normal(m, x);
                    add_normal(m, y);
                    add_normal(m, z);
                }
                else r = 2;
                break;

            case 2:
                if (sscanf(buff, "%f, %f\n", &x, &y) == 2) {
                    add_textura(m, x);
                    add_textura(m, y);
                }
                else r = 3;
                break;

            default:
                break;
        }
    }

    fclose(f);

    return m;
}


void file_atributos(TiXmlAttribute * pAttrib, char ** file, char ** textura, double * d, double * s, double * a, double * e) {
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "file")) *file = strdup(pAttrib->Value()); else
        if (!strcmp(pAttrib->Name(), "texture")) *textura = strdup(pAttrib->Value()); else
        if (!strcmp(pAttrib->Name(), "diffR") && pAttrib->QueryDoubleValue(d+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "diffG") && pAttrib->QueryDoubleValue(d+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "diffB") && pAttrib->QueryDoubleValue(d+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specR") && pAttrib->QueryDoubleValue(s+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specG") && pAttrib->QueryDoubleValue(s+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specB") && pAttrib->QueryDoubleValue(s+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambR" ) && pAttrib->QueryDoubleValue(a+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambG" ) && pAttrib->QueryDoubleValue(a+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambB" ) && pAttrib->QueryDoubleValue(a+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "emisR") && pAttrib->QueryDoubleValue(e+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "emisG") && pAttrib->QueryDoubleValue(e+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "emisB") && pAttrib->QueryDoubleValue(e+2) == TIXML_SUCCESS);
        pAttrib = pAttrib->Next();
    }
}


void scale_translate_atributos(TiXmlAttribute *pAttrib, double *x, double *y, double *z, double *t) {
    *t = *x = *y = *z = 0;
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "X")    && pAttrib->QueryDoubleValue(x) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "Y")    && pAttrib->QueryDoubleValue(y) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "Z")    && pAttrib->QueryDoubleValue(z) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "time") && pAttrib->QueryDoubleValue(t) == TIXML_SUCCESS);
        pAttrib = pAttrib->Next();
    }
}


void rotate_atributos(TiXmlAttribute *pAttrib, double *x, double *y, double *z, double *a, double *t) {
    *t = *a = *x = *y = *z = 0;
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "axisX") && pAttrib->QueryDoubleValue(x) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisY") && pAttrib->QueryDoubleValue(y) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "axisZ") && pAttrib->QueryDoubleValue(z) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "angle") && pAttrib->QueryDoubleValue(a) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "time")  && pAttrib->QueryDoubleValue(t) == TIXML_SUCCESS);
        pAttrib = pAttrib->Next();
    }
}


void light_atributos(TiXmlAttribute *pAttrib, char **t, double *pos, double *amb, double *dif, double *spec, double *spotD, double *spotExp, double *spotCut) {
    while (pAttrib) {
        if (!strcmp(pAttrib->Name(), "type")) *t = strdup(pAttrib->Value()); else
        if (!strcmp(pAttrib->Name(), "posX") && pAttrib->QueryDoubleValue(pos+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "posY") && pAttrib->QueryDoubleValue(pos+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "posZ") && pAttrib->QueryDoubleValue(pos+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "diffR") && pAttrib->QueryDoubleValue(dif+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "diffG") && pAttrib->QueryDoubleValue(dif+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "diffB") && pAttrib->QueryDoubleValue(dif+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specR") && pAttrib->QueryDoubleValue(spec+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specG") && pAttrib->QueryDoubleValue(spec+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "specB") && pAttrib->QueryDoubleValue(spec+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambR" ) && pAttrib->QueryDoubleValue(amb+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambG" ) && pAttrib->QueryDoubleValue(amb+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "ambB" ) && pAttrib->QueryDoubleValue(amb+2) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "dX") && pAttrib->QueryDoubleValue(spotD+0) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "dY") && pAttrib->QueryDoubleValue(spotD+1) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "dZ") && pAttrib->QueryDoubleValue(spotD+2) == TIXML_SUCCESS);else
        if (!strcmp(pAttrib->Name(), "exp") && pAttrib->QueryDoubleValue(spotExp) == TIXML_SUCCESS); else
        if (!strcmp(pAttrib->Name(), "cut") && pAttrib->QueryDoubleValue(spotCut) == TIXML_SUCCESS);
        pAttrib = pAttrib->Next();
    }
}


void elemento_atributos(TiXmlElement *pElement, unsigned int indent) {
    if (!pElement) return;

    if (!strcmp(pElement->Value(), "model")) {
        char *file = NULL;
        char *textura = NULL;
        double diffuse[4] = {0};
        double specular[4] = {0};
        double emissive[4] = {0};
        double ambient[4] = {0};

        for(int i = 0; i < 4; i++) {
            if (i != 3) {
                diffuse[i] = 0.8f;
                specular[i] = 0.0f;
                emissive[i] = 0.0f;
                ambient[i] = 0.2f;
            }
            else {
                diffuse[i] = 1.0f;
                specular[i] = 1.0f;
                emissive[i] = 1.0f;
                ambient[i] = 1.0f;
            }
        }

        file_atributos(pElement->FirstAttribute(), &file, &textura, diffuse, specular, ambient, emissive);

        MODEL m = read_file_points(file);



        set_ambient(m,ambient);
        set_diffuse(m,diffuse);
        set_specular(m,specular);
        set_emissive(m,emissive);
        if (textura) set_textura(m,textura);
    }

    else if (!strcmp(pElement->Value(), "scale")) {
        double x, y, z, time;
        scale_translate_atributos(pElement->FirstAttribute(), &x, &y, &z, &time);

        TRANSFORMACAO t = scale(x,y,z);
        add_transformation(ps_group, t);

    }

    else if (!strcmp(pElement->Value(), "translate")) {
        double x, y, z, time;
        scale_translate_atributos(pElement->FirstAttribute(), &x, &y, &z, &time);

        if (time > 0) {
            TRANSFORMACAO t = translate_time(time);
            add_transformation(ps_group, t);
            ps_translate = t;
        }
        else {
            TRANSFORMACAO t = translate(x,y,z);
            add_transformation(ps_group, t);
        }
    }

    else if (!strcmp(pElement->Value(), "rotate")) {
        double x, y, z, angle, time;
        rotate_atributos(pElement->FirstAttribute(), &x, &y, &z, &angle, &time);

        if (time > 0) {
            TRANSFORMACAO t = rotation_time(x,y,z,time);
            add_transformation(ps_group, t);
        }
        else {
            TRANSFORMACAO t = rotation(x,y,z,angle);
            add_transformation(ps_group, t);
        }
    }

    else if (ps_translate && !strcmp(pElement->Value(), "point")) {
        double x, y, z, time;
        scale_translate_atributos(pElement->FirstAttribute(), &x, &y, &z, &time);

        add_vertice_translate(ps_translate,x,y,z);
    }

    else if (!strcmp(pElement->Value(), "light")) {
        double pos[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // default is a point
        double amb[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // opengl default
        double dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //opengl default
        double spec[4] = { 1.0f, 1.0f, 1.0f, 1.0f}; // opengl default
        double spotD[3] = { 0.0f, 0.0f, -1.0f }; // opengl default
        double spotExp = 0.0f; // opengl default, uniform light dist
        double spotCut = 180.0f; // opengl default, uniform light dist
        char * type = NULL;
        light_atributos(pElement->FirstAttribute(), &type, pos, amb, dif, spec, spotD, &spotExp, &spotCut);

        if (strcmp(type,"DIRECTIONAL") == 0)
            pos[3] = 0.0f;

        LIGHT l = init_light(GL_LIGHT0 + luzes->size(), pos, amb, dif, spec, spotD, spotExp, spotCut);

        luzes->push_back(l);
    }
}



void parse_xml_nodes(TiXmlNode *pParent, unsigned int indent = 0) {
    if (!pParent) return;

    GROUP last = ps_group;

    TiXmlNode *pChild;
    if(!strcmp(pParent->Value(),"group")) {
        GROUP g = init_group();
        add_group(ps_group, g);
        ps_group = g;
    }
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

    if(!strcmp(pParent->Value(),"group")) {
        ps_group = last;
    }
    else if (!strcmp(pParent->Value(),"translate")) {
        ps_translate = NULL;
    }

}


void load_file(const char *pFilename) {
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
    for (auto l : *luzes)
        draw_light(l);

    draw_group(global_group);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(getCamX(), getCamY(), getCamZ(),
              getlookX(), getlookY(), getlookZ(),
              getupX(), getupY(), getupZ());

/*
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
*/
    //drawing instructions
//    glPolygonMode(GL_FRONT, GL_LINE);


    glColor3f(1,1,1);

    draw_from_vector();
    //glutSolidTeapot(1);
    // End of frame
    glutSwapBuffers();
}


void init(const char *file) {
    if (!global_group ) {
#ifndef __APPLE__
        glewInit();
#endif
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        luzes = new std::vector<LIGHT>();

        global_group = init_group();
        ps_group = global_group;

        load_file(file);

        if (luzes->size() > 0)
            glEnable(GL_LIGHTING);
        for(auto l : *luzes) {
            enable_light(l);
        }

        init_vbo_group(global_group);

        glEnable(GL_TEXTURE_2D);

        load_textures(global_group);
    }
}

int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    if (argc > 1) init(argv[1]);

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);


//registration of the mouse (functions in mouse.h)
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
   // glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
