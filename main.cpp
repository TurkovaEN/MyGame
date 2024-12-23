#include <SFML/Graphics.hpp>
#include "MAP.h"
#include "MapCollider.h"
#include "PLAYER.h"
#include "KeyDoorInteraction.h"
#include "PlayerController.h"



int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1570, 730), "MyGame", sf::Style::Close);

    // ��������
    sf::Texture t;
    t.loadFromFile("sprite_character.png"); // ���������� �������� ������� �� �����

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

        // ��������� �����
        playerController.handleInput(p); // �������� ������ PLAYER � PlayerController

        p.update(time, mapCollider);

        // �������� �� ������������ � ������
        if (keyDoor.checkKeyCollision(p.rect)) {
            keyDoor.handleKeyCollision();
        }
        // �������� �� ������������ � �������� ������ � ������� �� ��������� �������
        if (keyDoor.checkDoorCollision(p.rect) && keyDoor.isDoorOpen()) {
            keyDoor.showWinMessage(window);
            window.close(); // ������� ���� ����� ������
        }

        window.clear();
        window.draw(BG); // ��������� ������� ����
        GameMap.draw(window); // ��������� �����
        keyDoor.draw(window); // ��������� ����� � �����
        window.draw(p.sprite); // ��������� �������		

        // ����� ���������� � ������
        printPlayerInfo(p);

        window.display(); // ���������� ����������� ����	
    }
    return 0;
}