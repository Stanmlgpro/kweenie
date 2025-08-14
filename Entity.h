//
// Created by stan1 on 12/08/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

class Game;
class Entity {
private:
    sf::Vector2f targetPosition;
    sf::Vector2f position;

    float velocity = 0;
    float acceleration = 0;
    float hp;
    float hitboxRadius;

    sf::Texture texture;
    sf::Sprite sprite;

    bool flipped = false;
    bool dead = false;
    bool allied = true;
    float CD = 0;
    float CD_timer = 0;

    Game* game;
public:
    Entity() = default;

    void render(sf::RenderWindow* window);
    void setSprite(const std::string& img_path);
    void flip();

    float getVelocity();
    float getAcceleration();
    sf::Vector2f getPosition();
    sf::Vector2f getTargetPosition();
    float getHitboxRadius();
    float getHp();
    bool isFlipped();
    bool isDead();
    bool IsAllied() const { return allied; }
    Game* getGame() const { return game; }
    float getCD() const { return CD; }
    float getCD_timer() const { return CD_timer; }

    void setVelocity(float velocity);
    void setAcceleration(float acceleration);
    void setPosition(sf::Vector2f position);
    void setTargetPosition(sf::Vector2f targetPosition);
    void setHitboxRadius(float hitboxRadius);
    void setHp(float hp);
    void setDeath(bool death) { this->dead = death; }
    void setFlipped(bool flipped);
    void setIfAllied(bool allied) { this->allied = allied; }
    void setGame(Game* game) {this->game = game; }
    void setCD(float CD) {this->CD = CD; }
    void setCD_timer(float CD_timer) {this->CD_timer = CD_timer; }

    virtual void update(float dt);

    virtual ~Entity() = default;
};

#endif //ENTITY_H
