#include "Enemy.h"

#include "MapCollider.h"

// Конструктор класса Enemy
Enemy::Enemy(sf::Texture& image) : PLAYER(image) {
    // Установка начальных значений для врага
    dx = 0.05; // скорость врага
    dy = 0; // вертикальная скорость
}

void Enemy::update(float time, MapCollider& mapCollider) {
    PLAYER::update(time, mapCollider); // Вызов метода базового класса

    // Дополнительная логика для врага
    this->rect.left += this->dx * time; // Движение врага
    if (this->rect.left < 0 || this->rect.left > 1570) {
        dx = -dx; // Изменение направления
    }
    mapCollider.handleCollision(this->rect, this->dx, this->dy, this->onGround, 0); // Обработка столкновений

    // Обновление спрайта
    sprite.setPosition(rect.left, rect.top);
}

void Enemy::display(std::ostream& os) const {
    os << "Enemy Position: (" << rect.left << ", " << rect.top << ")\n";
    os << "Enemy Speed: (" << dx << ", " << dy << ")\n";
}

// Перегрузка оператора присваивания
Enemy & Enemy::operator=(const PLAYER & other) {
    if (this != &other) {
        // Копируем данные из other в this
        this->dx = other.getDX();
        this->dy = other.getDY();
        this->rect = other.getRect();
        this->onGround = other.isOnGround();
        this->sprite = other.getSprite(); // Если нужно, копируем спрайт
        // Можно добавить другие необходимые поля
    }
    return *this;
}