#include <stdio.h>
#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
	RenderWindow window(VideoMode(900, 900), "MyGame"); //создание окна

	Sprite s;
	Texture t;
	t.loadFromFile("sprite1.png"); //добавление текстуры спрайта из файла
	s.setTexture(t);
	s.setTextureRect(IntRect(253, 286, 120, 150));

	s.setPosition(50, 100); //установка спрайта на карту

	while (window.isOpen())
	{
		Event event; //обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //закрытие окна, нажатием на крестик
				window.close();
		}

		//движение на стрелочки

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

		window.clear(Color::White); //задний фон окна
		window.draw(s); //вывод спрайта
		window.display(); //обновление содержимого окна
	}


	return 0;




}