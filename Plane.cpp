/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Plane.hpp"

Plane::Plane() {
    
    rotation = 0.0f;
    radius = 0;
    sintel_pos[0] = 0.0f;
    sintel_pos[1] = 0.0f;
    sintel_pos[2] = 0.0f;
    
    sintel = glmReadOBJ("assets/Legorreta_good.obj");
    glmFacetNormals(sintel);
    glmDimensions(sintel, sintel_dims);
    float center[3] = { sintel_pos[0] + sintel_dims[0] / 2.0f,
        sintel_pos[1] + sintel_dims[1] / 2.0f,
        static_cast<float>(sintel_pos[2] + sintel_dims[2] / 2.0) };
    radius = sqrtf(center[0] * center[0] +
                   center[1] * center[1] +
                   center[2] * center[2]);
    
    printf("SINTEL_DIMS={%.3f,%.3f,%.3f,%.3f}\n", sintel_dims[0], sintel_dims[1], sintel_dims[2]);
    printf("RADIUS=%.3f\n", radius);
    
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

Plane::~Plane(){}

void Plane::draw() {
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha1);
    
    glPushMatrix(); {
        glmDraw(sintel, GLM_SMOOTH | GLM_TEXTURE);
    }
    glPopMatrix();
}

