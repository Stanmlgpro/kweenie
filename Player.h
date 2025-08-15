//
// Created by stan1 on 13/08/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Projectile.h"
#include <cmath>

class Player : public Entity {
public:
    Player();

    void update(float dt) override;

    virtual Projectile* Q(sf::Vector2f mousePos) = 0;
    virtual Projectile* W(sf::Vector2f mousePos) = 0;
    virtual Projectile* E(sf::Vector2f mousePos) = 0;
    virtual Projectile* R(sf::Vector2f mousePos) = 0;

    float getQ_CD() const;
    float getW_CD() const;
    float getE_CD() const;
    float getR_CD() const;
    float getQ_time() const;
    float getW_time() const;
    float getE_time() const;
    float getR_time() const;

    void setQ_CD(float CD);
    void setW_CD(float CD);
    void setE_CD(float CD);
    void setR_CD(float CD);
    void setQ_time(float time);
    void setW_time(float time);
    void setE_time(float time);
    void setR_time(float time);

    Projectile* died() override;

private:
    float Q_CD = 0;
    float Q_time = 0;
    float W_CD = 0;
    float W_time = 0;
    float E_CD = 0;
    float E_time = 0;
    float R_CD = 0;
    float R_time = 0;
};

class Archer : public Player {
public:
    Archer();

    Projectile* Q(sf::Vector2f mousePos) override;
    Projectile* W(sf::Vector2f mousePos) override;
    Projectile* E(sf::Vector2f mousePos) override;
    Projectile* R(sf::Vector2f mousePos) override;
};

#endif //PLAYER_H
