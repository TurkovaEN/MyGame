#ifndef MAPCOLLIDER_H
#define MAPCOLLIDER_H

#include <SFML/Graphics.hpp>

class MapCollider {
public:
    bool checkCollision(const sf::FloatRect& rect, int dir) const;
    void handleCollision(sf::FloatRect& rect, float& dx, float& dy, bool& onGround, int dir);
};

#endif 