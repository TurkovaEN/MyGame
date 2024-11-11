#include <stdio.h>
#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
	RenderWindow window(VideoMode(900, 900), "MyGame"); //�������� ����

	Sprite s;
	Texture t;
	t.loadFromFile("sprite1.png"); //���������� �������� ������� �� �����
	s.setTexture(t);
	s.setTextureRect(IntRect(253, 286, 120, 150));

	s.setPosition(50, 100); //��������� ������� �� �����

	while (window.isOpen())
	{
		Event event; //��������� �������
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //�������� ����, �������� �� �������
				window.close();
		}

		//�������� �� ���������

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			s.move(-0.1, 0);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			s.move(0.1, 0);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			s.move(0, 0.1);
		}

		window.clear(Color::White); //������ ��� ����
		window.draw(s); //����� �������
		window.display(); //���������� ����������� ����
	}


	return 0;




}