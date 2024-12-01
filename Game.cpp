#include <stdio.h>
#include <SFML/Graphics.hpp>

int ground = 580;
using namespace sf;

const int H = 23;
const int W = 50;
const int TILE_SIZE = 32;

std::string TileMap[H] = {
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

class MAP {
public:
	Texture stoneTexture; // “екстура дл€ тайлов

	MAP(const std::string& stonePath) {
		if (!stoneTexture.loadFromFile(stonePath)) {
			// ќбработка ошибки загрузки текстуры
			throw std::runtime_error("Ќе удалось загрузить текстуру камн€!");
		}
	}

	// ћетод дл€ отрисовки карты
	void draw(RenderWindow& window) const {
		RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));
		tile.setTexture(&stoneTexture);

		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				if (TileMap[i][j] == '#') {
					tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
					window.draw(tile);
				}
			}
		}
	}

	// ћетод дл€ получени€ размера карты
	Vector2u getSize() const {
		return Vector2u(W * TILE_SIZE, H * TILE_SIZE);
	}
};



class MapCollider {
public:
	// ѕроверка столкновений
	bool checkCollision(const FloatRect& rect, int dir) const {
		for (int i = rect.top / TILE_SIZE; i < (rect.top + rect.height) / TILE_SIZE; i++) {
			for (int j = rect.left / TILE_SIZE; j < (rect.left + rect.width) / TILE_SIZE; j++) {
				if (i >= 0 && i < H && j >= 0 && j < W && TileMap[i][j] == '#') {
					return true;
				}
			}
		}
		return false;
	}
	//ќбработка столкновений
	void handleCollision(FloatRect& rect, float& dx, float& dy, bool& onGround, int dir) {
		for (int i = rect.top / TILE_SIZE; i < (rect.top + rect.height) / TILE_SIZE; ++i) {
			for (int j = rect.left / TILE_SIZE; j < (rect.left + rect.width) / TILE_SIZE; ++j) {
				if (i >= 0 && i < H && j >= 0 && j < W && TileMap[i][j] == '#') {
					if (dir == 0) { // √оризонтальное столкновение
						if (dx > 0) rect.left = j * TILE_SIZE - rect.width;
						if (dx < 0) rect.left = j * TILE_SIZE + TILE_SIZE;
						dx = 0;
					}
					else { //¬ертикальное столкновение
						if (dy > 0) {
							rect.top = i * TILE_SIZE - rect.height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0) {
							rect.top = i * TILE_SIZE + TILE_SIZE;
							dy = 0;
						}
					}
					break; 
				}
			}
		}
	}
	
};

class PLAYER {
public:
	float dx, dy; //скорость
	FloatRect rect; // координаты ширины и высоты
	bool onGround; // проверка находитс€ ли спрайт на земле
	Sprite sprite; //
	float currentFrame; //текущий кадр
	
	

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(220, 189, 158, 112); //rect (x,y, width, height), (x,y) - координаты левого верхнего угла, width - ширина, height - высота
		dx = dy = 0.1;
		currentFrame = 0;
		onGround = false;
	}

	void update(float time, MapCollider& mapCollider)
	{
		
		rect.left += dx * time; //координата х
		mapCollider.handleCollision(rect, dx, dy, onGround, 0); // √оризонтальное столкновение

		if (!onGround) 
			dy = dy + 0.0005 * time; //ускорение свободного падени€ при прыжке
		rect.top += dy * time; //координата у
		onGround = false;
		mapCollider.handleCollision(rect, dx, dy, onGround, 1); //¬ертикальное столкновение


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
	
};

int main()
{
	RenderWindow window;
	window.create(VideoMode(1570, 730), "MyGame", Style::Close);

			//текстуры
	Texture t;
	t.loadFromFile("sprite_character.png"); //добавление текстуры спрайта из файла

	Texture background;
	background.loadFromFile("background.jpg");
	Sprite BG;
	BG.setTexture(background);
	BG.setPosition(0, 0);

	MAP GameMap("stone.jpg");
	
	PLAYER p(t);
	MapCollider MapCollider;

	float currentFrame = 0;

	Clock clock;


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
		p.update(time, MapCollider);

		window.clear();
		window.draw(BG); //отрисовка заднего фона
		
		GameMap.draw(window); // отрисовка карты
		
		window.draw(p.sprite); // отрисовка спрайта

		window.display(); //обновление содержимого окна

		
	}
	return 0;
}
