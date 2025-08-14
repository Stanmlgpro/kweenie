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
    Entity* getTarget() const;

private:
    Entity* target = nullptr;
};

class Zombie : public Enemy {
public:
    Zombie();

    void update(float dt) override;
};

#endif //ENEMY_H
