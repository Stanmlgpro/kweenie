//
// Created by stan1 on 13/08/2025.
//

#include "Player.h"
#include "Game.h"

Player::Player() {
    setIfAllied(true);
}

void Player::update(float dt) {
    float dt_ = dt / 180;
    Q_time -= dt_;
    W_time -= dt_;
    E_time -= dt_;
    R_time -= dt_;
    if (Q_time < 0) Q_time = 0;
    if (W_time < 0) W_time = 0;
    if (E_time < 0) E_time = 0;
    if (R_time < 0) R_time = 0;

    Entity::update(dt);
}

float Player::getQ_CD() const {
    return Q_CD;
}
float Player::getW_CD() const {
    return W_CD;
}
float Player::getE_CD() const {
    return E_CD;
}
float Player::getR_CD() const {
    return R_CD;
}
float Player::getQ_time() const {
    return Q_time;
}
float Player::getW_time() const {
    return W_time;
}
float Player::getE_time() const {
    return E_time;
}
float Player::getR_time() const {
    return R_time;
}

void Player::setQ_CD(float CD) {
    this->Q_CD = CD;
}
void Player::setW_CD(float CD) {
    this->W_CD = CD;
}
void Player::setE_CD(float CD) {
    this->E_CD = CD;
}
void Player::setR_CD(float CD) {
    this->R_CD = CD;
}
void Player::setQ_time(float time) {
    this->Q_time = time;
}
void Player::setW_time(float time) {
    this->W_time = time;
}
void Player::setE_time(float time) {
    this->E_time = time;
}
void Player::setR_time(float time) {
    this->R_time = time;
}

Projectile* Player::died() {
    getGame()->getGameRenderer()->getWindow()->close();
    return nullptr;
}

Archer::Archer() {
    setSprite("../Resources/Archer.png");
    setPosition({500.f, 500.f});
    setAcceleration(1);
    setVelocity(1);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(10);
    setHp(100);
    setQ_CD(0.5);
    setQ_time(0);
    setW_CD(3);
    setW_time(0);
    setE_CD(6);
    setE_time(0);
    setR_CD(30);
    setR_time(0);
}

Projectile* Archer::Q(sf::Vector2f mousePos) {
    if (getQ_time() <= 0) {
        setQ_time(getQ_CD());
        Projectile* projectile = new Projectile(getPosition(),mousePos - getPosition(), 4, 200, 20, 10, "../Resources/Arrow.png");
        setTargetPosition(getPosition());
        return projectile;
    }
    return nullptr;
}
Projectile* Archer::W(sf::Vector2f mousePos) {
    if (getW_time() <= 0) {
        setW_time(getW_CD());
        Projectile* projectile = new Projectile(getPosition(),mousePos - getPosition(), 2, 200, 20, 10, "../Resources/Arrow.png");
        setTargetPosition(getPosition());
        return projectile;
    }
    return nullptr;
}
Projectile* Archer::E(sf::Vector2f mousePos) {
    if (getE_time() == 0) {
        setE_time(getE_CD());
        sf::Vector2f direction = mousePos - getPosition();

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length == 0.f) {
            return nullptr;
        }
        direction /= length;
        setPosition(getPosition() + direction * 200.f);
        setTargetPosition(getPosition());
    }
    return nullptr;
}
Projectile* Archer::R(sf::Vector2f mousePos) {
    if (getR_time() <= 0) {
        setR_time(getR_CD());
        Projectile* projectile = new Projectile(getPosition(),mousePos - getPosition(), 5, 500, 200, 50, "../Resources/Big_arrow.jpg");
        setTargetPosition(getPosition());
        return projectile;
    }
    return nullptr;
}
