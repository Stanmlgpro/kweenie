//
// Created by stan1 on 12/08/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

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

    void setVelocity(float velocity);
    void setAcceleration(float acceleration);
    void setPosition(sf::Vector2f position);
    void setTargetPosition(sf::Vector2f targetPosition);
    void setHitboxRadius(float hitboxRadius);
    void setHp(float hp);
    void setDeath(bool death) { this->dead = death; }
    void setFlipped(bool flipped);
    void setIfAllied(bool allied) { this->allied = allied; }

    virtual void update(float dt);

    virtual ~Entity() = default;
};

#endif //ENTITY_H
