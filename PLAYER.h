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

    float* getSpeedPointer() {
        return &dx; // ���������� ��������� �� �������� �� ��� X
    }
    float& getSpeedReference() {
        return dx; // ���������� ������ �� �������� �� ��� X
    }

    PLAYER operator+(const PLAYER& other) {
        PLAYER result(*this);
        result.dx += other.dx; // ��������� ��������
        return result;
    }

    PLAYER& operator++() { // ���������� ���������
        this->dx += 1.0f; // ����������� ��������
        return *this;
    }

    PLAYER operator++(int) { // ����������� ���������
        PLAYER temp = *this;
        this->dx += 1.0f;
        return temp;
    }

    friend void printPlayerInfo(const PLAYER& player); // ������������� �������
};

#endif // PLAYER_H
