#include "KeyDoorInteraction.h"
#include <SFML/Graphics.hpp>

KeyDoorInteraction::KeyDoorInteraction(const std::string& keyPath, const std::string& doorClosedPath, const std::string& doorOpenedPath, const std::string& fontPath)
    : hasKey(false) {
    if (!keyTexture.loadFromFile(keyPath)) {
        throw std::runtime_error("�� ������� ��������� �������� �����!");
    }
    if (!doorClosedTexture.loadFromFile(doorClosedPath)) {
        throw std::runtime_error("�� ������� ��������� �������� �������� �����!");
    }
    if (!doorOpenedTexture.loadFromFile(doorOpenedPath)) {
        throw std::runtime_error("�� ������� ��������� �������� �������� �����!");
    }
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("�� ������� ��������� �����!");
    }

    keySprite.setTexture(keyTexture);
    doorSprite.setTexture(doorClosedTexture);
    keyText.setFont(font);
    keyText.setCharacterSize(30);
    keyText.setFillColor(sf::Color::White);
    keyText.setPosition(35, 25);
    updateKeyText();

    // ����������� ������� ����� � ����� 
    keySprite.setPosition(1420, 160);
    doorSprite.setPosition(1280, 550);
}

void KeyDoorInteraction::updateKeyText() {
    std::string keyStatus = hasKey ? "yes" : "no";
    keyText.setString("Key: " + keyStatus);
}

void KeyDoorInteraction::draw(sf::RenderWindow& window) const {
    window.draw(keySprite);
    window.draw(doorSprite);
    window.draw(keyText);
}

bool KeyDoorInteraction::checkKeyCollision(const sf::FloatRect& playerRect) const {
    return keySprite.getGlobalBounds().intersects(playerRect);
}

void KeyDoorInteraction::handleKeyCollision() {
    hasKey = true;
    updateKeyText();
    keySprite.setPosition(-100, -100); // ������� ���� � ������
    doorSprite.setTexture(doorOpenedTexture);
}

bool KeyDoorInteraction::checkDoorCollision(const sf::FloatRect& playerRect) const {
    return doorSprite.getGlobalBounds().intersects(playerRect);
}

bool KeyDoorInteraction::isDoorOpen() const {
    return hasKey;
}

void KeyDoorInteraction::showWinMessage(sf::RenderWindow& window) const {
    sf::Font font;
    if (!font.loadFromFile("arial_bolditalicmt.ttf")) { 
        throw std::runtime_error("�� ������� ��������� �����!");
    }
    sf::Text winText(L"�� ������ �������! ����������� ���� � ����������...", font, 32);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition((window.getSize().x - winText.getLocalBounds().width) / 2.0f, (window.getSize().y - winText.getLocalBounds().height) / 2.0f);
    window.draw(winText);
    window.display();
    sf::sleep(sf::seconds(3)); // ��������� 3 �������
}