#include <stdio.h>
#include <SFML/Graphics.hpp>

int ground = 580;
using namespace sf;

const int H = 23;
const int W = 50;

String TileMap[H] = {
	"#################################################",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#  K                                         E  #",
	"#########                              ##########",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#           #######         #########           #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                    ####                       #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#                                               #",
	"#################################################"
};

class PLAYER {
public:
	float dx, dy; //скорость
	FloatRect rect; // координаты ширины и высоты
	bool onGround; // проверка находится ли спрайт на земле
	Sprite sprite; //
	float currentFrame; //текущий кадр

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(220, 189, 158, 112); //rect (x,y, width, height), (x,y) - координаты левого верхнего угла, width - ширина, height - высота
		


		dx = dy = 0.1;
		currentFrame = 0;
	}

	void update(float time) 
	{
		
		rect.left += dx * time; //координата х
		Collision(0);

		if (!onGround) 
			dy = dy + 0.0005 * time; //ускорение свободного падения при прыжке
		rect.top += dy * time; //координата у
		onGround = false;
		Collision(1);


		currentFrame += 0.005 * time;
		if (currentFrame > 7)
			currentFrame -= 7;

		if (dx>0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 220, 185, 160, 118));
		if(dx<0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 220 + 160, 185, -160, 118));

		sprite.setPosition(rect.left, rect.top); //вывод спрайта в позицию х, у

		dx = 0;
	}

	//обработка столкновений
	void Collision(int dir)
	{
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left+rect.width)/32; j++) {
				if (TileMap[i][j] == '#') {

					if ((dx > 0)&&(dir==0)) rect.left = j * 32 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;

					if ((dy > 0) && (dir == 1)) {
						rect.top = i * 32 - rect.height;
						dy = 0;
						onGround = true;
					}
					if ((dy < 0) && (dir == 1)) {
						rect.top = i * 32 + 32;
						dy = 0;
					}
				}

			}
	}
	
};

int main()
{
	RenderWindow window(VideoMode(1600, 735), "MyGame"); //создание окна
	Texture t;
	t.loadFromFile("sprite_character.png"); //добавление текстуры спрайта из файла

	PLAYER p(t);

	float currentFrame = 0;

	Clock clock;

	RectangleShape rectangle(Vector2f(32,32));


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 400;

		Event event; //обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //закрытие окна, нажатием на крестик
				window.close();
		}

		//движение на стрелочки

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
				p.dy = -0.45; //высота прыжка
				p.onGround = false;
			}
		}
		p.update(time);

		window.clear(Color::White); //задний фон окна

		for(int i = 0; i < H; i++)
			for (int j = 0; j < W; j++) {
				if (TileMap[i][j] == '#')
					rectangle.setFillColor(Color::Black); //стены
				else if (TileMap[i][j] == 'K')
					rectangle.setFillColor(Color::Yellow); //для ключа
				else if (TileMap[i][j] == 'E')
					rectangle.setFillColor(Color::Blue); //для выхода
				else if (TileMap[i][j] == ' ')
					continue;
				rectangle.setPosition(j * 32, i * 32);
				window.draw(rectangle);
			}

		window.draw(p.sprite);

		window.display(); //обновление содержимого окна

		
	}
	return 0;
}
