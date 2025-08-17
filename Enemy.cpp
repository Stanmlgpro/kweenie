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
    setPosition({700.f, 700.f});
    setAcceleration(0.6);
    setVelocity(0.6);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(50);
    setHp(40);
    setCD(1);
    setSprite("../Resources/Zombie.png");
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
        getGame()->addProjectiles ( {
            {
            getPosition(),
            {1.f, 0.f},
            0.f,
            0.2f,
            75.f,
            20.f,
            &getGame()->arrowTexture,
            false,
            nullptr
            }
        });
    }
}

std::vector<ProjectileData> Zombie::died() {
    getGame()->addGold(1);
    return {};
}

Skeleton::Skeleton() {
    setPosition({700.f, 700.f});
    setAcceleration(1.1);
    setVelocity(1.1);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(40);
    setHp(60);
    setCD(1.2);
    setSprite("../Resources/Skeleton.png");
}

void Skeleton::update(float dt) {
    Enemy::update(dt);
    if (!getTarget()) return;
    sf::Vector2f toTarget = getTargetPosition() - getPosition();
    float dist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (dist < 10.f) { // close enough to target, pick a new one
        float radius = 400;
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * M_PI;
        float x = getTarget()->getPosition().x + radius * cos(angle);
        float y = getTarget()->getPosition().y + radius * sin(angle);
        setTargetPosition({x,y});
    }

    if (getCD_timer() <= 0) {
        setCD_timer(getCD()); // reset cooldown

        getGame()->addProjectiles ( {
            {
            getPosition(),
            getTarget()->getPosition() - getPosition(),
            3.f,
            500.f,
            30.f,
            5.f,
            &getGame()->arrowTexture,
            false,
            nullptr
            }
        });
    }
}

std::vector<ProjectileData> Skeleton::died() {
    getGame()->addGold(2);
    return {};
}

Tombstone::Tombstone() {
    setPosition({300.f, 300.f});
    setAcceleration(0);
    setVelocity(0);
    setTargetPosition({0.f, 0.f});
    setHitboxRadius(120);
    setHp(100);
    setCD(2);
    setSprite("../Resources/Tombstone.png");
}

void Tombstone::update(float dt) {
    Enemy::update(dt);
    setHp(getHp() - dt/70);
    if (getCD_timer() <= 0) {
        setCD_timer(getCD());

        auto zombie = new Zombie();
        zombie->setPosition(getPosition());
        getGame()->addEntity(zombie);
    }
}

std::vector<ProjectileData> Tombstone::died() {
    getGame()->addGold(5);
    return {};
}

ZombieBoss::ZombieBoss() {
    setPosition({300.f, 300.f});
    setAcceleration(0.4);
    setVelocity(0.4);
    setTargetPosition({0.f, 0.f});
    setHitboxRadius(300);
    setHp(1000);
    setCD(2);
    setSprite("../Resources/Zombie_Boss.png");
}

void ZombieBoss::update(float dt) {
    Enemy::update(dt);
    if (!getTarget()) return;
    sf::Vector2f toTarget = getTargetPosition() - getPosition();
    float dist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (dist < 10.f) { // close enough to target, pick a new one
        float radius = 700;
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * M_PI;
        float x = getTarget()->getPosition().x + radius * cos(angle);
        float y = getTarget()->getPosition().y + radius * sin(angle);
        setTargetPosition({x,y});
    }

    if (getCD_timer() <= 0) {
        setCD_timer(getCD());

        getGame()->addProjectiles ( {
            {
            getPosition(),
            getTarget()->getPosition() - getPosition(),
            4.f,
            1000.f,
            70.f,
            20.f,
            &getGame()->zombieAttackTexture,
            false,
                [&](const sf::Vector2f& hitPos) {
                    auto zombie = new Zombie();
                    zombie->setPosition(hitPos);
                    getGame()->addEntity(zombie);
                }
            }
        });
    }
}

std::vector<ProjectileData> ZombieBoss::died() {
    getGame()->addGold(100);
}
