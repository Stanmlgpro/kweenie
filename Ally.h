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

private:
    Entity* target = nullptr;
};

class Peasant : public Ally {
public:
    Peasant();

    void update(float dt) override;
};

#endif //ALLY_H
