#ifndef KEYDOORINTERACTION_H
#define KEYDOORINTERACTION_H

#include <SFML/Graphics.hpp>

class KeyDoorInteraction {
public:
    bool hasKey;
    sf::Sprite keySprite;
    sf::Sprite doorSprite;
    sf::Texture keyTexture;
    sf::Texture doorClosedTexture;
    sf::Texture doorOpenedTexture;
    sf::Font font;
    sf::Text keyText;

    KeyDoorInteraction(const std::string& keyPath, const std::string& doorClosedPath, const std::string& doorOpenedPath, const std::string& fontPath);
    void updateKeyText();
    void draw(sf::RenderWindow& window) const;
    bool checkKeyCollision(const sf::FloatRect& playerRect) const;
    void handleKeyCollision();
    bool checkDoorCollision(const sf::FloatRect& playerRect) const;
    bool isDoorOpen() const;
    void showWinMessage(sf::RenderWindow& window) const;
};

#endif // KEYDOORINTERACTION_H