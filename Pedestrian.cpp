/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Pedestrian.hpp"

Pedestrian::Pedestrian(Point ** _ctrlPoints, int _id) {
    
    id = _id;
    
    mainBezier = new Bezier(6, _ctrlPoints);
    r = g = b = 1.0f;
    t = (float)rand() / RAND_MAX;
    location = new Point(mainBezier->evaluateBezier(t));
    realLocation = new Point(mainBezier->evaluateBezier(t));
    radius = 2.5f;
    float dirBool = (float)rand() / RAND_MAX;
    if (dirBool < 0.5) {
        forward = false;
    }
    else {
        forward = true;
    }
    if (forward) {
        oldLocation = new Point(mainBezier->evaluateBezier(t - 0.001));
    }
    else {
        oldLocation = new Point(mainBezier->evaluateBezier(t + 0.001));
    }
    goAround = false;
    sinAround = 0;
    
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
    armRot = 0;
}

Pedestrian::Pedestrian(Point ** _mainPoints, Point ** _backPoints, int _id) {
    
    id = _id;
    
    mainBezier = new Bezier(6, _mainPoints);
    backBezier = new Bezier(6, _backPoints);
    
    activeBezier = &mainBezier;
    
    usingBackup = false;
    isChangingCurve = false;
    
    r = g = b = 1.0f;
    t = (float)rand() / RAND_MAX;
    location = new Point(mainBezier->evaluateBezier(t));
    realLocation = new Point(mainBezier->evaluateBezier(t));
    radius = 1.0f;
    float dirBool = (float)rand() / RAND_MAX;
    if (dirBool < 0.5) {
        forward = false;
    }
    else {
        forward = true;
    }
    if (forward) {
        oldLocation = new Point(mainBezier->evaluateBezier(t - 0.001));
    }
    else {
        oldLocation = new Point(mainBezier->evaluateBezier(t + 0.001));
    }
    goAround = false;
    sinAround = 0;
    
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
    armRot = 0;
}

Pedestrian::~Pedestrian() {
    mainBezier->~Bezier();
    location->~Point();
}

void Pedestrian::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha0);
    
    glPushMatrix(); {
        
        glTranslatef(realLocation->x, realLocation->y, realLocation->z);
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
    //bezier->draw();
}

void Pedestrian::update() {
    armRot += 0.1f;
    
    if (isChangingCurve) {
        vector3f dir(0, 0, 0);
        if (usingBackup) {
            dir.x = mainBezier->evaluateBezier(t)->x - realLocation->x;
            dir.y = mainBezier->evaluateBezier(t)->y - realLocation->y;
            dir.z = mainBezier->evaluateBezier(t)->z - realLocation->z;
        }
        else {
            dir.x = backBezier->evaluateBezier(t)->x - realLocation->x;
            dir.y = backBezier->evaluateBezier(t)->y - realLocation->y;
            dir.z = backBezier->evaluateBezier(t)->z - realLocation->z;
        }
        dir * 0.001f;
        oldLocation = realLocation;
        realLocation->x += dir.x;
        realLocation->y += dir.y;
        realLocation->z += dir.z;
        if (usingBackup) {
            if ((abs(realLocation->x - mainBezier->evaluateBezier(t)->x) < 0.01) &&
                (abs(realLocation->y - mainBezier->evaluateBezier(t)->y) < 0.01) &&
                (abs(realLocation->z - mainBezier->evaluateBezier(t)->z) < 0.01)) {
                isChangingCurve = false;
                usingBackup = !usingBackup;
                activeBezier = &mainBezier;
            }
        }
        else {
            if ((abs(realLocation->x - backBezier->evaluateBezier(t)->x) < 0.01) &&
                (abs(realLocation->y - backBezier->evaluateBezier(t)->y) < 0.01) &&
                (abs(realLocation->z - backBezier->evaluateBezier(t)->z) < 0.01)) {
                isChangingCurve = false;
                usingBackup = !usingBackup;
                activeBezier = &backBezier;
            }
            
        }
        
    }
    else
    {
        if (!goAround) {
            if (t >= 1) {
                forward = false;
            }
            else if (t <= 0) {
                forward = true;
            }
        }
        
        if (forward) {
            do {
                t += 0.0001f;
            } while (t < 0);
        }
        else {
            do {
                t -= 0.0001f;
            } while (t > 1);
        }
        
        oldLocation = location;
        location = (*activeBezier)->evaluateBezier(t);
        realLocation = (*activeBezier)->evaluateBezier(t);
        
        if (goAround) {
            
            vector3f dir(
                         location->x - oldLocation->x,
                         location->y - oldLocation->y,
                         location->z - oldLocation->z);
            
            dir.normalize();
            
            vector3f normToDir(-dir.z, dir.y, dir.x);
            
            normToDir * radius * 5;
            
            sinAround += 0.1;
            realLocation->x += normToDir.x * sin(DEGTORAD(sinAround));
            realLocation->y += normToDir.y * sin(DEGTORAD(sinAround));
            realLocation->z += normToDir.z * sin(DEGTORAD(sinAround));
            
            if (sinAround >= 180) {
                sinAround = 0;
                goAround = false;
            }
            
            
        }
        
    }
}

bool Pedestrian::inCollision(Pedestrian * other) {
    
    float sumR = radius + other->radius;
    float sumR2 = sumR * sumR;
    
    float * nrm = new float[3];
    nrm[0] = location->x - other->location->x;
    nrm[1] = location->y - other->location->y;
    nrm[2] = location->z - other->location->z;
    
    float distance2 = (nrm[0] * nrm[0]) + (nrm[1] * nrm[1]) + (nrm[2] * nrm[2]);
    
    if (sumR2 > distance2) {
        delete[] nrm;
        return true;
    }
    else delete[] nrm; return false;
}

Point ** Pedestrian::getActiveCtrlPoints() {
    return (*activeBezier)->ctrlPoints;
}
