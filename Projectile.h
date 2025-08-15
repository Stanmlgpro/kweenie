//
// Created by stan1 on 13/08/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>
#include <cmath>

class Projectile {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float radius;
    float lifetime;
    float age = 0.0f;
    float damage;

    sf::CircleShape shape;
    sf::Sprite sprite;

    bool allied = true;
    bool active = false;

    sf::Texture* texture = nullptr;
public:
    Projectile() = default;

    Projectile(sf::Vector2f startPos, sf::Vector2f direction, float spd, float life, float size, float damage, std::string texturePath);

    void Activate(sf::Vector2f startPos, sf::Vector2f direction, float spd, float life, float size, float damage, sf::Texture* tex, bool isAllied);

    bool update(float dt);
    void setSprite(const std::string& img_path);
    void render(sf::RenderWindow* window);

    sf::Vector2f getPosition() const { return position; }
    float getRadius() const { return radius; }
    float getDamage() const { return damage; }
    bool IsAllied() const { return allied; }
    void deactivate() { active = false; }
    bool isActive() const { return active; }

    void setIfAllied(bool allied) { this->allied = allied; }

    virtual ~Projectile() = default;
};


#endif //PROJECTILE_H
