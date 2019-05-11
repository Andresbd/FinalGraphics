//
//  cCamera.cpp
//  proyFinal
//
//  Created by Andres Bustamante on 5/10/19.
//  Copyright © 2019 Andres Bustamante. All rights reserved.
//

#include "cCamera.hpp"

Camera::Camera()
{
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    dir.x = 0;
    dir.y = 0;
    dir.z = -1;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    
    pivot.x = pivot.y = pivot.z = 0;
    nearDist = 1.0f;
    farDist = 50.0f;
    fov = 90;
    setCamDef();
}

void Camera::setView()
{
    int viewportCoords[4];
    glGetIntegerv(GL_VIEWPORT, viewportCoords);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (GLfloat)viewportCoords[2] / (GLfloat)viewportCoords[3], nearDist, farDist);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              pos.x, pos.y, pos.z,
              pos.x + dir.x, pos.y + dir.y, pos.z + dir.z,
              up.x, up.y, up.z
              );
}

void Camera::move(float dist, float angle) {
    vector3f moveDir;
    float cosAng, sinAng, radAng;
    radAng = DEGTORAD(angle);
    cosAng = cos(radAng);
    sinAng = sin(radAng);
    
    float d[] = { dir.x, dir.y, dir.z };
    float u[] = { up.x, up.y, up.z };
    float r[] = { 0,0,0 };
    
    crossProduct(d, u, r);
    vector3f right(r[0], r[1], r[2]);
    moveDir = dir * cosAng - right * sinAng;
    pos = dist * moveDir;
}

bool Camera::pointInFrustum(vector3f p) {
    
    glGetIntegerv(GL_VIEWPORT, viewportDims);
    
    ratio = (float) viewportDims[2] / (float) viewportDims[3];
    
    float tang = 2 * tan(fov / 2);
    float height = nearDist * tang;
    float Wnear = height * ratio;
    vector3f v = p - pos;
    
    float pcz, pcx, pcy;
    
    pcz = vector3f::dotProd(v, zref);
    if (pcz > farDist || pcz < nearDist) {
        return false;
    }
    
    pcy = vector3f::dotProd(v, yref);
    float aux = pcz * tang;
    if (pcy > aux || pcy < -aux) {
        return false;
    }
    
    pcx = vector3f::dotProd(v, xref);
    aux = aux * ratio;
    if (pcx > aux || pcx < -aux) {
        return false;
    }
    
    return true;
}

void Camera::moveAround(float angle, vector3f axis) {
    float d[] = { dir.x, dir.y, dir.z };
    float u[] = { up.x, up.y, up.z };
    float r[] = { 0,0,0 };
    crossProduct(d, u, r);
    float a[] = { axis.x, axis.y, axis.z };
    float oa[] = { axis.x, axis.y, axis.z };
    unitVector(a);
    
    float negPos[] = { pos.x - pivot.x, pos.y - pivot.y, pos.z - pivot.z };
    float distPivot = vecMagnitude(negPos);
    unitVector(negPos);
    float radAng = DEGTORAD(angle);
    float newPos[] = { 0,0,0 };
    float newDir[] = { 0,0,0 };
    float newUp[] = { 0,0,0 };
    rotatePointAroundAxis(negPos, a, radAng, newPos);
    rotatePointAroundAxis(d, a, radAng, newDir);
    rotatePointAroundAxis(u, a, radAng, newUp);
    newPos[2] * distPivot;
    dir.set(newDir[0], newDir[1], newDir[2]);
    up.set(newUp[0], newUp[1], newUp[2]);
    setCamDef();
}

void Camera::rotate(float angle, vector3f axis) {
    float ax[] = { axis.x, axis.y, axis.z };
    unitVector(ax);
    float radAng = DEGTORAD(angle);
    float d[] = { dir.x, dir.y, dir.z };
    float u[] = { up.x, up.y, up.z };
    float r[] = { 0,0,0 };
}

void Camera::setCamDef() {
    zref.x = dir.x;
    zref.y = dir.y;
    zref.z = dir.z;
    zref.normalize();
    up.normalize();
    xref = vector3f::crossProd(zref, up);
    xref.normalize();
    yref = vector3f::crossProd(xref, zref);
    yref.normalize();
}

Camera::~Camera() {};
