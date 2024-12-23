#include "MAP.h"

std::string TileMap[H] = {
    "#################################################",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#########                              ##########",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#           #######         #########           #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                    ####                       #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#                                               #",
    "#################################################"
};


int MAP::mapCount = 0; // Инициализация статического поля

MAP::MAP(const std::string& stonePath) {
    if (!stoneTexture.loadFromFile(stonePath)) {
        throw std::runtime_error("Не удалось загрузить текстуру камня!");
    }

    mapCount++; // Увеличиваем счетчик при создании новой карты
}

void MAP::draw(sf::RenderWindow& window) const {
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    tile.setTexture(&stoneTexture);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (TileMap[i][j] == '#') {
                tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                window.draw(tile);
            }
        }
    }
}

sf::Vector2u MAP::getSize() const {
    return sf::Vector2u(W * TILE_SIZE, H * TILE_SIZE);
}