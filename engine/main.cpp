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

TiXmlDocument doc;

// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------
const unsigned int NUM_INDENTS_PER_SPACE=2;

const char * getIndent( unsigned int numIndents )
{
    static const char * pINDENT="                                      + ";
    static const unsigned int LENGTH=strlen( pINDENT );
    unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
    if ( n > LENGTH ) n = LENGTH;

    return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
    static const char * pINDENT="                                        ";
    static const unsigned int LENGTH=strlen( pINDENT );
    unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
    if ( n > LENGTH ) n = LENGTH;

    return &pINDENT[ LENGTH-n ];
}


void read_file_points(const char *file) {
    printf("loading solid: %s\n",file);
    FILE *f;
    float x, y, z;
    f = fopen(file, "r");
    while (!feof(f) && fscanf(f, "%f, %f, %f\n", &x, &y, &z)) {
        PONTO p;
        p.x = x;
        p.y = y;
        p.z = z;

        pontos.push_back(p);
    }
    fclose(f);
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
    if ( !pElement ) return 0;

    TiXmlAttribute* pAttrib=pElement->FirstAttribute();
    int i=0;
    int ival;
    double dval;
    const char* pIndent=getIndent(indent);
//    printf("\n");
    while (pAttrib)
    {
//        printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());
        if(!strcmp(pAttrib->Name(),"file")) read_file_points(pAttrib->Value());
//        if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
//        if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
//        printf( "\n" );
        i++;
        pAttrib=pAttrib->Next();
    }
    return i;
}

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 )
{
    if ( !pParent ) return;

    TiXmlNode* pChild;
    TiXmlText* pText;
    int t = pParent->Type();
//    printf( "%s", getIndent(indent));
    int num;

    switch ( t )
    {
        case TiXmlNode::NodeType::TINYXML_DOCUMENT :
//            printf( "Document" );
            break;

        case TiXmlNode::NodeType::TINYXML_ELEMENT:
//            printf( "Element [%s]", pParent->Value() );
            num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
/*            switch(num)
            {
                case 0:  printf( " (No attributes)"); break;
                case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
                default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
            }
*/            break;

        case TiXmlNode::NodeType::TINYXML_COMMENT:
            printf( "Comment: [%s]", pParent->Value());
            break;

        case TiXmlNode::NodeType::TINYXML_UNKNOWN:
//            printf( "Unknown" );
            break;

        case TiXmlNode::NodeType::TINYXML_TEXT:
//            pText = pParent->ToText();
//            printf( "Text: [%s]", pText->Value() );
            break;

        case TiXmlNode::NodeType::TINYXML_DECLARATION:
//            printf( "Declaration" );
            break;
        default:
            break;
    }
//    printf( "\n" );
    for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
    {
        dump_to_stdout( pChild, indent+1 );
    }
}

// load the named file and dump its structure to STDOUT
void dump_to_stdout(const char* pFilename){
    puts(pFilename);
    TiXmlDocument doc(pFilename);
    bool loadOkay = doc.LoadFile();
    if (loadOkay)
    {
//        printf("\n%s:\n", pFilename);
        dump_to_stdout( &doc ); // defined later in the tutorial
    }
    else
    {
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


void draw_from_file() {
    int k = pontos.size();
    glColor3f(1, 1, 1);
    for (int j = 0; j < k; ++j) {
        glVertex3f(pontos[j].x, pontos[j].y, pontos[j].z);
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

    draw_from_file();

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
            closeup += 0.25 ;
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
void load_file(const char * file){
    if (pontos.empty()) {
        dump_to_stdout(file);
    }
}

int main(int argc, char **argv) {
    if(argc>1) load_file(argv[1]);

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
