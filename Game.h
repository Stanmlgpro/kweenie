#ifndef GAME_H
#define GAME_H
#include <thread>

#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameRenderer.h"
#include "GUI.h"
#include "uiButton.h"
#include "Player.h"
#include "Projectile.h"
#include <cmath>
#include "Wave.h"

class Entity;
class Player;
class GameRenderer;
class GUI;

struct ProjectileData {
    sf::Vector2f startPos;
    sf::Vector2f direction;
    float speed;
    float life;
    float size;
    float damage;
    sf::Texture* tex;
    bool isAllied;
};

class Game {
public:
    sf::Texture arrowTexture;
    sf::Texture bigArrowTexture;

    std::vector<Projectile> projectilePool;

    Game();

    void start();

    void update();

    float timeBetweenWaves();
    GameRenderer* getGameRenderer();
    GUI* getGUI();

    void setGameRenderer(GameRenderer* gameRenderer);
    void setGUI(GUI* gui);
    void setDifficulty(int difficulty);
    void addProjectiles(const std::vector<ProjectileData>& projectiles);
    void addEntity(Entity* entity);
    void setWave(Wave* wave);
    void addGold(float gold);

    std::vector<Entity*> getEntities();
    std::vector<Projectile>& getProjectilePool();
    Player* getPlayer();
    float getGold();
    float getDifficulty();

    Projectile* getInactiveProjectile();

    ~Game();

private:
    GameRenderer* gameRenderer = nullptr;
    GUI* gui = nullptr;
    Player* player = nullptr;
    std::vector<Entity*> entities;
    Wave* wave;
    float dt = 2;
    float gold = 0;
    float time_between_waves;
    float time_between_waves_timer;
    int difficulty;
    int game_length = 1;
    bool waveFinished = false;
};



#endif //GAME_H
