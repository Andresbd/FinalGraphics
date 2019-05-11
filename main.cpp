/*
* A01172912 | Andr�s Bustamante D�az
* A01332653 | Miguel Angel Azuara Olivares
* A01336656 | Jos� Alberto Jurado Hern�ndez
* A01362620 | Santiago Beddoe Levy
*/

#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Pedestrian.hpp"
#include "Plane.hpp"
#include "Point.hpp"
#include "cCamera.hpp"

GLfloat *Ia, *Is, *Id, *Ip;
Camera* mainCam;

int mouseCords[2];
int mouseMotionType = 0;

Plane * plane;
Pedestrian * p;
Point ** ctrlPoints;

GLfloat*    global_ambient;

void axes() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    {
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);
        
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 10, 0);
        
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);
    }
    glEnd();
}

void init() // FOR GLUT LOOP
{
    mainCam = new Camera();
    mainCam->pos.y = 15;
    mainCam->pos.z = 20;
    
//    Fuentes de luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat diffusel0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambientl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientl0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusel0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularl0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    global_ambient = new GLfloat[4];
    global_ambient[0] = 0.3f;
    global_ambient[1] = 0.3f;
    global_ambient[2] = 0.3f;
    global_ambient[3] = 1.0f;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    plane = new Plane();
    
    ctrlPoints = new Point *[7];
    
    ctrlPoints[0] = new Point(-7.75, 0, 5.75);
    ctrlPoints[1] = new Point(-6.5, 0, 4.75);
    ctrlPoints[2] = new Point(-6, 0, 2.75);
    ctrlPoints[3] = new Point(-5.75, 0, -1.25);
    ctrlPoints[4] = new Point(-3.75, 0, -0.25);
    ctrlPoints[5] = new Point(-2.25, 0, -1.25);
    ctrlPoints[6] = new Point(-0.5, 0, -2.25);
    
    p = new Pedestrian(0, 0, 1, ctrlPoints);
    
    glEnable(GL_DEPTH_TEST);            // Enable check for close and far objects.
    glClearColor(0.0, 0.0, 0.0, 0.0);    // Clear the color state.
    glMatrixMode(GL_MODELVIEW);            // Go to 3D mode.
    glLoadIdentity();                    // Reset 3D view matrix.
}

void display()                            // Called for each frame (about 60 times per second).
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                // Clear color and depth buffers.
    glLoadIdentity();                                                // Reset 3D view matrix.
    mainCam->setView();
    plane->draw();
    p->draw();
    glutSwapBuffers();                                                // Swap the hidden and visible buffers.
}

void idle()                                                            // Called when drawing is finished.
{
    p->update();
    glutPostRedisplay();                                            // Display again.
}

void reshape(int x, int y)                                            // Called when the window geometry changes.
{
    glMatrixMode(GL_PROJECTION);                                    // Go to 2D mode.
    glLoadIdentity();                                                // Reset the 2D matrix.
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);        // Configure the camera lens aperture.
    glMatrixMode(GL_MODELVIEW);                                        // Go to 3D mode.
    glViewport(0, 0, x, y);                                            // Configure the camera frame dimensions.
    
    gluLookAt(0.0, 1.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    display();
}

void motion(int x, int y) {
    switch (mouseMotionType) {
        case 1:
            mainCam->moveAround(-(mouseCords[1] - y)*0.01, vector3f(0, 1, 0));
            mainCam->moveAround(-(mouseCords[0] - x)*0.01, vector3f(1, 0, 0));
            break;
        case 2:
            mainCam->moveAround(-(mouseCords[1] - x)*0.01, vector3f(0, 0, 1));
            break;
        case 3:
            mainCam->moveAround(-(mouseCords[1] - y)*0.01, vector3f(0, 0, 1));
            break;
        case 4:
            
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    mouseCords[0] = x;
    mouseCords[1] = y;
    int mods;
    
    if (state == GLUT_DOWN) {
        mods = glutGetModifiers();
        if (mods & GLUT_ACTIVE_SHIFT) {
            mouseMotionType = 2;
        }
        else if (mods & GLUT_ACTIVE_ALT) {
            mouseMotionType = 3;
        }
        else if (mods & GLUT_ACTIVE_CTRL) {
            mouseMotionType = 4;
        }
        else {
            mouseMotionType = 1;
        }
    }
}


int main(int argc, char* argv[])
{
    srand(time(NULL));
    glutInit(&argc, argv);                                            // Init GLUT with command line parameters.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);        // Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
    glutInitWindowSize(800, 800);
    glutCreateWindow("CEDETEC - LEGORRETA");
    
    init();
    
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutReshapeFunc(reshape);                                        // Reshape CALLBACK function.
    glutDisplayFunc(display);                                        // Display CALLBACK function.
    glutIdleFunc(idle);                                                // Idle CALLBACK function.
    glutMainLoop();                                                    // Begin graphics program.
    return 0;                                                        // ANSI C requires a return value.
}
