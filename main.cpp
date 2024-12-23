#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "Enemy.h" // ���������� ����� �����
#include "KeyDoorInteraction.h"
#include "PlayerController.h"
#include <iostream>
#include <vector>
#include <algorithm> // ��� std::sort � std::find_if

// ������� ��� ���������� ������� �� ��������
bool compareSpeed(const PLAYER& a, const PLAYER& b) {
    return a.dx < b.dx; // ���������� �� ��������
}

// ������� ��� ������ ������ �� �������
PLAYER* findPlayerByPosition(std::vector<PLAYER>& players, float x, float y) {
    auto it = std::find_if(players.begin(), players.end(), [x, y](const PLAYER& player) {
        return player.rect.left == x && player.rect.top == y;
        });
    return (it != players.end()) ? &(*it) : nullptr; // ���������� ��������� �� ������ ��� nullptr
}

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

    // �������� ������� �������� PLAYER
    const int playerCount = 5; // ���������� �������
    std::vector<PLAYER> players;
    for (int i = 0; i < playerCount; ++i) {
        players.emplace_back(t); // ��������� ������� � ������
    }
    // �������� ������
    const int enemyCount = 3; // ���������� ������
    std::vector<Enemy> enemies;
    for (int i = 0; i < enemyCount; ++i) {
        enemies.emplace_back(t); // ��������� ������ � ������
    }

    // ���������� ������� �� ��������
    std::sort(players.begin(), players.end(), compareSpeed);

    // ����� ������ �� �������
    PLAYER* foundPlayer = findPlayerByPosition(players, players[0].rect.left, players[0].rect.top);
    if (foundPlayer) {
        std::cout << "����� ������ �� �������: (" << foundPlayer->rect.left << ", " << foundPlayer->rect.top << ")\n";
    }
    else {
        std::cout << "����� �� ������.\n";
    }

    
    // �������� ���������� ������� �������� MAP
    const int mapCount = 2; // ���������� ����
    MAP* maps[mapCount];
    try {
        for (int i = 0; i < mapCount; ++i) {
            maps[i] = new MAP("stone.jpg"); // ������� �����
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // ���������� ��������� ��� ������
    }
    


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

        // ��������� ����� ��� ���� �������
        for (auto& player : players) {
            playerController.handleInput(player); // �������� ������ PLAYER � PlayerController
            player.update(time, mapCollider);
        }
        for (auto& enemy : enemies) {
            enemy.update(time, mapCollider); // ��������� ������
        }

        // �������� �� ������������ � ������
        if (keyDoor.checkKeyCollision(players[0].rect)) { // ��������� ������ ������� ������
            keyDoor.handleKeyCollision();
        }
        // �������� �� ������������ � �������� ������ � ������� �� ��������� �������
        if (keyDoor.checkDoorCollision(players[0].rect) && keyDoor.isDoorOpen()) {
            keyDoor.showWinMessage(window);
            window.close(); // ������� ���� ����� ������
        }

        window.clear();
        window.draw(BG); // ��������� ������� ����
        for (int i = 0; i < mapCount; ++i) {
            maps[i]->draw(window); // ��������� ����
        }
        keyDoor.draw(window); // ��������� ����� � �����
        for (const auto& player : players) {
            window.draw(player.sprite); // ��������� �������� �������
        }
        for (const auto& enemy : enemies) {
            window.draw(enemy.sprite); // ��������� �������� ������
        }

        // ����� ���������� � ������ ������
        printPlayerInfo(players[0]);


        window.display(); // ���������� ����������� ����	
    }
    // ������������ ������ ��� ����
    for (int i = 0; i < mapCount; ++i) {
        delete maps[i];
    }

    return 0;
}