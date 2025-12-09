#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class Player {
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	bool isOnGround;
	float jumpStrength;
	float moveSpeed;
	float gravity;

public:
	Player(float x, float y) :
		velocity(0, 0),
		isOnGround(false),
		jumpStrength(12.0f),
		moveSpeed(5.0f),
		gravity(0.5f) {

		body.setSize(sf::Vector2f(30, 50));
		body.setPosition(x, y);
		body.setFillColor(sf::Color::Blue);
	}

	void update() {
		velocity.y += gravity;
		body.move(velocity);
		if (body.getPosition().y > 550) {
			body.setPosition(body.getPosition().x, 550);
			velocity.y = 0;
			isOnGround = true;
		}
	}

	void jump() {
		if (isOnGround) {
			velocity.y = -jumpStrength;
			isOnGround = false;
		}
	}

	void moveLeft() {
		velocity.x = -moveSpeed;
	}

	void moveRight() {
		velocity.x = moveSpeed;
	}

	void stopHorizontal() {
		velocity.x = 0;
	}

	sf::FloatRect getBounds() const {
		return body.getGlobalBounds();
	}

	sf::Vector2f getPosition() const {
		return body.getPosition();
	}

	void draw(sf::RenderWindow& window) {
		window.draw(body);
	}

	void setPosition(float x, float y) {
		body.setPosition(x, y);
	}

	void setOnGround(bool onGround) {
		isOnGround = onGround;
	}
};

class Platform {
private:
	sf::RectangleShape shape;
	
public:
	Platform(float x, float y, float width, float height) {
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Green);
	}

	sf::FloatRect getBounds() const {
		return shape.getGlobalBounds();
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(shape);
	}
};

class Coin {
private:
	sf::CircleShape shape;
	bool collected;

public:
	Coin(float x, float y) : collected(false) {
		shape.setRadius(10);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Yellow);
		shape.setOutlineColor(sf::Color(255, 165, 0));
		shape.setOutlineThickness(2);
	}

	bool isCollected() const { return collected; }

	void collect() { collected = true; }

	bool checkCollision(const sf::FloatRect& bounds) {
		if (!collected && shape.getGlobalBounds().intersects(bounds)) {
			collected = true;
			return true;
		}
		return false;
	}

	void draw(sf::RenderWindow& window) const {
		if (!collected) {
			window.draw(shape);
		}
	}
};

class Enemy {
private:
	sf::RectangleShape body;
	float speed;
	float patrolDistance;
	float startX;
	bool movingRight;

public:
	Enemy(float x, float y, float patrolDist = 100.0f) :
		speed(2.0f),
		patrolDistance(patrolDist),
		startX(x),
		movingRight(true) {

		body.setSize(sf::Vector2f(30, 30));
		body.setPosition(x, y);
		body.setFillColor(sf::Color::Red);
	}

	void update() {

		if (movingRight) {
			body.move(speed, 0);
			if (body.getPosition().x > startX + patrolDistance) {
				movingRight = false;
			}
		}
		else {
			body.move(-speed, 0);
			if (body.getPosition().x < startX) {
				movingRight = true;
			}
		}
	}

	sf::FloatRect getBounds() const {
		return body.getGlobalBounds();
	}

	bool checkCollision(const sf::FloatRect& bounds) const {
		return body.getGlobalBounds().intersects(bounds);
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(body);
	}
};

class Game {
private:
	sf::RenderWindow window;
	sf::View camera;
	Player player;
	std::vector<Platform> platforms;
	std::vector<Coin> coins;
	std::vector<Enemy> enemies;
	int score;
	sf::Font font;
	sf::Text scoreText;
	sf::Text gameOverText;
	bool gameOver;

public:
	Game() :
		window(sf::VideoMode(800, 600), "2D Platformer", sf::Style::Close),
		player(100, 300),
		score(0),
		gameOver(false) {

		setupGame();
	}

	void setupGame() {

		camera.setSize(800, 600);
		camera.setCenter(400, 300);

		platforms.push_back(Platform(0, 580, 800, 20));
		platforms.push_back(Platform(100, 450, 200, 20));
		platforms.push_back(Platform(400, 350, 150, 20));
		platforms.push_back(Platform(200, 250, 100, 20));
		platforms.push_back(Platform(500, 200, 200, 20));

		coins.push_back(Coin(150, 400));
		coins.push_back(Coin(450, 300));
		coins.push_back(Coin(250, 200));
		coins.push_back(Coin(550, 150));
		coins.push_back(Coin(350, 100));

		enemies.push_back(Enemy(300, 530, 150));
		enemies.push_back(Enemy(500, 430, 100));

		if (!font.loadFromFile("arial.ttf")) {
			std::cout << "Font not found\n";
			font = sf::Font();
			if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
				std::cout << "System font not found either, text will be invisible\n";
			}
		}

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(10, 10);
		updateScoreText();

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(40);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setPosition(250, 250);
		gameOverText.setString("GAME OVER!\nPress R to restart");

		window.setFramerateLimit(60);
	}

	void updateScoreText() {
		scoreText.setString("Score: " + std::to_string(score));
	}

	void checkCollisions() {
		for (const auto& platform : platforms) {
			sf::FloatRect playerBounds = player.getBounds();
			sf::FloatRect platformBounds = platform.getBounds();

			if (playerBounds.intersects(platformBounds)) {

				playerBounds = player.getBounds();
				float playerBottom = playerBounds.top + playerBounds.height;
				float platformTop = platformBounds.top;

				if (playerBottom > platformTop && playerBottom < platformTop + 20) {
					player.setPosition(player.getPosition().x, platformTop - playerBounds.height);
					player.setOnGround(true);
				}
			}
		}

		for (auto& coin : coins) {
			if (coin.checkCollision(player.getBounds())) {
				score += 10;
					updateScoreText();
			}
		}

		for (const auto& enemy : enemies) {
			if (enemy.checkCollision(player.getBounds())) {
				gameOver = true;
			}
		}
	}

	void updateCamera() {
		sf::Vector2f playerPos = player.getPosition();
		camera.setCenter(playerPos.x + 150, 300);

		if (camera.getCenter().x < 400) camera.setCenter(400, 300);
		if (camera.getCenter().x > 1000) camera.setCenter(1000, 300);
	}

	void restartGame() {
		player = Player(100, 300);
		score = 0;
		gameOver = false;
		updateScoreText();

		coins.clear();
		coins.push_back(Coin(150, 400));
		coins.push_back(Coin(450, 300));
		coins.push_back(Coin(250, 200));
		coins.push_back(Coin(550, 150));
		coins.push_back(Coin(350, 100));
	}

	void handleInput() {
		if (gameOver) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				restartGame();
			}
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.moveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.moveRight();
		}
		else {
			player.stopHorizontal();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.jump();
		}
	}

	void update() {
		if (gameOver) return;

		player.update();

		for (auto& enemy : enemies) {
			enemy.update();
		}

		checkCollisions();
		updateCamera();
	}

	void render() {
		window.clear(sf::Color(135, 206, 235));

		window.setView(camera);

		for (const auto& platform : platforms) {
			platform.draw(window);
		}

		for (const auto& coin : coins) {
			coin.draw(window);
		}

		for (const auto& enemy : enemies) {
			enemy.draw(window);
		}

		player.draw(window);

		window.setView(window.getDefaultView());

		window.draw(scoreText);

		if (gameOver) {
			window.draw(gameOverText);
		}

		window.display();
	}

	void run() {
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			handleInput();
			update();
			render();
		}
	}
};

int main() {
	std::cout << "=== 2D PLATFORMER GAME ===\n";
	std::cout << "Controls:\n";
	std::cout << "A - Move Left\n";
	std::cout << "D - Move Right\n";
	std::cout << "SPACE - Jump\n";
	std::cout << "R - Restart (when game over)\n\n";
	std::cout << "Collect yellow coins (10 points each)\n";
	std::cout << "Avoid red enemies!\n";

	Game game;
	game.run();

	return 0;
}

