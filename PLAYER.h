#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <ostream>

class Character {
public:
    virtual void update(float time, class MapCollider& mapCollider) = 0; // ����� ����������� �������
    virtual void display(std::ostream& os) const = 0; // ����� ����������� �������
    virtual ~Character() = default; // ����������� ����������
};

class PLAYER : public Character {
//public:
protected:
    float dx, dy; // ��������

    sf::FloatRect rect; // ���������� ������ � ������
    bool onGround; // �������� ��������� �� ������ �� �����
    sf::Sprite sprite; // ������
    float currentFrame; // ������� ����
public:
    PLAYER(sf::Texture& image);
    void update(float time, class MapCollider& mapCollider) override;;
   
    // ������� ��� ������� � protected �����
    const sf::FloatRect& getRect() const { return rect; }
    const sf::Sprite& getSprite() const { return sprite; }
    float getDX() const { return dx; }
    float getDY() const { return dy; }
    bool isOnGround() const { return onGround; }

    // �������
    void setDX(float value) { dx = value; }
    void setDY(float value) { dy = value; }
    void setOnGround(bool value) { onGround = value; }

    void display(std::ostream& os) const override;
    friend std::ostream& operator<<(std::ostream& os, const PLAYER& player);
};
std::ostream& operator<<(std::ostream& os, const PLAYER& player);

#endif // PLAYER_H
