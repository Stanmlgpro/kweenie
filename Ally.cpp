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
    Entity::update(dt);
}

Peasant::Peasant() {
    setSprite("../Resources/Peasant.jpg");
    setPosition({700.f, 700.f});
    setAcceleration(0.6);
    setVelocity(0.6);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(10);
    setHp(40);
    setCD(1);
}

void Peasant::update(float dt) {
    float dis = INFINITY;
    Entity* target_entity = nullptr;
    for (Entity* entity : getGame()->getEntities()) {
        sf::Vector2f distance = getGame()->getPlayer()->getPosition() - getPosition();
        float check = std::sqrt(distance.x * distance.x + distance.y * distance.y);
        if (check < dis) {
            dis = check;
            target_entity = entity;
        }
    }
    setTargetPosition(target_entity->getPosition());

    float meleeRange = 75.f; // adjust to your zombie reach
    // Handle melee attack
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

    Ally::update(dt);
}
