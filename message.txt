#include "utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>


const float COEFF_WINDOW = 7 * 10;
const float SCREEN_WIDTH = 16* COEFF_WINDOW;
const float SCREEN_HEIGHT = 9* COEFF_WINDOW;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Simple Platformer");

sf::Texture playerTexture;
sf::Sprite playerSprite;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

sf::RectangleShape * basePlatform;
sf::RectangleShape* playerHitbox;

bool isRunning = true;
sf::Event event;


sf::Vector2f player_pos = sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
sf::Vector2f player_velocity = sf::Vector2f(0.f, 0.f);

float gravity = 0.75f;
sf::Vector2f friction = sf::Vector2f(0.99f, .99f);
//on glisse legerement en X et pas en Y


std::string playerTexturePath = "Assets/perso-face.png";
std::string backgroundTexturePath = "Assets/background.png";
void close();
void updatePhysic();

bool isJumping = false;
bool isOnGround = false;
bool resetPosition = false;
float vel_jump = 0.f;

void init() {

	//player texture load from assets
	std::cout << playerTexturePath << std::endl;
	playerTexture.loadFromFile(playerTexturePath);
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2.f, playerSprite.getGlobalBounds().height / 2.f);
	playerSprite.setScale(3.f, 3.f);

	playerHitbox = new sf::RectangleShape();
	sf::Vector2f coeffHitBoxPlayer = sf::Vector2f(70.f, 30.f);
	playerHitbox->setSize(sf::Vector2f(playerSprite.getGlobalBounds().width - coeffHitBoxPlayer.x, playerSprite.getGlobalBounds().height - coeffHitBoxPlayer.y));
	playerHitbox->setOutlineColor(sf::Color::Red);
	playerHitbox->setFillColor(sf::Color::Transparent);
	playerHitbox->setPosition(playerSprite.getPosition());
	playerHitbox->setOutlineThickness(1.f);
	playerHitbox->setOrigin(sf::Vector2f(playerHitbox->getGlobalBounds().width / 2.f, playerHitbox->getGlobalBounds().height / 2.f));
	
	backgroundTexture.loadFromFile(backgroundTexturePath);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(SCREEN_WIDTH / float(backgroundTexture.getSize().x),SCREEN_HEIGHT / float(backgroundTexture.getSize().y));

	basePlatform = new sf::RectangleShape();
	basePlatform->setSize(sf::Vector2f(SCREEN_WIDTH/2, 100));
	basePlatform->setFillColor(sf::Color::Green);
	basePlatform->setPosition(sf::Vector2f(SCREEN_HEIGHT/2, 3*SCREEN_HEIGHT/4));
}

void update() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isRunning = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		player_velocity.x = -.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		player_velocity.x = .5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
		isJumping = true;
		if (isOnGround) {
			isOnGround = false;
			vel_jump = .5f;
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		resetPosition = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		close();


	// Handle collision between player and basePlateform
	if (playerHitbox->getGlobalBounds().intersects(basePlatform->getGlobalBounds())) {
		isOnGround = true;
	} else {
		isOnGround = false;
	}

	// Calculate the position based on the velocity
	updatePhysic();
	playerSprite.setPosition(player_pos);
	if (resetPosition) {
		resetPosition = false;
		player_pos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3);
		player_velocity = sf::Vector2f(0.f, 0.f);
	}

	playerHitbox->setPosition(playerSprite.getPosition());

	window.clear();
	window.draw(backgroundSprite);
	window.draw(playerSprite);
	window.draw(*basePlatform);
	window.draw(*playerHitbox);
	window.display();
}

void updatePhysic() {
	if (!isOnGround) {
		if (vel_jump > 0.1f) {
			vel_jump *= friction.y;
			player_velocity.y -= vel_jump;
		}
		else
			vel_jump = 0.f;

		if (player_velocity.y + gravity < gravity)
			player_velocity.y += gravity;
		else
			player_velocity.y = gravity;
		
	} else if (!isJumping) {
		player_velocity.y = 0;
	}
	isJumping = false;
	

	player_velocity.x *= friction.x;
	player_velocity.y *= friction.y;
	player_pos += player_velocity;
}


void close() {
	window.close();
	exit(0);
}

int main() {
	bool isRunning = true;
	init();
	while (isRunning) {

		//update at 60Hz
		update();
	}
	close();
	return 0;
}