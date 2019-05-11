//
//  cCamera.hpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/10/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#pragma once
#ifndef cCamera_hpp
#define cCamera_hpp

#include <stdio.h>
#include "vecs.hpp"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

class Camera
{
public:
    Camera();
    ~Camera();
    
    void setView();
    void move(float dist, float angle);
    void moveAround(float angle, vector3f p);
    bool pointInFrustum(vector3f p);
    void rotate(float angle, vector3f p);
    void setCamDef();
    
    vector3f pos;        // Position of camera
    vector3f dir;        // Z unit in camera space
    vector3f up;        // Y unit in camera space
    vector3f pivot;        // Where the camera is looking at
    float nearDist;        // Near plane distance
    float farDist;        // Far plane distance
    float fov;            // Field of view, lens aperture in Y
    int viewportDims[4];
    float ratio;
    
    vector3f xref, yref, zref;
};

#endif /* cCamera_hpp */
