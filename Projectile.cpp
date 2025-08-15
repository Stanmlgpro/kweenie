//
// Created by stan1 on 13/08/2025.
//

#include "Projectile.h"

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f direction, float spd, float life, float size, float damage, std::string texturePath) : position(startPos), speed(spd), lifetime(life), radius(size), damage(damage) {
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    velocity = direction * speed;

    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);

    setSprite(texturePath);
}

void Projectile::setSprite(const std::string& img_path) {
    if (!this->texture.loadFromFile(img_path)) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->sprite.setTexture(this->texture);

    // Center the sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    float radius = shape.getRadius();

    sf::Vector2u texSize = this->texture.getSize();
    float scaleFactor = (radius * 2.f) / static_cast<float>(texSize.x);
    sprite.setScale(scaleFactor, scaleFactor);

    // Rotate according to velocity direction
    float angle = std::atan2(velocity.y, velocity.x) * 180.f / M_PI;
    sprite.setRotation(angle);
}

void Projectile::render(sf::RenderWindow* window) {
    sprite.setPosition(position.x, position.y);
    window->draw(sprite);
}

bool Projectile::update(float dt) {
    position += velocity * dt;
    age += dt;
    shape.setPosition(position);

    return age >= lifetime;
}
