/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

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
#include "Point.hpp"
#include <math.h>
#include <stdio.h>

class Bezier {
public:
    
    int degree;
    Point ** ctrlPoints;
    float * coefficients;
    
    Bezier(int _degree, Point ** _ctrlPoints);
    ~Bezier();
    
    void calculateCoefficients();
    void draw();
    int factorial(int n);
    float combination(int n, int i);
    Point * evaluateBezier(float t);
};
