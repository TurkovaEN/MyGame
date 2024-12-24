#include "Enemy.h"

#include "MapCollider.h"

// ����������� ������ Enemy
Enemy::Enemy(sf::Texture& image) : PLAYER(image) {
    // ��������� ��������� �������� ��� �����
    dx = 0.05; // �������� �����
    dy = 0; // ������������ ��������
}

void Enemy::update(float time, MapCollider& mapCollider) {
    PLAYER::update(time, mapCollider); // ����� ������ �������� ������

    // �������������� ������ ��� �����
    this->rect.left += this->dx * time; // �������� �����
    if (this->rect.left < 0 || this->rect.left > 1570) {
        dx = -dx; // ��������� �����������
    }
    mapCollider.handleCollision(this->rect, this->dx, this->dy, this->onGround, 0); // ��������� ������������

    // ���������� �������
    sprite.setPosition(rect.left, rect.top);
}

void Enemy::display(std::ostream& os) const {
    os << "Enemy Position: (" << rect.left << ", " << rect.top << ")\n";
    os << "Enemy Speed: (" << dx << ", " << dy << ")\n";
}

// ���������� ��������� ������������
Enemy & Enemy::operator=(const PLAYER & other) {
    if (this != &other) {
        // �������� ������ �� other � this
        this->dx = other.getDX();
        this->dy = other.getDY();
        this->rect = other.getRect();
        this->onGround = other.isOnGround();
        this->sprite = other.getSprite(); // ���� �����, �������� ������
        // ����� �������� ������ ����������� ����
    }
    return *this;
}