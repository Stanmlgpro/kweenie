//
// Created by stan1 on 13/08/2025.
//

#include "Enemy.h"

Enemy::Enemy() {
    setIfAllied(false);
}

void Enemy::update(float dt) {
    Entity::update(dt);
}

Zombie::Zombie() {
    setSprite("../Resources/Zombie.png");
    setPosition({700.f, 700.f});
    setAcceleration(1);
    setVelocity(1);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(10);
    setHp(40);
}
