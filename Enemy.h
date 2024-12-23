#ifndef ENEMY_H
#define ENEMY_H

#include "PLAYER.h"

class Enemy : public PLAYER {
public:
    Enemy(sf::Texture& image) : PLAYER(image) {
        // ��������� ��������� �������� ��� �����
        dx = 0.05; // �������� �����
        dy = 0; // ������������ ��������
    }

    void update(float time, MapCollider& mapCollider) {
        // ������ �������� ����� (��������, �������� ����� � ������)
        this->rect.left += this->dx * time; // �������� �����
        if (this->rect.left < 0 || this->rect.left > 1570) {
            dx = -dx; // ��������� �����������
        }
        mapCollider.handleCollision(this->rect, this->dx, this->dy, this->onGround, 0);

        // ���������� ������������� ���������
        rect.top += dy * time;
        onGround = false;
        mapCollider.handleCollision(rect, dx, dy, onGround, 1);

        // ���������� �������
        sprite.setPosition(rect.left, rect.top);
    }
};

#endif // ENEMY_H