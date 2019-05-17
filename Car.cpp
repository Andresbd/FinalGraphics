//
//  Car.cpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/17/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#include "Car.hpp"

Car::Car(float _x, float _y, float _z, float _v)
{
    pos = new float[3];
    pos[0] = _x;
    pos[1] = _y;
    pos[2] = _z;
    
    velocity = _v;
}


Car::Car(float _x, float _y, float _z)
{
    
    rot = 180;
    pos = new float[3];
    dims = new float[3];
    center = new float[3];
    
    pos[0] = _x;
    pos[1] = _y;
    pos[2] = _z;
    
    rotation = 0.0f;
    radius = 0;
    sintel_pos[0] = 0.0f;
    sintel_pos[1] = 0.0f;
    sintel_pos[2] = 0.0f;
    
    velocity = 0.01f;
    
    sintel2 = glmReadOBJ("assets/car.obj");
    glmFacetNormals(sintel2);
    glmDimensions(sintel2, sintel_dims);
    float center[3] = { sintel_pos[0] + sintel_dims[0] / 2.0f,
        sintel_pos[1] + sintel_dims[1] / 2.0f,
        static_cast<float>(sintel_pos[2] + sintel_dims[2] / 2.0) };
    radius = sqrtf(center[0] * center[0] +
                   center[1] * center[1] +
                   center[2] * center[2]);
    
    center[0] = pos[0] + dims[0] / 1.0f;
    center[1] = pos[1] + dims[1] / 1.0f;
    center[2] = pos[2] + dims[2] / 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    ka1 = new GLfloat[4]; // Ambient
    kd1 = new GLfloat[4]; // Diffuse
    ks1 = new GLfloat[4]; // Specular
    alpha1 = new GLfloat[1]; // Shininess

    ka1[0] = 0.1f;
    ka1[1] = 0.1f;
    ka1[2] = 0.1f;
    ka1[3] = 1.0f;

    kd1[0] = 1.0f;
    kd1[1] = 1.0f;
    kd1[2] = 1.0f;
    kd1[3] = 1.0f;

    ks1[0] = 1.0f;
    ks1[1] = 1.0f;
    ks1[2] = 1.0f;
    ks1[3] = 1.0f;

    alpha1[0] = 55.0f;
    
}


void Car::draw()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha1);
    
    glPushMatrix(); {
        glRotatef(rot, 0, -1, 0);
        glTranslated(pos[0], pos[1], pos[2]);
        glmDraw(sintel2, GLM_SMOOTH | GLM_TEXTURE);
    }
    glPopMatrix();
}

void Car::move(float _x, float _z)
{
    pos[0] -= _x;
    pos[2] -= _z;
}
    
    void Car::update()
    {
        glPushMatrix();
        {
            glTranslatef(pos[0], pos[1], pos[2]);
        }
        glPopMatrix();
    }
    
    Car::~Car()
    {
    }
