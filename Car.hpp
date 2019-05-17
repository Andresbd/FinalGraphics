//
//  Car.hpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/17/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#pragma once

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
#include "Plane.hpp"

class Car
{
public:
    Car (float _x, float _y, float _z);
    Car(float _x, float _y, float _z, float _v);
    
    GLfloat* global_ambient;
    GLfloat *ka1, *ks1, *kd1, *alpha1;
    
    GLMmodel* sintel2;
    float* pos;
    float velocity;
    float* dims;
    float* center;
    int rot;
    float speed;
    float sintel_pos[3];
    float sintel_dims[3];
    float rotation;
    float radius;
    
    void draw();
    void move(float _x, float _z);
    void update();
    
    ~Car();
};
