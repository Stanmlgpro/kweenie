//
// Created by stan1 on 17/08/2025.
//

#ifndef AREAEFFECT_H
#define AREAEFFECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <functional>

class Entity;
class Game;
class AreaEffect {
private:
    sf::Vector2f position;
    float radius;
    float age = 0.0f;
    float life;
    float tickInterval;
    float tickTimer;

    sf::CircleShape shape;
    sf::Sprite sprite;

    bool allied = true;
    bool active = false;

    sf::Texture* texture = nullptr;
    std::function<void(Entity&)> onHit;

    Game* game;
public:
    AreaEffect() = default;

    void Activate(sf::Vector2f Pos, float life, float size, float tickInterval, sf::Texture* tex, bool isAllied, std::function<void(Entity&)> onHit);

    bool update(float dt);
    void render(sf::RenderWindow* window);
    void setGame(Game* game) { this->game = game; }

    sf::Vector2f getPosition() const { return position; }
    float getRadius() const { return radius; }
    bool IsAllied() const { return allied; }
    void deactivate() { active = false; }
    bool isActive() const { return active; }
    Game* getGame() const { return game; }

    void setIfAllied(bool allied) { this->allied = allied; }

    virtual ~AreaEffect() = default;
};



#endif //AREAEFFECT_H
