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
#include "Character.hpp"

GLfloat *Ia, *Is, *Id, *Ip;
Camera* mainCam;

int mouseCords[2];
int mouseMotionType = 0;

Plane * plane;
Pedestrian ** p;
Point ** ctrlP0, ** ctrlP1, ** ctrlP2, ** ctrlP3, ** ctrlP4, ** ctrlP5;
Character * c;

float spawned;

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
    mainCam->dir.y = -45;
    mainCam->pos.y = 30;
    mainCam->pos.z = -30;
    mainCam->fov = 150;
    mainCam->farDist = 250;
    
    c = new Character(0,0);
    
    spawned = 100;
    
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
    
    // BEZIER CURVE ------------------------- 0
    ctrlP0 = new Point *[7];
    ctrlP0[0] = new Point(7, 0, 7.5);
    ctrlP0[1] = new Point(7, 0, 0);
    ctrlP0[2] = new Point(7, 0, -5);
    ctrlP0[3] = new Point(7, 0, -10);
    ctrlP0[4] = new Point(6, 0, -20);
    ctrlP0[5] = new Point(7, 0, -35);
    ctrlP0[6] = new Point(7, 0, -56.8);
    
    // BEZIER CURVE ------------------------- 1
    ctrlP1 = new Point *[7];
    ctrlP1[0] = new Point(-25, 0, -36);
    ctrlP1[1] = new Point(-15, 0, -35);
    ctrlP1[2] = new Point(-5, 0, -37);
    ctrlP1[3] = new Point(5, 0, -38);
    ctrlP1[4] = new Point(15, 0, -39);
    ctrlP1[5] = new Point(20, 0, -40);
    ctrlP1[6] = new Point(24, 0, -40);
    
    // BEZIER CURVE ------------------------- 2
    ctrlP2 = new Point *[7];
    ctrlP2[0] = new Point(16, 0, 7.5);
    ctrlP2[1] = new Point(16, 0, 0);
    ctrlP2[2] = new Point(16, 0, -5);
    ctrlP2[3] = new Point(16, 0, -15);
    ctrlP2[4] = new Point(15, 0, -25);
    ctrlP2[5] = new Point(14, 0, -35);
    ctrlP2[6] = new Point(18, 0, -56);
    
    // BEZIER CURVE ------------------------- 3
    ctrlP3 = new Point *[7];
    ctrlP3[0] = new Point(-25, 0, -30);
    ctrlP3[1] = new Point(-15, 0, -31);
    ctrlP3[2] = new Point(-5, 0, -30);
    ctrlP3[3] = new Point(5, 0, -30);
    ctrlP3[4] = new Point(15, 0, -30);
    ctrlP3[5] = new Point(20, 0, -30);
    ctrlP3[6] = new Point(24, 0, -30);
    
    // BEZIER CURVE ------------------------- 4
    ctrlP4 = new Point *[7];
    ctrlP4[0] = new Point(0, 0, 0);
    ctrlP4[1] = new Point(20, 0, 0);
    ctrlP4[2] = new Point(15, 0, -20);
    ctrlP4[3] = new Point(18, 0, -10);
    ctrlP4[4] = new Point(18, 0, -30);
    ctrlP4[5] = new Point(17, 0, -40);
    ctrlP4[6] = new Point(18, 0, -50);
    
    // BEZIER CURVE ------------------------- 5
    ctrlP5 = new Point *[7];
    ctrlP5[0] = new Point(-25, 0, -32);
    ctrlP5[1] = new Point(-15, 0, -32);
    ctrlP5[2] = new Point(-5, 0, -32);
    ctrlP5[3] = new Point(5, 0, -32);
    ctrlP5[4] = new Point(15, 0, -32);
    ctrlP5[5] = new Point(20, 0, -42);
    ctrlP5[6] = new Point(24, 0, -42);
    
    p = new Pedestrian*[spawned];
    
    for(int x = 0; x <= spawned; x++) {
        if (x<16) {
            p[x] = new Pedestrian(ctrlP0, x);
        }else if (x >= 16 && x < 32) {
            p[x] = new Pedestrian(ctrlP1, x);
        }else if(x >= 32 && x < 48) {
            p[x] = new Pedestrian(ctrlP2, x);
        }else if(x >= 48 && x < 64) {
            p[x] = new Pedestrian(ctrlP3, x);
        }else if(x >= 64 && x < 80) {
            p[x] = new Pedestrian(ctrlP4, x);
        }else if(x >= 80) {
            p[x] = new Pedestrian(ctrlP5, x);
        }
    }
    
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
    for (int i = 0; i <= spawned; i++) {
        p[i]->draw();
    }
    c->draw();
    glutSwapBuffers();                                                // Swap the hidden and visible buffers.
}

void idle()                                                            // Called when drawing is finished.
{
    for (int i = 0; i < spawned; i++) {
        p[i]->update();
    }
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
            mainCam->moveAround(-(mouseCords[1] - y)*0.01, vector3f(1, 0, 0));
            mainCam->moveAround(-(mouseCords[0] - x)*0.01, vector3f(0, 1, 0));
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

void arrowKey(int key, int x, int y) {
    float _x = 0, _z = 0;
    switch (key) {
        case GLUT_KEY_UP:
            _z -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            _z += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            _x -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            _x += 0.1f;
            break;
    }
    c->move(_x*4, _z*4);
    
    glutPostRedisplay();
    
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
    glutSpecialFunc(arrowKey);
    glutReshapeFunc(reshape);                                        // Reshape CALLBACK function.
    glutDisplayFunc(display);                                        // Display CALLBACK function.
    glutIdleFunc(idle);                                                // Idle CALLBACK function.
    glutMainLoop();                                                    // Begin graphics program.
    return 0;                                                        // ANSI C requires a return value.
}
