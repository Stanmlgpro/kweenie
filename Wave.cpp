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
    float extra_factor = 300;
    float baseTime = 2.5f * extra_factor;             // base spawn interval
    float difficultyFactor = 0.5f;    // higher difficulty → faster spawn

    float spawnTime = baseTime / (1.0f + difficulty * difficultyFactor); // faster with difficulty
    spawnTime += length;                                   // slightly slower for more enemies

    std::cout << spawnTime << std::endl;
    return spawnTime;
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

int Wave::biasedIndex(int maxIndex, float difficulty) {
    float r = static_cast<float>(rand()) / RAND_MAX;

    // Bias formula:
    // At difficulty 0 → pow(r, 2.0) → favors low indices strongly
    // At higher difficulty → pow(r, 0.5..1) → more uniform, allows stronger enemies
    float bias = std::max(0.5f, 2.0f - difficulty * 0.2f);

    r = pow(r, bias); // lower bias favors stronger enemies less at start

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
    int index = biasedIndex(enemies.size() - 1, difficulty);
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
