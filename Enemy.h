//
// Created by stan1 on 13/08/2025.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"


class Enemy : public Entity {
public:
    Enemy();

    void update(float dt) override;
};

class Zombie : public Enemy {
public:
    Zombie();
};

#endif //ENEMY_H
