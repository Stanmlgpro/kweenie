//
// Created by stan1 on 15/08/2025.
//

#include "Ally.h"
#include "Projectile.h"
#include "Game.h"

Ally::Ally() {
    setIfAllied(true);
}

void Ally::update(float dt) {
    float closestDistance = INFINITY;

    Game* game = getGame();
    if (game) {
        for (Entity* entity : game->getEntities()) {
            if (!entity || entity->IsAllied()) continue;

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
Entity* Ally::getTarget() const {
    return target;
}

Peasant::Peasant() {
    setSprite("../Resources/Peasant.png");
    setPosition({400.f, 100.f});
    setAcceleration(0.6);
    setVelocity(0.6);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(10);
    setHp(65);
    setCD(0.7);
}

void Peasant::update(float dt) {
    Ally::update(dt);
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
        meleeHit->setIfAllied(true);

        getGame()->addProjectile(meleeHit);
    }
}

Projectile* Peasant::died() {
    return nullptr;
}

Barn::Barn() {
    setSprite("../Resources/Barn.jpg");
    setPosition({100.f, 50.f});
    setAcceleration(0);
    setVelocity(0);
    setTargetPosition({0.f, 0.f});
    setHitboxRadius(15);
    setHp(100);
    setCD(3.5);
}

void Barn::update(float dt) {
    Ally::update(dt);

    if (getCD_timer() <= 0) {
        setCD_timer(getCD());

        auto zombie = new Peasant();
        zombie->setPosition(getPosition());
        getGame()->addEntity(zombie);
    }
}

Projectile* Barn::died() {
    return nullptr;
}
