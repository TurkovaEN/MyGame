#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class PLAYER {
public:
    float dx, dy; // ��������
    sf::FloatRect rect; // ���������� ������ � ������
    bool onGround; // �������� ��������� �� ������ �� �����
    sf::Sprite sprite; // ������
    float currentFrame; // ������� ����

    PLAYER(sf::Texture& image);
    void update(float time, class MapCollider& mapCollider);
};

#endif // PLAYER_H
