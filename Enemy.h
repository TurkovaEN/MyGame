#ifndef ENEMY_H
#define ENEMY_H

#include "PLAYER.h"

class Enemy : public PLAYER {
public:
    Enemy(sf::Texture& image) : PLAYER(image) {
        // Установка начальных значений для врага
        dx = 0.05; // скорость врага
        dy = 0; // вертикальная скорость
    }

    void update(float time, MapCollider& mapCollider) {
        // Логика движения врага (например, движение влево и вправо)
        this->rect.left += this->dx * time; // Движение врага
        if (this->rect.left < 0 || this->rect.left > 1570) {
            dx = -dx; // Изменение направления
        }
        mapCollider.handleCollision(this->rect, this->dx, this->dy, this->onGround, 0);

        // Обновление вертикального положения
        rect.top += dy * time;
        onGround = false;
        mapCollider.handleCollision(rect, dx, dy, onGround, 1);

        // Обновление спрайта
        sprite.setPosition(rect.left, rect.top);
    }
};

#endif // ENEMY_H