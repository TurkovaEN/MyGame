#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class PLAYER {
public:
    float dx, dy; // скорость
    sf::FloatRect rect; // координаты ширины и высоты
    bool onGround; // проверка находится ли спрайт на земле
    sf::Sprite sprite; // спрайт
    float currentFrame; // текущий кадр

    PLAYER(sf::Texture& image);
    void update(float time, class MapCollider& mapCollider);

    float* getSpeedPointer() {
        return &dx; // Возвращаем указатель на скорость по оси X
    }
    float& getSpeedReference() {
        return dx; // Возвращаем ссылку на скорость по оси X
    }

    PLAYER operator+(const PLAYER& other) {
        PLAYER result(*this);
        result.dx += other.dx; // Суммируем скорости
        return result;
    }

    PLAYER& operator++() { // Префиксный инкремент
        this->dx += 1.0f; // Увеличиваем скорость
        return *this;
    }

    PLAYER operator++(int) { // Постфиксный инкремент
        PLAYER temp = *this;
        this->dx += 1.0f;
        return temp;
    }

    friend void printPlayerInfo(const PLAYER& player); // Дружественная функция
};

#endif // PLAYER_H
