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
}

Character::Character(float x, float z)
{
    p = new Point(x, 0, z);
}

Character::~Character()
{
}

void Character::move(float _x, float _z) {
    p->x += _x;
    p->z += _z;
}

void Character::draw() {
    p->draw();
}
