#include "PLAYER.h"
#include "MapCollider.h"
#include <iostream>

PLAYER::PLAYER(sf::Texture& image) {
    sprite.setTexture(image);
    rect = sf::FloatRect(245, 186, 110, 112); // rect (x,y, width, height)

    dx = dy = 0.1;
    currentFrame = 0;
    sprite.setTextureRect(sf::IntRect(245, 186, 110, 112));
}

void PLAYER::update(float time, MapCollider& mapCollider) {
    /*
    rect.left += dx * time; // координата х
    mapCollider.handleCollision(rect, dx, dy, onGround, 0); // √оризонтальное столкновение

    */
    this->rect.left += this->dx * time; // »спользуем this дл€ €сности
    mapCollider.handleCollision(this->rect, this->dx, this->dy, this->onGround, 0);


    if (!onGround)
        dy = dy + 0.0005 * time; // ускорение свободного падени€ при прыжке
    rect.top += dy * time; // координата у
    onGround = false;
    mapCollider.handleCollision(rect, dx, dy, onGround, 1); // ¬ертикальное столкновение

    currentFrame += 0.005 * time;
    if (currentFrame > 7)
        currentFrame -= 7;

    if (dx > 0)
        sprite.setTextureRect(sf::IntRect(160 * int(currentFrame) + 245, 185, 95, 118));
    if (dx < 0)
        sprite.setTextureRect(sf::IntRect(160 * int(currentFrame) + 245 + 95, 185, -95, 118));

    sprite.setPosition(rect.left, rect.top); // вывод спрайта в позицию х, у

    dx = 0;

    
}

void printPlayerInfo(const PLAYER & player) {
        std::cout << "Player Position: (" << player.rect.left << ", " << player.rect.top << ")\n";
        std::cout << "Player Speed: (" << player.dx << ", " << player.dy << ")\n";
}
