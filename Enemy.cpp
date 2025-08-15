//
// Created by stan1 on 13/08/2025.
//

#include "Enemy.h"
#include "Game.h"

Enemy::Enemy() {
    setIfAllied(false);
}

void Enemy::update(float dt) {
    float closestDistance = INFINITY;

    Game* game = getGame();
    if (game) {
        // First check player as potential target
        Entity* player = game->getPlayer();
        if (player && player->IsAllied()) {
            sf::Vector2f dist = player->getPosition() - getPosition();
            closestDistance = std::hypot(dist.x, dist.y);
            target = player;
        }

        // Check other entities
        for (Entity* entity : game->getEntities()) {
            if (!entity || !entity->IsAllied() || entity == player) continue;

            sf::Vector2f dist = entity->getPosition() - getPosition();
            float currentDistance = std::hypot(dist.x, dist.y);

            if (currentDistance < closestDistance) {
                closestDistance = currentDistance;
                target = entity;
            }
        }
    }

    Entity::update(dt);
}
Entity* Enemy::getTarget() const {
    return target;
}

Zombie::Zombie() {
    setSprite("../Resources/Zombie.png");
    setPosition({700.f, 700.f});
    setAcceleration(0.6);
    setVelocity(0.6);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(10);
    setHp(40);
    setCD(1);
}

void Zombie::update(float dt) {
    Enemy::update(dt);
    if (!getTarget()) return;
    setTargetPosition(getTarget()->getPosition());

    float meleeRange = 75.f; // adjust to your zombie reach
    // Handle melee attack
    sf::Vector2f dist = getTarget()->getPosition() - getPosition();
    float dis = std::hypot(dist.x, dist.y);
    if (dis <= meleeRange && getCD_timer() <= 0) {
        setCD_timer(getCD()); // reset cooldown

        // Create a "melee projectile" at zombie's position
        auto meleeHit = new Projectile(
            getPosition(),
            {1.f, 0.f},
            0.f,
            0.2f,
            75.f,
            20.f,
            "../Resources/Arrow.png"
        );
        meleeHit->setIfAllied(false);

        getGame()->addProjectile(meleeHit);
    }
}

Projectile* Zombie::died() {
    getGame()->addGold(1);
    return nullptr;
}

Tombstone::Tombstone() {
    setSprite("../Resources/Tombstone.png");
    setPosition({300.f, 300.f});
    setAcceleration(0);
    setVelocity(0);
    setTargetPosition({0.f, 0.f});
    setHitboxRadius(15);
    setHp(100);
    setCD(2);
}

void Tombstone::update(float dt) {
    Enemy::update(dt);

    if (getCD_timer() <= 0) {
        setCD_timer(getCD());

        auto zombie = new Zombie();
        zombie->setPosition(getPosition());
        getGame()->addEntity(zombie);
    }
}

Projectile* Tombstone::died() {
    getGame()->addGold(5);
    return nullptr;
}
