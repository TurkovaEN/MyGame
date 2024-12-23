#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "KeyDoorInteraction.h"
#include "PlayerController.h"



int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1570, 730), "MyGame", sf::Style::Close);

    // текстуры
    sf::Texture t;
    t.loadFromFile("sprite_character.png"); // добавление текстуры спрайта из файла

    sf::Texture background;
    background.loadFromFile("background.jpg");
    sf::Sprite BG;
    BG.setTexture(background);
    BG.setPosition(0, 0);

    MAP GameMap("stone.jpg");
    PLAYER p(t);
    MapCollider mapCollider;
    PlayerController playerController;

    KeyDoorInteraction keyDoor(
        "key.png",  // Путь к текстуре ключа
        "door_close.jpg", // Путь к текстуре закрытой двери
        "door_open.jpg",  // Путь к текстуре открытой двери
        "arial_bolditalicmt.ttf"  // Путь к шрифту
    );
    sf::Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 400;

        sf::Event event; // обработка событий
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) // закрытие окна, нажатием на крестик
                window.close();
        }

        // Обработка ввода
        playerController.handleInput(p); // Передаем объект PLAYER в PlayerController

        p.update(time, mapCollider);

        // Проверка на столкновение с ключом
        if (keyDoor.checkKeyCollision(p.rect)) {
            keyDoor.handleKeyCollision();
        }
        // Проверка на столкновение с открытой дверью и переход на следующий уровень
        if (keyDoor.checkDoorCollision(p.rect) && keyDoor.isDoorOpen()) {
            keyDoor.showWinMessage(window);
            window.close(); // Закрыть окно после победы
        }

        window.clear();
        window.draw(BG); // отрисовка заднего фона
        GameMap.draw(window); // отрисовка карты
        keyDoor.draw(window); // Отрисовка ключа и двери
        window.draw(p.sprite); // отрисовка спрайта		

        // Вывод информации о игроке
        printPlayerInfo(p);

        window.display(); // обновление содержимого окна	
    }
    return 0;
}