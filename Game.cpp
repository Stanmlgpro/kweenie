#include "Game.h"

#include <variant>

#include "Ally.h"
#include "Enemy.h"

Game::Game() {
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
    for (size_t i = 0; i < projectiles.size(); ) {
        bool expired = projectiles[i]->update(dt);

        for (Entity* entity : entities) {
            if (projectiles[i]->IsAllied() == entity->IsAllied()) continue;
            float dist = std::sqrt(std::pow((projectiles[i]->getPosition().x - entity->getPosition().x), 2) + std::pow((projectiles[i]->getPosition().y- entity->getPosition().y), 2));
            if (dist < projectiles[i]->getRadius() + entity->getHitboxRadius()) {
                entity->setHp(entity->getHp() - projectiles[i]->getDamage());
                expired = true;
                break;
            }
        }

        if (expired) {
            projectiles.erase(projectiles.begin() + i);
        } else {
            ++i;
        }
    }
    entities.erase(
    std::remove_if(entities.begin(), entities.end(),
        [&](Entity* e) {
            if (e->isDead()) {
                addProjectile(e->died());
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
std::vector<Projectile*> Game::getProjectiles() {
    return projectiles;
}

Player* Game::getPlayer() {
    return player;
}
float Game::getGold() {
    return gold;
}

void Game::addProjectile(Projectile* projectile) {
    if (projectile) this->projectiles.push_back(projectile);
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
