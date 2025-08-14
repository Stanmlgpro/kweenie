//
// Created by stan1 on 13/08/2025.
//

#include "Enemy.h"
#include "Game.h"

Enemy::Enemy() {
    setIfAllied(false);
}

void Enemy::update(float dt) {
    Entity::update(dt);
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
    setTargetPosition(getGame()->getPlayer()->getPosition());

    // Calculate distance to player
    sf::Vector2f toPlayer = getGame()->getPlayer()->getPosition() - getPosition();
    float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    float meleeRange = 75.f; // adjust to your zombie reach

    // Handle melee attack
    if (getCD_timer() <= 0) {
        setCD_timer(getCD()); // reset cooldown

        // Create a "melee projectile" at zombie's position
        auto meleeHit = new Projectile(
            getPosition(),      // spawn on zombie
            {1.f, 0.f},         // direction doesn’t matter
            0.f,                // no movement
            0.2f,               // very short lifetime (0.2s)
            75.f,               // radius
            20.f                // damage
        );
        meleeHit->setIfAllied(false);

        getGame()->addProjectile(meleeHit);
    }

    Enemy::update(dt);
}
