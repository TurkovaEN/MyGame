#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

const int H = 23;
const int W = 50;
const int TILE_SIZE = 32;

extern std::string TileMap[H];

class MAP {
public:
    static int mapCount; // —татическое поле дл€ отслеживани€ количества карт

    sf::Texture stoneTexture;

    MAP(const std::string& stonePath);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2u getSize() const;

    static int getMapCount() { // —татический метод дл€ получени€ количества карт
        return mapCount;
    }
};

#endif // MAP_H