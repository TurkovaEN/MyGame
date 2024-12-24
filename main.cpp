#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "Enemy.h" // ���������� ����� �����
#include "KeyDoorInteraction.h"
#include "PlayerController.h"
#include "GameObjectManager.h" // ���������� ��������� �����
#include <iostream>
#include <vector>


int main() {
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(1570, 730), "MyGame", sf::Style::Close);

    // ��������
    sf::Texture t;

    try {
        if (!t.loadFromFile("sprite_character.png")) {
            throw std::runtime_error("�� ������� ��������� �������� ���������!");
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // ���������� ��������� ��� ������
    }

    sf::Texture background;

    try {
        if (!background.loadFromFile("background.jpg")) {
            throw std::runtime_error("�� ������� ��������� �������� ����!");
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // ���������� ��������� ��� ������
    }

    sf::Sprite BG;
    BG.setTexture(background);
    BG.setPosition(0, 0);

    // �������� ���������� ��� ������� � ������
    GameObjectManager<PLAYER> playerManager;
    GameObjectManager<Enemy> enemyManager;

    // �������� �������� PLAYER � ���������� �� � ��������
    const int playerCount = 5; // ���������� �������
    for (int i = 0; i < playerCount; ++i) {
        playerManager.addObject(new PLAYER(t)); // ��������� ������ ������
    }

    // �������� ������
    const int enemyCount = 3; // ���������� ������
    for (int i = 0; i < enemyCount; ++i) {
        enemyManager.addObject(new Enemy(t)); // ��������� ������ �����
    }


 
    MAP GameMap("stone.jpg");
    PLAYER p(t);

    MapCollider mapCollider;
    PlayerController playerController;

    KeyDoorInteraction keyDoor(
        "key.png",  // ���� � �������� �����
        "door_close.jpg", // ���� � �������� �������� �����
        "door_open.jpg",  // ���� � �������� �������� �����
        "arial_bolditalicmt.ttf"  // ���� � ������
    );

    sf::Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 400;

        sf::Event event; // ��������� �������
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) // �������� ����, �������� �� �������
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

        // ���������� ���� ������� � ������
        playerManager.updateAll(time, mapCollider);
        enemyManager.updateAll(time, mapCollider);

        window.clear();
        window.draw(BG); 
        GameMap.draw(window); 
        keyDoor.draw(window); 
        window.draw(p.getSprite()); 
        // ����������� ���� ������� � ������
        playerManager.displayAll(std::cout); // ����� ���������� � �������
        enemyManager.displayAll(std::cout); // ����� ���������� � ������

        window.display(); // ���������� ����������� ����	
    }
   

    return 0;
   
}