//
// Created by stan1 on 12/08/2025.
//

#include "Entity.h"

void Entity::update(float dt) {
    // Compute direction vector
    sf::Vector2f dir = targetPosition - position;

    // Compute distance to target
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (distance > 0.0f) {
        // Normalize direction
        dir /= distance;

        // Update velocity with acceleration
        velocity += acceleration * dt;

        // Move position
        position += dir * velocity * dt;

        // Update sprite position
        sprite.setPosition(position);

        // Flip sprite based on horizontal direction
        if (dir.x < 0 && !flipped) {
            sprite.setScale(-1.f, 1.f);
            flipped = true;
        } else if (dir.x > 0 && flipped) {
            sprite.setScale(1.f, 1.f);
            flipped = false;
        }
    } else {
        // Reached target, stop moving
        velocity = 0;
    }
}

void Entity::render(sf::RenderWindow* window) {
    sprite.setPosition(position.x, position.y);
    window->draw(sprite);
}

void Entity::setSprite(const std::string& img_path) {
    if (!this->texture.loadFromFile(img_path)) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->sprite.setTexture(this->texture);
    sf::Vector2u size = this->texture.getSize();
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    float scaleX = 100.0f / size.x;
    float scaleY = 100.0f / size.y;
    this->sprite.setScale(scaleX, scaleY);
}

void Entity::flip() {
    sprite.setPosition(position.x, position.y);
    sf::Vector2u size = this->texture.getSize();
    float scaleX = 100.0f / size.x;
    float scaleY = 100.0f / size.y;
    if (flipped) {
        this->sprite.setScale(scaleX, scaleY);
        return;
    }
    this->sprite.setScale(-scaleX, scaleY);
}

float Entity::getAcceleration() {
    return acceleration;
}
float Entity::getVelocity() {
    return velocity;
}
sf::Vector2f Entity::getPosition() {
    return position;
}
sf::Vector2f Entity::getTargetPosition() {
    return targetPosition;
}
float Entity::getHitboxRadius() {
    return hitboxRadius;
}
float Entity::getHp() {
    return hp;
}
bool Entity::isFlipped() {
    return flipped;
}
bool Entity::isDead() {
    return dead;
}

void Entity::setAcceleration(float acceleration) {
    this->acceleration = acceleration;
}
void Entity::setVelocity(float velocity) {
    this->velocity = velocity;
}
void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
}
void Entity::setTargetPosition(sf::Vector2f targetPosition) {
    this->targetPosition = targetPosition;
}
void Entity::setHitboxRadius(float hitboxRadius) {
    this->hitboxRadius = hitboxRadius;
}
void Entity::setHp(float hp) {
    this->hp = hp;
    if (this->hp <= 0) this->dead = true;
}
void Entity::setFlipped(bool flipped) {
    this->flipped = flipped;
}
