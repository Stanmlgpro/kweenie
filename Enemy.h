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
    std::vector<ProjectileData> died() override = 0;

private:
    Entity* target = nullptr;
};

class Zombie : public Enemy {
public:
    Zombie();

    void update(float dt) override;
    std::vector<ProjectileData> died() override;
};

class Tombstone : public Enemy {
public:
    Tombstone();

    void update(float dt) override;
    std::vector<ProjectileData> died() override;
};
#endif //ENEMY_H
