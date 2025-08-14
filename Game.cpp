#include "Game.h"

#include "Enemy.h"

Game::Game() {
    Archer* archer = new Archer();
    this->player = archer;
    Zombie* zombie = new Zombie();
    this->entities = {player, zombie};
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
                if (entity == player) std::cout << "player hit" << std::endl;
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
            if (e == player) return false;
            if (e->isDead()) {
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

void Game::addProjectile(Projectile* projectile) {
    if (projectile) {
        this->projectiles.push_back(projectile);
        std::cout << "projectile added" << std::endl;
    }
}

Game::~Game() {
    for (Entity* entity : entities) {
        delete entity;
    }
}
