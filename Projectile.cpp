//
// Created by stan1 on 13/08/2025.
//

#include "Projectile.h"

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f direction, float spd, float life, float size, float damage) : position(startPos), speed(spd), lifetime(life), radius(size), damage(damage) {
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    velocity = direction * speed;

    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
}

void Projectile::render(sf::RenderWindow* window) {
    window->draw(shape);
}

bool Projectile::update(float dt) {
    position += velocity * dt;
    age += dt;
    shape.setPosition(position);

    return age >= lifetime;
}
