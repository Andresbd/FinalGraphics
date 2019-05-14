/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Pedestrian.hpp"

Pedestrian::Pedestrian(Point ** _ctrlPoints, int _id) {
    
    id = _id;
    armRot = 0;
    
    bezier = new Bezier(6, _ctrlPoints);
    r = g = b = 1.0f;
    t = (float)rand() / RAND_MAX;
    location = new Point(bezier->evaluateBezier(t));
    realLocation = new Point(bezier->evaluateBezier(t));
    radius = 0.5f;
    float dirBool = (float)rand() / RAND_MAX;
    if (dirBool < 0.5) {
        forward = false;
    }
    else {
        forward = true;
    }
    if (forward) {
        oldLocation = new Point(bezier->evaluateBezier(t - 0.001));
    }
    else {
        oldLocation = new Point(bezier->evaluateBezier(t + 0.001));
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
}

Pedestrian::~Pedestrian() {
    bezier->~Bezier();
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
    if (id < 6) {
//        bezier->draw();
    }
    //bezier->draw();
}

void Pedestrian::update() {
    armRot++;
    
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
            t += 0.00005f;
        } while (t < 0);
    }
    else {
        do {
            t -= 0.00005f;
        } while (t > 1);
    }
    
    free(oldLocation);
    oldLocation = location;
    location = bezier->evaluateBezier(t);
    realLocation = bezier->evaluateBezier(t);
    
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

