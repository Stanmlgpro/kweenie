//
// Created by stan1 on 15/08/2025.
//

#ifndef ALLY_H
#define ALLY_H
#include "Entity.h"


class Ally : public Entity {
public:
    Ally();

    void update(float dt) override;
    Entity* getTarget() const;
    Projectile* died() override = 0;

private:
    Entity* target = nullptr;
};

class Peasant : public Ally {
public:
    Peasant();

    void update(float dt) override;
    Projectile* died() override;
};

class Barn : public Ally {
public:
    Barn();

    void update(float dt) override;
    Projectile* died() override;
};
#endif //ALLY_H
