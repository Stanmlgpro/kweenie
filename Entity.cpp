//
// Created by stan1 on 12/08/2025.
//

#include "Entity.h"
#include "Game.h"

void Entity::update(float dt) {
    float dt_ = dt / 180;
    CD_timer -= dt_;
    if (CD_timer < 0) CD_timer = 0;
    sf::Vector2f direction = targetPosition - position;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance == 0.f) return;

    sf::Vector2f directionNormalized = direction / distance;

    sf::Vector2f movement = directionNormalized * velocity * dt;

    if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
        position = targetPosition;
    } else {
        position += movement;
    }

    if (direction.x < 0 && !flipped) {
        flip();
        flipped = true;
    } else if (direction.x > 0 && flipped) {
        flip();
        flipped = false;
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
