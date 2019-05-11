/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Pedestrian.hpp"

Pedestrian::Pedestrian(float _r, float _g, float _b, Point ** _ctrlPoints) {
    
    bezier = new Bezier(6, _ctrlPoints);
    location = new Point(bezier->evaluateBezier(0));
    r = _r;
    g = _g;
    b = _b;
    t = 0;
    forward = true;
    
    ka0 = new GLfloat[4]; // Ambient
    kd0 = new GLfloat[4]; // Diffuse
    ks0 = new GLfloat[4]; // Specular
    alpha0 = new GLfloat[1]; // Shininess
    
    ka0[0] = 0.8f;
    ka0[1] = 0.1f;
    ka0[2] = 0.8f;
    ka0[3] = 1.0f;
    
    kd0[0] = 1.0f;
    kd0[1] = 0.4f;
    kd0[2] = 1.0f;
    kd0[3] = 1.0f;
    
    ks0[0] = 1.0f;
    ks0[1] = 1.0f;
    ks0[2] = 1.0f;
    ks0[3] = 1.0f;
    
    alpha0[0] = 50.0f;
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
        glTranslatef(location->x, location->y, location->z);
        glColor3f(r, g, b);
        glutSolidSphere(0.2, 10, 10);
    } glPopMatrix();
    //bezier->draw();
}

void Pedestrian::update() {
    if (t >= 1) {
        forward = false;
    }
    else if (t <= 0) {
        forward = true;
    }
    
    if (forward) {
        t += 0.0005f;
    }
    else {
        t -= 0.0005f;
    }
    location = bezier->evaluateBezier(t);
}
