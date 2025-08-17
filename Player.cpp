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

std::vector<ProjectileData> Player::died() {
    getGame()->getGameRenderer()->getWindow()->close();
    return {};
}

Archer::Archer() {
    setPosition({500.f, 500.f});
    setAcceleration(1);
    setVelocity(1);
    setTargetPosition({500.f, 500.f});
    setHitboxRadius(50);
    setHp(100);
    setQ_CD(0.25);
    setQ_time(0);
    setW_CD(3);
    setW_time(0);
    setE_CD(6);
    setE_time(0);
    setR_CD(10);
    setR_time(0);
    setSprite("../Resources/Archer.png");
}

std::vector<ProjectileData> Archer::Q(sf::Vector2f mousePos) {
    if (getQ_time() <= 0) {
        setQ_time(getQ_CD());
            return {{
                getPosition(),
                mousePos - getPosition(),
                4.f,       // speed
                200.f,     // life
                30.f,      // size
                10.f,      // damage
                &getGame()->arrowTexture,
                true,
                nullptr
            }};
    }
    return {};
}

std::vector<ProjectileData> Archer::W(sf::Vector2f mousePos) {
    if (getW_time() <= 0) {
        setW_time(getW_CD());

        std::vector<ProjectileData> projectiles;
        sf::Vector2f baseDir = mousePos - getPosition();
        float baseAngle = std::atan2(baseDir.y, baseDir.x);

        int arrowCount = 15;
        float spread = 2.f * (M_PI / 180.f); // 2° spread

        for (int i = 0; i < arrowCount; ++i) {
            float angle = baseAngle + (i - arrowCount / 2) * spread;
            sf::Vector2f dir(std::cos(angle), std::sin(angle));

            projectiles.push_back({
                getPosition(),
                dir,
                3.f,       // speed
                200.f,     // lifetime
                15.f,      // size
                5.f,      // damage
                &getGame()->arrowTexture,
                true,
                nullptr
            });
        }
        return projectiles;
    }
    return {};
}
std::vector<ProjectileData> Archer::E(sf::Vector2f mousePos) {
    if (getE_time() == 0) {
        setE_time(getE_CD());
        sf::Vector2f direction = mousePos - getPosition();

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length == 0.f) {
            return {};
        }
        direction /= length;
        setPosition(getPosition() + direction * 200.f);
    }
    return {};
}
std::vector<ProjectileData> Archer::R(sf::Vector2f mousePos) {
    if (getR_time() <= 0) {
        setR_time(getR_CD());
        setTargetPosition(getPosition());
        return {{
            getPosition(),
            mousePos - getPosition(),
            7.f,       // speed
            200.f,     // life
            50.f,      // size
            50.f,      // damage
            &getGame()->arrowTexture,
            true,
            nullptr
        }};
    }
    return {};
}
