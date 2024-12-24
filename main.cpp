#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "Enemy.h" // Подключаем новый класс
#include "KeyDoorInteraction.h"
#include "PlayerController.h"
#include "GameObjectManager.h" // Подключаем шаблонный класс
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

    // Создание менеджеров для игроков и врагов
    GameObjectManager<PLAYER> playerManager;
    GameObjectManager<Enemy> enemyManager;

    // Создание объектов PLAYER и добавление их в менеджер
    const int playerCount = 5; // Количество игроков
    for (int i = 0; i < playerCount; ++i) {
        playerManager.addObject(new PLAYER(t)); // Добавляем нового игрока
    }

    // Создание врагов
    const int enemyCount = 3; // Количество врагов
    for (int i = 0; i < enemyCount; ++i) {
        enemyManager.addObject(new Enemy(t)); // Добавляем нового врага
    }


 
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
        playerController.handleInput(p); 

        p.update(time, mapCollider);

        if (keyDoor.checkKeyCollision(p.getRect())) {
            keyDoor.handleKeyCollision();
        }

        if (keyDoor.checkDoorCollision(p.getRect()) && keyDoor.isDoorOpen()) {
            keyDoor.showWinMessage(window);
            window.close();
        }

        // Обновление всех игроков и врагов
        playerManager.updateAll(time, mapCollider);
        enemyManager.updateAll(time, mapCollider);

        window.clear();
        window.draw(BG); 
        GameMap.draw(window); 
        keyDoor.draw(window); 
        window.draw(p.getSprite()); 
        // Отображение всех игроков и врагов
        playerManager.displayAll(std::cout); // Вывод информации о игроках
        enemyManager.displayAll(std::cout); // Вывод информации о врагах

        window.display(); // обновление содержимого окна	
    }
   

    return 0;
   
}