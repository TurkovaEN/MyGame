#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "KeyDoorInteraction.h"
#include "PlayerController.h"
#include <iostream>
#include <vector>



int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1570, 730), "MyGame", sf::Style::Close);

    // текстуры
    sf::Texture t;

    try {
        if (!t.loadFromFile("sprite_character.png")) {
            throw std::runtime_error("Не удалось загрузить текстуру персонажа!");
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // Завершение программы при ошибке
    }

    sf::Texture background;

    try {
        if (!background.loadFromFile("background.jpg")) {
            throw std::runtime_error("Не удалось загрузить текстуру фона!");
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // Завершение программы при ошибке
    }

    sf::Sprite BG;
    BG.setTexture(background);
    BG.setPosition(0, 0);

    // Создание массива объектов PLAYER
    const int playerCount = 5; // Количество игроков
    std::vector<PLAYER> players;
    for (int i = 0; i < playerCount; ++i) {
        players.emplace_back(t); // Добавляем игроков в массив
    }

    // Создание двумерного массива объектов MAP
    const int mapCount = 2; // Количество карт
    MAP* maps[mapCount];
    try {
        for (int i = 0; i < mapCount; ++i) {
            maps[i] = new MAP("stone.jpg"); // Создаем карты
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // Завершение программы при ошибке
    }


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

        // Обработка ввода для всех игроков
        for (auto& player : players) {
            playerController.handleInput(player); // Передаем объект PLAYER в PlayerController
            player.update(time, mapCollider);
        }

        // Проверка на столкновение с ключом
        if (keyDoor.checkKeyCollision(players[0].rect)) { // Проверяем только первого игрока
            keyDoor.handleKeyCollision();
        }
        // Проверка на столкновение с открытой дверью и переход на следующий уровень
        if (keyDoor.checkDoorCollision(players[0].rect) && keyDoor.isDoorOpen()) {
            keyDoor.showWinMessage(window);
            window.close(); // Закрыть окно после победы
        }

        window.clear();
        window.draw(BG); // отрисовка заднего фона
        for (int i = 0; i < mapCount; ++i) {
            maps[i]->draw(window); // отрисовка карт
        }
        keyDoor.draw(window); // Отрисовка ключа и двери
        for (const auto& player : players) {
            window.draw(player.sprite); // отрисовка спрайтов игроков
        }

        // Вывод информации о первом игроке
        printPlayerInfo(players[0]);


        window.display(); // обновление содержимого окна	
    }
    // Освобождение памяти для карт
    for (int i = 0; i < mapCount; ++i) {
        delete maps[i];
    }

    return 0;
}