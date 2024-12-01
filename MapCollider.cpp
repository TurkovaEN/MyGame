#include "MapCollider.h"
#include "MAP.h"

bool MapCollider::checkCollision(const sf::FloatRect& rect, int dir) const {
    for (int i = rect.top / TILE_SIZE; i < (rect.top + rect.height) / TILE_SIZE; i++) {
        for (int j = rect.left / TILE_SIZE; j < (rect.left + rect.width) / TILE_SIZE; j++) {
            if (i >= 0 && i < H && j >= 0 && j < W && TileMap[i][j] == '#') {
                return true;
            }
        }
    }
    return false;
}

void MapCollider::handleCollision(sf::FloatRect& rect, float& dx, float& dy, bool& onGround, int dir) {
    for (int i = rect.top / TILE_SIZE; i < (rect.top + rect.height) / TILE_SIZE; ++i) {
        for (int j = rect.left / TILE_SIZE; j < (rect.left + rect.width) / TILE_SIZE; ++j) {
            if (i >= 0 && i < H && j >= 0 && j < W && TileMap[i][j] == '#') {
                if (dir == 0) { // Горизонтальное столкновение
                    if (dx > 0) rect.left = j * TILE_SIZE - rect.width;
                    if (dx < 0) rect.left = j * TILE_SIZE + TILE_SIZE;
                    dx = 0;
                }
                else { // Вертикальное столкновение
                    if (dy > 0) {
                        rect.top = i * TILE_SIZE - rect.height;
                        dy = 0;
                        onGround = true;
                    }
                    if (dy < 0) {
                        rect.top = i * TILE_SIZE + TILE_SIZE;
                        dy = 0;
                    }
                }
                break;
            }
        }
    }
}