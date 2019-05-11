/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#pragma once

#include "Bezier.hpp"

Bezier::Bezier(int _degree, Point ** _ctrlPoints) {
    degree = _degree;
    coefficients = new float[degree + 1];
    ctrlPoints = new Point *[degree + 1];
    for (int i = 0; i <= degree; i++) {
        ctrlPoints[i] = new Point(_ctrlPoints[i]);
    }
}

Bezier::~Bezier(){
    delete ctrlPoints;
}

void Bezier::calculateCoefficients() {
    for (int i = 0; i <= degree; i++) {
        coefficients[i] = combination(degree, i);
    }
}

int Bezier::factorial(int n) {
    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

float Bezier::combination(int n, int i) {
    float nf = (float)factorial(n);
    return nf / (factorial(i) * factorial(n - i));
}


Point * Bezier::evaluateBezier(float t) {
    calculateCoefficients();
    Point * p = new Point(0, 0, 0);
    for (int i = 0; i <= degree; i++) {
        float c = pow(1 - t, degree - i) * pow(t, i);
        p = p->add(ctrlPoints[i]->multiplyByScalar(coefficients[i] * c));
    }
    return p;
}

void Bezier::draw() {
    for (int i = 0; i <= degree; i++) {
        glPushMatrix(); {
            glTranslatef(ctrlPoints[i]->x, ctrlPoints[i]->y, ctrlPoints[i]->z);
            glColor3f(1, 0, 0);
            glutSolidSphere(0.15, 10, 10);
        } glPopMatrix();
    }
}
