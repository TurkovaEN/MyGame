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
};

#endif // PLAYER_H
