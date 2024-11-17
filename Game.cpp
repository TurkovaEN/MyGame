#include <stdio.h>
#include <SFML/Graphics.hpp>

int ground = 550;
using namespace sf;


class PLAYER {
public:
	float dx, dy; //��������
	FloatRect rect; // ���������� ������ � ������
	bool onGround; // �������� ��������� �� ������ �� �����
	Sprite sprite; //
	float currentFrame; //������� ����

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(220, 189, 158, 112); //rect (x,y, width, height), (x,y) - ���������� ������ �������� ����, width - ������, height - ������

		dx = dy = 0.1;
		currentFrame = 0;
	}

	void update(float time) 
	{
		rect.left += dx * time; //���������� �

		if (!onGround) 
			dy = dy + 0.0005 * time; //��������� ���������� ������� ��� ������
		rect.top += dy * time; //���������� �
		onGround = false;

		
		if (rect.top > ground)
		{
			rect.top = ground; 
			dy = 0;
			onGround = true;
		}
		
		

		currentFrame += 0.005 * time;
		if (currentFrame > 7)
			currentFrame -= 7;

		if (dx>0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 220, 185, 160, 118));
		if(dx<0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 220 + 160, 185, -160, 118));

		sprite.setPosition(rect.left, rect.top); //����� ������� � ������� �, �

		dx = 0;
	}

};

int main()
{
	RenderWindow window(VideoMode(2500, 1250), "MyGame"); //�������� ����
	Texture t;
	t.loadFromFile("sprite_character.png"); //���������� �������� ������� �� �����

	PLAYER p(t);

	float currentFrame = 0;

	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 400;

		Event event; //��������� �������
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //�������� ����, �������� �� �������
				window.close();
		}

		//�������� �� ���������

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) {
				p.dy = -0.4; //������ ������
				p.onGround = false;
			}
		}
		p.update(time);

		window.clear(Color::White); //������ ��� ����

		window.draw(p.sprite);

		window.display(); //���������� ����������� ����

		
	}
	return 0;
}
