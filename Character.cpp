//
//  Character.cpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/13/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#include "Character.hpp"

Character::Character()
{
    radius = 1;
    armRot = 0;
}

Character::Character(float x, float z)
{
    p = new Point(x, 0.5, z);
    radius = 1;
    armRot = 0;
    
    ka0 = new GLfloat[4]; // Ambient
    kd0 = new GLfloat[4]; // Diffuse
    ks0 = new GLfloat[4]; // Specular
    alpha0 = new GLfloat[1]; // Shininess
    
    ka0[0] = 0.05 + (0.2 - 0.05) * (float)rand() / RAND_MAX;
    ka0[1] = 0.05 + (0.2 - 0.05) * (float)rand() / RAND_MAX;
    ka0[2] = 0.05 + (0.2 - 0.05) * (float)rand() / RAND_MAX;
    ka0[3] = 1.0f;
    
    kd0[0] = 0.2 + (1.0 - 0.2) * (float)rand() / RAND_MAX;
    kd0[1] = 0.2 + (1.0 - 0.2) * (float)rand() / RAND_MAX;
    kd0[2] = 0.2 + (1.0 - 0.2) * (float)rand() / RAND_MAX;
    kd0[3] = 1.0f;
    
    ks0[0] = 0.4 + (0.8 - 0.4) * (float)rand() / RAND_MAX;
    ks0[1] = 0.4 + (0.8 - 0.4) * (float)rand() / RAND_MAX;
    ks0[2] = 0.4 + (0.8 - 0.4) * (float)rand() / RAND_MAX;
    ks0[3] = 1.0f;
    
    alpha0[0] = 100.0f;
}

Character::~Character()
{
}

void Character::move(float _x, float _z) {
    p->x += _x;
    p->z += _z;
    armRot += 2;
}

void Character::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha0);
    
    glPushMatrix(); {
        
        glTranslatef(p->x, p->y, p->z);
        glScalef(radius, radius, radius);
        glPushMatrix();
        {
            glTranslatef(0.0f, 1.4f, 0.0f);
            glutSolidSphere(0.6, 20, 20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glScalef(1.0f, 0.8f, 0.5f);
            glutSolidSphere(1.0, 20, 20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glRotatef(30 * sin(DEGTORAD(armRot)), 1.0f, 0.0f, 0.0f);
            glTranslatef(1.1f, -0.5f, 0.0f);
            glScalef(0.2f, 0.8f, 0.2f);
            glutSolidSphere(1.0, 20, 20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glRotatef(30 * sin(DEGTORAD(armRot + 180)), 1.0f, 0.0f, 0.0f);
            glTranslatef(-1.1f, -0.5f, 0.0f);
            glScalef(0.2f, 0.8f, 0.2f);
            glutSolidSphere(1.0, 20, 20);
        }
        glPopMatrix();
    } glPopMatrix();
}

bool Character::inCollision(Pedestrian * other){
    
    float sumR = radius + other->radius;
    float sumR2 = sumR * sumR;
    
    float * nrm = new float[3];
    nrm[0] = p->x - other->location->x;
    nrm[1] = p->y - other->location->y;
    nrm[2] = p->z - other->location->z;
    
    float distance2 = (nrm[0] * nrm[0]) + (nrm[1] * nrm[1]) + (nrm[2] * nrm[2]);
    
    if (sumR2 > distance2) {
        delete[] nrm;
        return true;
    }
    else delete[] nrm; return false;
}
