#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

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
	"#                                               #",
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
	Texture stoneTexture; // Текстура для тайлов

	MAP(const std::string& stonePath) {
		if (!stoneTexture.loadFromFile(stonePath)) {
			// Обработка ошибки загрузки текстуры
			throw std::runtime_error("Не удалось загрузить текстуру камня!");
		}
	}

	// Метод для отрисовки карты
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

	// Метод для получения размера карты
	Vector2u getSize() const {
		return Vector2u(W * TILE_SIZE, H * TILE_SIZE);
	}
};

class MapCollider {
public:
	// Проверка столкновений
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
	//Обработка столкновений
	void handleCollision(FloatRect& rect, float& dx, float& dy, bool& onGround, int dir) {
		for (int i = rect.top / TILE_SIZE; i < (rect.top + rect.height) / TILE_SIZE; ++i) {
			for (int j = rect.left / TILE_SIZE; j < (rect.left + rect.width) / TILE_SIZE; ++j) {
				if (i >= 0 && i < H && j >= 0 && j < W && TileMap[i][j] == '#') {
					if (dir == 0) { // Горизонтальное столкновение
						if (dx > 0) rect.left = j * TILE_SIZE - rect.width;
						if (dx < 0) rect.left = j * TILE_SIZE + TILE_SIZE;
						dx = 0;
					}
					else { //Вертикальное столкновение
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
	bool onGround; // проверка находится ли спрайт на земле
	Sprite sprite; //
	float currentFrame; //текущий кадр
	

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(245, 186, 110, 112); //rect (x,y, width, height), (x,y) - координаты левого верхнего угла, width - ширина, height - высота

		dx = dy = 0.1;
		currentFrame = 0;
		sprite.setTextureRect(IntRect(245, 186, 110, 112));
	}

	void update(float time, MapCollider& mapCollider)
	{
		
		rect.left += dx * time; //координата х
		mapCollider.handleCollision(rect, dx, dy, onGround, 0); // Горизонтальное столкновение

		if (!onGround) 
			dy = dy + 0.0005 * time; //ускорение свободного падения при прыжке
		rect.top += dy * time; //координата у
		onGround = false;
		mapCollider.handleCollision(rect, dx, dy, onGround, 1); //Вертикальное столкновение


		currentFrame += 0.005 * time;
		if (currentFrame > 7)
			currentFrame -= 7;

		if (dx>0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 245, 185, 95, 118));
		if(dx<0)
			sprite.setTextureRect(IntRect(160 * int(currentFrame) + 245 + 95, 185, -95, 118));

		sprite.setPosition(rect.left, rect.top); //вывод спрайта в позицию х, у

		dx = 0;

	}
	
};

class KeyDoorInteraction {
public:
	bool hasKey = false;
	Sprite keySprite;
	Sprite doorSprite;
	Texture keyTexture;
	Texture doorClosedTexture;
	Texture doorOpenedTexture;
	Font font;
	Text keyText;


	KeyDoorInteraction(const std::string& keyPath, const std::string& doorClosedPath, const std::string& doorOpenedPath, const std::string& fontPath) {
		if (!keyTexture.loadFromFile(keyPath)) {
			throw std::runtime_error("Не удалось загрузить текстуру ключа!");
		}
		if (!doorClosedTexture.loadFromFile(doorClosedPath)) {
			throw std::runtime_error("Не удалось загрузить текстуру закрытой двери!");
		}
		if (!doorOpenedTexture.loadFromFile(doorOpenedPath)) {
			throw std::runtime_error("Не удалось загрузить текстуру открытой двери!");
		}
		if (!font.loadFromFile(fontPath)) {
			throw std::runtime_error("Не удалось загрузить шрифт!");
		}

		keySprite.setTexture(keyTexture);
		doorSprite.setTexture(doorClosedTexture);
		keyText.setFont(font);
		keyText.setCharacterSize(30);
		keyText.setFillColor(sf::Color::White);
		keyText.setPosition(35, 25);
		updateKeyText();

		//  Изначальные позиции ключа и двери 
		keySprite.setPosition(1420, 160);
		doorSprite.setPosition(1280, 550); 
	}


	void updateKeyText() {
		std::string keyStatus = hasKey ?"yes" : "no";
		keyText.setString(L"Key: " + keyStatus);
	}


	void draw(RenderWindow& window) const {
		window.draw(keySprite);
		window.draw(doorSprite);
		window.draw(keyText);
	}


	bool checkKeyCollision(const FloatRect& playerRect) const {
		return keySprite.getGlobalBounds().intersects(playerRect);
	}


	void handleKeyCollision() {
		hasKey = true;
		updateKeyText();
		keySprite.setPosition(-100, -100); // Убираем ключ с экрана
		doorSprite.setTexture(doorOpenedTexture);
	}


	bool checkDoorCollision(const FloatRect& playerRect) const {
		return doorSprite.getGlobalBounds().intersects(playerRect);
	}


	bool isDoorOpen() const {
		return hasKey;
	}

	void showWinMessage(RenderWindow& window) const {
		Font font;
		if (!font.loadFromFile("ofont.ru_Arial Cyr.ttf")) { // или путь к вашему шрифту
			throw std::runtime_error("Не удалось загрузить шрифт!");
		}
		Text winText(L"Вы прошли уровень! Продолжение игры в разработке...", font, 32);
		winText.setFillColor(sf::Color::Green);
		winText.setPosition((window.getSize().x - winText.getLocalBounds().width) / 2.0f, (window.getSize().y - winText.getLocalBounds().height) / 2.0f);
		window.draw(winText);
		window.display();
		sleep(seconds(3)); //Подождать 3 секунды
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

	KeyDoorInteraction keyDoor(
		"key.png",  // Путь к текстуре ключа
		"door_close.png", // Путь к текстуре закрытой двери
		"door_open.png",  // Путь к текстуре открытой двери
		"ofont.ru_Arial Cyr.ttf"  // Путь к шрифту
	);

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

		// Проверка на столкновение с ключом
		if (keyDoor.checkKeyCollision(p.rect)) {
			keyDoor.handleKeyCollision();
		}
		// Проверка на столкновение с открытой дверью и переход на следующий уровень
		if (keyDoor.checkDoorCollision(p.rect) && keyDoor.isDoorOpen()) {
			keyDoor.showWinMessage(window);
			window.close(); // Закрыть окно после победы
		}

		window.clear();
		window.draw(BG); //отрисовка заднего фона
		GameMap.draw(window); // отрисовка карты
		keyDoor.draw(window); // Отрисовка ключа и двери
		window.draw(p.sprite); // отрисовка спрайта		
		window.display(); //обновление содержимого окна	
	}
	return 0;
}
