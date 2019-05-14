/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Pedestrian.hpp"

Pedestrian::Pedestrian(Point ** _ctrlPoints, int _id) {
    
    id = _id;
    
    bezier = new Bezier(7, _ctrlPoints);
    r = g = b = 1.0f;
    t = (float)rand() / RAND_MAX;
    location = new Point(bezier->evaluateBezier(t));
    realLocation = new Point(bezier->evaluateBezier(t));
    radius = 1.0f;
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
        //glutSolidSphere(0.2, 10, 10);
        // HEAD
        glPushMatrix(); {
            glTranslatef(0, 2.5, 0);
            glutSolidSphere(radius, 10, 10);
        } glPopMatrix();
        // TORSO
        glPushMatrix(); {
            glutSolidSphere(radius, 10, 10);
        } glPopMatrix();
        // LEFT ARM
        glPushMatrix(); {
            glTranslatef(1.5, -0.5, 0);
            glutSolidSphere(radius, 10, 10);
        } glPopMatrix();
        // RIGHT ARM
        glPushMatrix(); {
            glTranslatef(-1.5, 0.5, 0);
            glutSolidSphere(radius, 10, 10);
        } glPopMatrix();
    } glPopMatrix();
    if (id < 6) {
        bezier->draw();
    }
    //bezier->draw();
}

void Pedestrian::update() {
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
            t += 0.01f;
        } while (t < 0);
    }
    else {
        do {
            t -= 0.01f;
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

