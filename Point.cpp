/*
 * A01172912 | Andr�s Bustamante D�az
 * A01332653 | Miguel Angel Azuara Olivares
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 * A01362620 | Santiago Beddoe Levy
 */

#include "Point.hpp"

Point::Point(Point * other) {
    x = other->x;
    y = other->y;
    z = other->z;
}

Point::Point(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

Point::~Point(){}

Point * Point::multiplyByScalar(float s) {
    Point * p = new Point(this);
    p->x *= s;
    p->y *= s;
    p->z *= s;
    return p;
}

Point * Point::add(Point * other) {
    Point * p = new Point(this);
    p->x += other->x;
    p->y += other->y;
    p->z += other->z;
    return p;
}
