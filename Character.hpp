//
//  Character.hpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/13/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#pragma once
#ifdef _APPLE_
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
#ifdef _unix_
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include "Point.hpp"
#include <stdlib.h>
#include "vecs.hpp"
#include "Pedestrian.hpp"



class Character
{
public:
    
    Character();
    Character(float x, float z);
    ~Character();
    Point * p;
    void move(float _x, float _z);
    bool inCollision(Pedestrian * other);
    void draw();
    void update();
    
    float radius;
    float armRot;
    GLfloat *ka0, *ks0, *kd0, *alpha0;
};
