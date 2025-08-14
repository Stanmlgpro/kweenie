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
class Game {
public:
    Game();

    void update();

    GameRenderer* getGameRenderer();
    GUI* getGUI();

    void setGameRenderer(GameRenderer* gameRenderer);
    void setGUI(GUI* gui);
    void addProjectile(Projectile* projectile);
    void addEntity(Entity* entity);

    std::vector<Entity*> getEntities();
    std::vector<Projectile*> getProjectiles();
    Player* getPlayer();

    ~Game();

private:
    GameRenderer* gameRenderer = nullptr;
    GUI* gui = nullptr;
    Player* player = nullptr;
    std::vector<Entity*> entities;
    std::vector<Projectile*> projectiles;
    float dt = 2;
};



#endif //GAME_H
