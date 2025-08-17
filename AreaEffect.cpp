//
// Created by stan1 on 17/08/2025.
//

#include "AreaEffect.h"
#include "Game.h"

void AreaEffect::Activate(sf::Vector2f Pos, float life, float size, float tickInterval, sf::Texture* tex, bool isAllied, std::function<void(Entity&)> onHit) {
    this->position = Pos;
    this->life = life;
    this->radius = size;
    this->texture = tex;
    this->allied = isAllied;
    this->age = 0;
    this->onHit = onHit;
    this->tickInterval = tickInterval;
    this->tickTimer = tickInterval;

    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);

    active = true;
    setIfAllied(isAllied);
    sprite.setTexture(*texture);

    // Center the sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    float radius = shape.getRadius();

    sf::Vector2u texSize = this->texture->getSize();
    float scaleFactor = (radius * 2.f) / static_cast<float>(texSize.x);
    sprite.setScale(scaleFactor, scaleFactor);
}

void AreaEffect::render(sf::RenderWindow* window) {
    sprite.setPosition(position.x, position.y);
    window->draw(sprite);
}

bool AreaEffect::update(float dt) {
    if (!active) return false;
    age += dt;

    tickTimer -= dt;
    if (tickTimer <= 0.f) {
        tickTimer = tickInterval;
        for (auto entity : getGame()->getEntitiesInRange(position, radius, allied, !allied)) {
            if (onHit) onHit(*entity);
        }
    }
    shape.setPosition(position);
    return age >= life;
}
