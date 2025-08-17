#include "Game.h"

#include <variant>

#include "Ally.h"
#include "Enemy.h"

Game::Game() {
    arrowTexture.loadFromFile("../Resources/Arrow.png");
    bigArrowTexture.loadFromFile("../Resources/Big_arrow.png");
    fireTexture.loadFromFile("../Resources/Fire.png");

    projectilePool.resize(200);
    areaEffectPool.resize(200);

    Archer* archer = new Archer();
    this->player = archer;
    addEntity(player);
    setDifficulty(1);
    start();
}

void Game::start() {
    time_between_waves = timeBetweenWaves();
    time_between_waves_timer = time_between_waves;
    setWave(new Wave(difficulty, std::pow(difficulty*2,2), false));
}

float Game::timeBetweenWaves() {
    float extra_factor = 100;
    float baseTime = 15.f * extra_factor;     // seconds at easy difficulty
    float minTime  = 3.f * extra_factor;      // never shorter than this
    float decay    = 0.85f * extra_factor;    // smaller = faster decay with difficulty

    float time = baseTime * pow(decay, getDifficulty() - 1);

    return std::max(minTime, time);
}

void Game::update() {
    if (!waveFinished) {
        wave->setGame(this);
        wave->update(dt);

        // Check if wave is finished AND no enemies remain
        bool enemiesRemain = false;
        for (Entity* entity : entities) {
            if (!entity->IsAllied()) {
                enemiesRemain = true;
                break;
            }
        }

        if (wave->getLength() <= 0 && !enemiesRemain) {
            waveFinished = true;
            time_between_waves_timer = time_between_waves; // start countdown after wave ends
        }
    } else {
        time_between_waves_timer -= dt;
        std::cout << "counting down: " << time_between_waves_timer << std::endl;

        if (time_between_waves_timer <= 0) {
            // Only spawn new wave if no enemies exist
            bool enemiesRemain = false;
            for (Entity* entity : entities) {
                if (!entity->IsAllied()) {
                    enemiesRemain = true;
                    break;
                }
            }

            if (!enemiesRemain) {
                setWave(new Wave(difficulty*sqrt(game_length), std::pow(game_length,2), false));
                game_length++;
                waveFinished = false; // wave started
            }
        }
    }

    wave->setGame(this);
    wave->update(dt);

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
            projectilePool[i].hit();
            projectilePool[i].deactivate();
        } else {
            ++i;
        }
    }
    for (size_t i = 0; i < areaEffectPool.size(); ) {
        areaEffectPool[i].setGame(this);
        bool expired = areaEffectPool[i].update(dt);
        if (!areaEffectPool[i].isActive()) {
            ++i;
            continue;
        }
        if (expired) {
            areaEffectPool[i].deactivate();
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
void Game::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
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
std::vector<AreaEffect>& Game::getAreaEffectPool() {
    return areaEffectPool;
}

Player* Game::getPlayer() {
    return player;
}
float Game::getGold() {
    return gold;
}
float Game::getDifficulty() {
    return difficulty;
}

Projectile* Game::getInactiveProjectile() {
    for (auto& p : projectilePool) {
        if (!p.isActive()) return &p; // reuse
    }
    return nullptr; // all in use
}
AreaEffect* Game::getInactiveAreaEffect() {
    for (auto& a : areaEffectPool) {
        if (!a.isActive()) return &a; // reuse
    }
    return nullptr; // all in use
}

void Game::addProjectiles(const std::vector<ProjectileData>& projectiles) {
    for (const auto& data : projectiles) {
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
            data.isAllied,
            data.onHit
        );
    }
}

void Game::addAreaEffects(const std::vector<AreaEffectData>& areaEffects) {
    for (const auto& data : areaEffects) {
        AreaEffect* a = getInactiveAreaEffect();
        if (!a) {
            std::cerr << "No inactive areaEffect available! Increase pool size.\n";
            continue;
        }
        a->Activate(
            data.Pos,
            data.life,
            data.size,
            data.tickInterval,
            data.tex,
            data.isAllied,
            data.onHit
        );
    }
}

void Game::addEntity(Entity* entity) {
    if (entity) this->entities.push_back(entity);
}
void Game::setWave(Wave* wave) {
    if (wave) this->wave = wave;
}
void Game::addGold(float gold) {
    this->gold += gold;
}

std::vector<Entity*> Game::getEntitiesInRange(sf::Vector2f pos, float radius, bool onlyAllies, bool onlyEnemies) {
    std::vector<Entity*> result;

    for (auto& entity : getEntities()) {
        float dx = entity->getPosition().x - pos.x;
        float dy = entity->getPosition().y - pos.y;
        float distSq = dx*dx + dy*dy;
        std::cout << "Effect pos: " << pos.x << "," << pos.y
          << " | Entity pos: " << entity->getPosition().x << "," << entity->getPosition().y
          << " | dx*dx+dy*dy: " << (entity->getPosition().x - pos.x)*(entity->getPosition().x - pos.x) +
                                    (entity->getPosition().y - pos.y)*(entity->getPosition().y - pos.y)
          << std::endl;
        float combinedRadius = radius + entity->getHitboxRadius();
        if (distSq <= combinedRadius*combinedRadius) result.push_back(entity);
    }
    return result;
}

Game::~Game() {
    for (Entity* entity : entities) {
        delete entity;
    }
}
