#include <stdio.h>
#include <SFML/Graphics.hpp>

int ground = 150;
using namespace sf;


class PLAYER {
public:
	float dx, dy; //��������
	FloatRect rect; // ���������� ������ � ������
	bool onGround; // �������� ��������� �� ������ �� �����
	Sprite sprite; //
//	float currentFrame; //������� ����

	PLAYER(Texture &image)
	{
		rect = FloatRect(0, 0, 40, 50);
		dx = dy = 0;
	}

	void update(float time) {
		rect.left += dx * time; //���������� �

		if (!onGround) 
			dy = dy + 0.00005 * time; //��������� ���������� ������� ��� ������
		rect.top += dy * time; //���������� �
		onGround = false;

		if (rect.top > ground)
		{
			rect.top = ground; 
			dy = 0;
			onGround = true;
		}

		

		sprite.setPosition(rect.left, rect.top); //����� ������� � ������� �, �
		dx = 0;
	}

};

int main()
{
	RenderWindow window(VideoMode(900, 900), "MyGame"); //�������� ����
	Texture t;
		t.loadFromFile("testik.png"); //���������� �������� ������� �� �����
		
	PLAYER p(t);
	
	p.sprite.setTexture(t);
	p.sprite.setPosition(-0, 0);
		

	/*
	Sprite s;
	
	Texture t;
	t.loadFromFile("sprite1.png"); //���������� �������� ������� �� �����
	s.setTexture(t);
	s.setTextureRect(IntRect(253, 286, 120, 150));
	
	s.setPosition(50, 100); //��������� ������� �� �����
	*/
	
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Event event; //��������� �������
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //�������� ����, �������� �� �������
				window.close();
		}

		//�������� �� ���������

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			//s.move(-0.1, 0);
			p.dx = -0,1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			//s.move(0.1, 0);
			p.dx = 0,1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			//s.move(0, 0.1);
			if (p.onGround) {
				p.dy = -0.4;
				p.onGround = false;
			}
		}
		p.update(time);

		window.clear(Color::White); //������ ��� ����
		window.draw(p.sprite); //����� �������
		window.display(); //���������� ����������� ����
	}


	return 0;




}