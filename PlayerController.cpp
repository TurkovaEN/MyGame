#include "PlayerController.h"
#include <SFML/Window.hpp>

void PlayerController::handleInput(PLAYER& player) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.dx = -0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.dx = 0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (player.onGround) {
            player.dy = -0.45; // высота прыжка
            player.onGround = false;
        }
    }
}