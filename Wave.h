//
// Created by stan1 on 16/08/2025.
//

#ifndef WAVE_H
#define WAVE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game;
class Wave {
public:
    Wave(int difficulty, float length, bool bossfight);

    sf::Vector2f chooseSpawnPointAroundPlayer(sf::Vector2f playerPos, float radius);
    int biasedIndex(int maxIndex, float bias = 2.0f);
    std::string chooseEnemy();
    void update(float dt);
    void spawn();
    float getLength();

    void setGame(Game* game);

    float calculateSpawnTime() const;

private:
    std::vector<std::string> enemies = {"zombie", "skeleton", "tombstone"};
    std::vector<std::string> bosses = {"zombieboss"};
    int difficulty = 0;
    float length;
    float spawnTime;
    float spawnTime_timer;

    bool bossfight = false;

    Game* game;
};



#endif //WAVE_H
