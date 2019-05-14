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
Point ** ctrlP0, ** ctrlP1, ** ctrlP2, ** ctrlP3, ** ctrlP4, ** ctrlP5, ** ctrlP6;
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
    mainCam->pos.y = 20;
//    mainCam->pos.z = -30;
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
    ctrlP0[0] = new Point(3, 0.5, -18);
    ctrlP0[1] = new Point(4, 0.5, -12);
    ctrlP0[2] = new Point(7, 0.5, -6);
    ctrlP0[3] = new Point(7, 0.5, 1);
    ctrlP0[4] = new Point(6, 0.5, 7);
    ctrlP0[5] = new Point(7, 0.5, 16);
    ctrlP0[6] = new Point(7, 0.5, 23);
    
    // BEZIER CURVE ------------------------- 1
    ctrlP1 = new Point *[7];
    ctrlP1[0] = new Point(-7, 0.5, 22);
    ctrlP1[1] = new Point(-6, 0.5, 15);
    ctrlP1[2] = new Point(1, 0.5, 14);
    ctrlP1[3] = new Point(6, 0.5, 11);
    ctrlP1[4] = new Point(11, 0.5, 5);
    ctrlP1[5] = new Point(14, 0.5, -1);
    ctrlP1[6] = new Point(15, 0.5, -8);
    
    // BEZIER CURVE ------------------------- 2
    ctrlP2 = new Point *[7];
    ctrlP2[0] = new Point(-19, 0.5, -17);
    ctrlP2[1] = new Point(-12, 0.5, -16);
    ctrlP2[2] = new Point(-5, 0.5, -14);
    ctrlP2[3] = new Point(2, 0.5, -11);
    ctrlP2[4] = new Point(5, 0.5, -6);
    ctrlP2[5] = new Point(11, 0.5, -1);
    ctrlP2[6] = new Point(16, 0.5, 4);
    
    // BEZIER CURVE ------------------------- 3
    ctrlP3 = new Point *[7];
    ctrlP3[0] = new Point(10, 0.5, 8);
    ctrlP3[1] = new Point(7, 0.5, 10);
    ctrlP3[2] = new Point(7, 0.5, 17);
    ctrlP3[3] = new Point(7, 0.5, 22);
    ctrlP3[4] = new Point(7, 0.5, 28);
    ctrlP3[5] = new Point(7, 0.5, 34);
    ctrlP3[6] = new Point(9, 0.5, 40);
    
    // BEZIER CURVE ------------------------- 4
    ctrlP4 = new Point *[7];
    ctrlP4[0] = new Point(-2, 0.5, 35);
    ctrlP4[1] = new Point(4, 0.5, 33);
    ctrlP4[2] = new Point(8, 0.5, 27);
    ctrlP4[3] = new Point(8, 0.5, 21);
    ctrlP4[4] = new Point(8, 0.5, 15);
    ctrlP4[5] = new Point(7, 0.5, 6);
    ctrlP4[6] = new Point(10, 0.5, 1);
    
    // BEZIER CURVE ------------------------- 5
    ctrlP5 = new Point *[7];
    ctrlP5[0] = new Point(2, 0.5, 16);
    ctrlP5[1] = new Point(1, 0.5, 9);
    ctrlP5[2] = new Point(3, 0.5, 3);
    ctrlP5[3] = new Point(7, 0.5, -3);
    ctrlP5[4] = new Point(10, 0.5, -8);
    ctrlP5[5] = new Point(8, 0.5, -13);
    ctrlP5[6] = new Point(4, 0.5, -19);
    
    // BEZIER CURVE ------------------------- 6
    ctrlP6 = new Point *[7];
    ctrlP6[0] = new Point(-24, 0.5, 19);
    ctrlP6[1] = new Point(-25, 0.5, 13);
    ctrlP6[2] = new Point(-20, 0.5, 8);
    ctrlP6[3] = new Point(-14, 0.5, 7);
    ctrlP6[4] = new Point(-8, 0.5, 7);
    ctrlP6[5] = new Point(-2, 0.5, 7);
    ctrlP6[6] = new Point(3, 0.5, 7);
    
    p = new Pedestrian*[spawned];
    
    for (int i = 0; i <= spawned; i++) {
        switch (i % 7) {
            case 0:
                p[i] = new Pedestrian(ctrlP0, i);
                break;
            case 1:
                p[i] = new Pedestrian(ctrlP1, i);
                break;
            case 2:
                p[i] = new Pedestrian(ctrlP2, i);
                break;
            case 3:
                p[i] = new Pedestrian(ctrlP3, i);
                break;
            case 4:
                p[i] = new Pedestrian(ctrlP4, i);
                break;
            case 5:
                p[i] = new Pedestrian(ctrlP5, i);
                break;
            case 6:
                p[i] = new Pedestrian(ctrlP6, i);
                break;
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
        if(!c->inCollision(p[i])){
            for (int j = 0; j < spawned; j++) {
                if (i != j) {
                    if (p[i]->inCollision(p[j])) {
                        //                    printf("collision: %d and %d\n", i, j);
                        if (p[i]->bezier->ctrlPoints == p[j]->bezier->ctrlPoints) {
                            //                        printf("   same curve\n", i, j);
                            if (p[i]->forward != p[j]->forward) {
                                p[i]->goAround = true;
                                p[i]->update();
                            }
                            else {
                                if (i < j) {
                                    p[i]->update();
                                }
                            }
                        }
                        else {
                            //                        printf("   diff curve\n", i, j);
                            if (i < j) {
                                p[i]->update();
                            }
                            else {
                                p[i]->goAround = true;
                            }
                        }
                    }
                    else {
                        p[i]->update();
                    }
                }
            }
        }
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
            mainCam->dir.y++;
            break;
        case 3:
            mainCam->dir.y--;
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

void keysInput(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            mainCam->pos.z--;
            break;
        case 's':
            mainCam->pos.z++;
            break;
        case 'a':
            mainCam->pos.x--;
            break;
        case 'd':
            mainCam->pos.x++;
            break;
        default:
            break;
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
    
    glutKeyboardFunc(keysInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(arrowKey);
    glutReshapeFunc(reshape);                                        // Reshape CALLBACK function.
    glutDisplayFunc(display);                                        // Display CALLBACK function.
    glutIdleFunc(idle);                                                // Idle CALLBACK function.
    glutMainLoop();                                                    // Begin graphics program.
    return 0;                                                        // ANSI C requires a return value.
}
