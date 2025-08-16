//
// Created by stan1 on 16/08/2025.
//

#include "Wave.h"

#include "Enemy.h"
#include "Game.h"

Wave::Wave(int difficulty, float length, bool bossfight) : difficulty(difficulty), length(length), bossfight(bossfight) {
    spawnTime = calculateSpawnTime();
    spawnTime_timer = spawnTime;
}

void Wave::setGame(Game* game) {
    this->game = game;
}

float Wave::calculateSpawnTime() const {
    float extra_factor = 3000;
    float baseTime = 2.5f * extra_factor;       // base spawn interval in seconds
    float minTime  = 0.3  * extra_factor;       // never faster than this
    float difficultyFactor = 0.15f * extra_factor; // higher = faster spawn at higher difficulty
    float lengthFactor = 0.08f * extra_factor;  // slows down for bigger waves

    // Exponential decay with difficulty
    float difficultyTime = baseTime * std::exp(-difficulty * difficultyFactor);

    // Slightly increase for large waves
    float lengthTime = length * lengthFactor;

    float spawnTime = difficultyTime + lengthTime;

    return std::max(minTime, spawnTime);
}

void Wave::update(float dt) {
    spawnTime_timer -= dt;
    if (spawnTime_timer <= 0.f && length > 0) {
        spawn();
        length--;
        spawnTime_timer = spawnTime; // reset
    }
}

float Wave::getLength() {
    return length;
}

sf::Vector2f Wave::chooseSpawnPointAroundPlayer(sf::Vector2f playerPos, float radius) {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * M_PI;
    float x = playerPos.x + radius * cos(angle);
    float y = playerPos.y + radius * sin(angle);
    return {x, y};
}

int Wave::biasedIndex(int maxIndex, float bias) {
    // random in [0,1)
    float r = static_cast<float>(rand()) / RAND_MAX;

    // power bias: higher bias = more weight on small numbers
    r = pow(r, bias);

    return static_cast<int>(r * (maxIndex + 1));
}

std::string Wave::chooseEnemy() {
    // Chance for boss if bossfight == true
    if (bossfight && !bosses.empty()) {
        float chance = 0.1f; // 10% chance per spawn
        float r = static_cast<float>(rand()) / RAND_MAX;
        if (r < chance) {
            return bosses[rand() % bosses.size()];
        }
    }

    // Normal enemy from enemies vector
    int index = biasedIndex(enemies.size() - 1, 2.0f); // bias = 2
    return enemies[index];
}

void Wave::spawn() {
    sf::Vector2f spawnPos = chooseSpawnPointAroundPlayer(game->getPlayer()->getPosition(), 700.f);
    std::string enemyType = chooseEnemy();

    Entity* entity;
    if (enemyType == "zombie") {
        entity = new Zombie();
    }
    if (enemyType == "tombstone") {
        entity = new Tombstone();
    }
    entity->setPosition(spawnPos);
    game->addEntity(entity);
}
