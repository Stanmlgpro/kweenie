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

    void update();

    GameRenderer* getGameRenderer();
    GUI* getGUI();

    void setGameRenderer(GameRenderer* gameRenderer);
    void setGUI(GUI* gui);
    void addProjectiles(const std::vector<ProjectileData>& projectiles);
    void addEntity(Entity* entity);
    void addGold(float gold);

    std::vector<Entity*> getEntities();
    std::vector<Projectile*> getProjectiles();
    Player* getPlayer();
    float getGold();

    Projectile* getInactiveProjectile();

    ~Game();

private:
    GameRenderer* gameRenderer = nullptr;
    GUI* gui = nullptr;
    Player* player = nullptr;
    std::vector<Entity*> entities;
    std::vector<Projectile*> projectiles;
    float dt = 2;
    float gold = 0;
};



#endif //GAME_H
