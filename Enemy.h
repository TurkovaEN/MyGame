#ifndef ENEMY_H
#define ENEMY_H

#include "PLAYER.h"


class Enemy : public PLAYER {
public:
    Enemy(sf::Texture& image);
    Enemy& operator=(const PLAYER& other);

    void update(float time, MapCollider& mapCollider) override; // ����������� �����
    void display(std::ostream& os) const override; // �������������� �����

};


#endif // ENEMY_H