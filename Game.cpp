#include "Game.h"

#include <variant>

#include "Ally.h"
#include "Enemy.h"

Game::Game() {
    arrowTexture.loadFromFile("../Resources/Arrow.png");
    bigArrowTexture.loadFromFile("../Resources/Big_arrow.png");

    projectilePool.resize(200);

    Archer* archer = new Archer();
    this->player = archer;
    Tombstone* tombstone1 = new Tombstone();
    tombstone1->setPosition({300.f, 300.f});
    Tombstone* tombstone2 = new Tombstone();
    tombstone2->setPosition({900.f, 220.f});
    Barn* barn = new Barn();
    this->entities = {player, tombstone1, tombstone2, barn};
}

void Game::update() {
    for (Entity* entity : entities) {
        entity->setGame(this);
        entity->update(dt);
    }
    for (size_t i = 0; i < projectilePool.size(); ) {
        bool expired = projectilePool[i].update(dt);
        if (!projectilePool[i].isActive()) {
            ++i;
            continue;
        }

        for (Entity* entity : entities) {
            if (projectilePool[i].IsAllied() == entity->IsAllied()) continue;
            float dist = std::sqrt(std::pow((projectilePool[i].getPosition().x - entity->getPosition().x), 2) + std::pow((projectilePool[i].getPosition().y- entity->getPosition().y), 2));
            if (dist < projectilePool[i].getRadius() + entity->getHitboxRadius()) {
                entity->setHp(entity->getHp() - projectilePool[i].getDamage());
                expired = true;
                break;
            }
        }

        if (expired) {
            projectilePool[i].deactivate();
        } else {
            ++i;
        }
    }
    entities.erase(
    std::remove_if(entities.begin(), entities.end(),
        [&](Entity* e) {
            if (e->isDead()) {
                addProjectiles(e->died());
                delete e;
                return true;
            }
            return false;
        }),
    entities.end()
);
    this->getGameRenderer()->render();
}

GameRenderer* Game::getGameRenderer() {
    return gameRenderer;
}
GUI* Game::getGUI() {
    return gui;
}

void Game::setGameRenderer(GameRenderer* gameRenderer) {
    this->gameRenderer = gameRenderer;
}
void Game::setGUI(GUI* gui) {
    this->gui = gui;
}

std::vector<Entity*> Game::getEntities() {
    return entities;
}
std::vector<Projectile>& Game::getProjectilePool() {
    return projectilePool;
}

Player* Game::getPlayer() {
    return player;
}
float Game::getGold() {
    return gold;
}

Projectile* Game::getInactiveProjectile() {
    for (auto& p : projectilePool) {
        if (!p.isActive()) return &p; // reuse
    }
    return nullptr; // all in use
}

void Game::addProjectiles(const std::vector<ProjectileData>& projectilePool) {
    for (const auto& data : projectilePool) {
        Projectile* p = getInactiveProjectile();
        if (!p) {
            std::cerr << "No inactive projectile available! Increase pool size.\n";
            continue;
        }
        p->Activate(
            data.startPos,
            data.direction,
            data.speed,
            data.life,
            data.size,
            data.damage,
            data.tex,
            data.isAllied
        );
    }
}
void Game::addEntity(Entity* entity) {
    if (entity) this->entities.push_back(entity);
}
void Game::addGold(float gold) {
    this->gold += gold;
}

Game::~Game() {
    for (Entity* entity : entities) {
        delete entity;
    }
}
