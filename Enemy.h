#ifndef ENEMY_H
#define ENEMY_H

#include "PLAYER.h"


class Enemy : public PLAYER {
public:
    Enemy(sf::Texture& image);
    Enemy& operator=(const PLAYER& other);

    void update(float time, MapCollider& mapCollider) override; // Перегружаем метод
    void display(std::ostream& os) const override; // Переопределяем метод

};


#endif // ENEMY_H