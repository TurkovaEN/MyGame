#include <stdio.h>
#include <SFML/Graphics.hpp>

int ground = 150;
using namespace sf;


class PLAYER {
public:
	float dx, dy; //скорость
	FloatRect rect; // координаты ширины и высоты
	bool onGround; // проверка находится ли спрайт на земле
	Sprite sprite; //
//	float currentFrame; //текущий кадр

	PLAYER(Texture &image)
	{
		rect = FloatRect(0, 0, 40, 50);
		dx = dy = 0;
	}

	void update(float time) {
		rect.left += dx * time; //координата х

		if (!onGround) 
			dy = dy + 0.00005 * time; //ускорение свободного падения при прыжке
		rect.top += dy * time; //координата у
		onGround = false;

		if (rect.top > ground)
		{
			rect.top = ground; 
			dy = 0;
			onGround = true;
		}

		

		sprite.setPosition(rect.left, rect.top); //вывод спрайта в позицию х, у
		dx = 0;
	}

};

int main()
{
	RenderWindow window(VideoMode(900, 900), "MyGame"); //создание окна
	Texture t;
		t.loadFromFile("testik.png"); //добавление текстуры спрайта из файла
		
	PLAYER p(t);
	
	p.sprite.setTexture(t);
	p.sprite.setPosition(-0, 0);
		

	/*
	Sprite s;
	
	Texture t;
	t.loadFromFile("sprite1.png"); //добавление текстуры спрайта из файла
	s.setTexture(t);
	s.setTextureRect(IntRect(253, 286, 120, 150));
	
	s.setPosition(50, 100); //установка спрайта на карту
	*/
	
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Event event; //обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //закрытие окна, нажатием на крестик
				window.close();
		}

		//движение на стрелочки

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

		window.clear(Color::White); //задний фон окна
		window.draw(p.sprite); //вывод спрайта
		window.display(); //обновление содержимого окна
	}


	return 0;




}