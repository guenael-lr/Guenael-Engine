#include "ExampleLevel.hpp"

C_Game_Example::C_Game_Example() {
	isRunning = false;
	player_isJumping = false;
	player_isOnGround = false;
	bufferWin.loadFromFile("Assets/Sounds/win.mp3");
	soundWin.setBuffer(bufferWin);
	bufferDeath.loadFromFile("Assets/Sounds/death.mp3");
	soundDeath.setBuffer(bufferDeath);
	//load the font and the text
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		std::cout << "pas youpi" << std::endl;;

	textCollectibles.setFont(font);
	textCollectibles.setString("Kouquiz : " + std::to_string(collectibles) + " / " + std::to_string(totalCollectibles));
	textCollectibles.setCharacterSize(24);
	textCollectibles.setFillColor(sf::Color::Black);
	textCollectibles.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - textCollectibles.getGlobalBounds().width / 2, textCollectibles.getGlobalBounds().height / 2 + 2));

}

bool C_Game_Example::getIsRunning() {
	return isRunning;
}

void C_Game_Example::run() {
	//make background light blue
	if (!isRunning)
		return;



	sf::Event event;
	while (gameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isRunning = false;
			this->restart();
			gameWindow.close();
		}

		//move player velocity with the keyboard arrows
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player.setVelocity(sf::Vector2f(10.0f, player.getVelocity().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player.setVelocity(sf::Vector2f(-10.0f, player.getVelocity().y));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player_isOnGround) {
			player.playJumpSound();
			player_isJumping = true;
			player_isOnGround = false;
			player.setVelocity(sf::Vector2f(player.getVelocity().x, -15.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			player.setVelocity(sf::Vector2f(player.getVelocity().x * 2, player.getVelocity().y));
	}
	gameWindow.clear(sf::Color(135, 206, 250));
	this->applyPhysics();

	//draw all the lists of the C_Game_Example
	for (int i = 0; i < list_collection.size(); i++)
		list_collection[i].draw(gameWindow);

	for (int i = 0; i < list_platform.size(); i++)
		list_platform[i].draw(gameWindow);

	for (int i = 0; i < list_flags.size(); i++)
		list_flags[i].draw(gameWindow);

	player.draw(gameWindow);
	textCollectibles.setString("Kouquiz : " + std::to_string(collectibles) + " / " + std::to_string(totalCollectibles));
	gameWindow.draw(textCollectibles);
	gameWindow.display();
}

void C_Game_Example::checkCollision() {
	for (int i = 0; i < list_collection.size(); i++) {
		if (player.getRect().getGlobalBounds().intersects(list_collection[i].getRect().getGlobalBounds())) {
			++collectibles;
			list_collection[i].playActionSound();
			list_collection[i].move(sf::Vector2f(10000.f, 10000.f));
		}
	}
	for (int i = 0; i < list_platform.size(); i++) {
		if (player.getRect().getGlobalBounds().intersects(list_platform[i].getRect().getGlobalBounds())) {
			if (!player_isJumping && player.getPosition().y + player.getRect().getGlobalBounds().height < list_platform[i].getPosition().y + list_platform[i].getRect().getGlobalBounds().height / 3) {
				player.setVelocity(sf::Vector2f(player.getVelocity().x, 0));
				player.move(sf::Vector2f(player.getPosition().x, list_platform[i].getPosition().y + 5.f - player.getRect().getGlobalBounds().height));
				player_isOnGround = true;
			}
			else if (!player_isJumping)
				if (player.getPosition().x > list_platform[i].getPosition().x) {
					player.setVelocity(-player.getVelocity() / 2.f);
					player.move(sf::Vector2f(player.getPosition().x + 10.f, player.getPosition().y));
				}
				else if (player.getPosition().x < list_platform[i].getPosition().x) {
					player.move(sf::Vector2f(player.getPosition().x - 10.f, player.getPosition().y));
					player.setVelocity(sf::Vector2f(-player.getVelocity().x / 2.f, player.getVelocity().y));
				}
			//player->setIsJumping(false);
		}
	}
	for (int i = 0; i < list_flags.size(); i++) {
		if (player.getRect().getGlobalBounds().intersects(list_flags[i].getRect().getGlobalBounds())) {
			if (collectibles == totalCollectibles) {
				soundWin.play();
				this->restart();
				gameWindow.close();
			}
		}
	}
}

void C_Game_Example::applyPhysics() {
	player.setVelocity(sf::Vector2f(player.getVelocity().x * player.getFriction().x, (player.getVelocity().y + player.getGravity()) * player.getFriction().y));
	if (player.getVelocity().y > 0)
		player_isJumping = false;
	this->checkCollision();

	for (int i = 0; i < list_collection.size(); i++) {
		list_collection[i].translate(list_collection[i].getVelocity());
	}
	for (int i = 0; i < list_platform.size(); i++) {
		list_platform[i].translate(list_platform[i].getVelocity());
	}
	for (int i = 0; i < list_flags.size(); i++) {
		list_flags[i].translate(list_flags[i].getVelocity());
	}
	player.translate(player.getVelocity());

	if (player.getPosition().y > 3000) {
		soundDeath.play();
		this->restart();
		gameWindow.close();
	}

	//camera follow the player
	sf::Vector2f movement = sf::Vector2f(0.f, 0.f);
	if (player.getPosition().x < 500.f) {
		movement = sf::Vector2f(player.getPosition().x - 500.f, 0.f);

		//move every object in the list to the right
		for (int i = 0; i < list_collection.size(); i++) {
			list_collection[i].move(list_collection[i].getPosition() - movement);
		}
		for (int i = 0; i < list_platform.size(); i++) {
			list_platform[i].move(list_platform[i].getPosition() - movement);
		}
		for (int i = 0; i < list_flags.size(); i++) {
			list_flags[i].move(list_flags[i].getPosition() - movement);
		}
		player.move(player.getPosition() - movement);
	}

	if (player.getPosition().x > SCREEN_WIDTH - 500.f) {
		movement = sf::Vector2f(player.getPosition().x - (SCREEN_WIDTH - 500.f), 0.f);

		//move every object in the list to the left
		for (int i = 0; i < list_collection.size(); i++) {
			list_collection[i].move(list_collection[i].getPosition() - movement);
		}
		for (int i = 0; i < list_platform.size(); i++) {
			list_platform[i].move(list_platform[i].getPosition() - movement);
		}
		for (int i = 0; i < list_flags.size(); i++) {
			list_flags[i].move(list_flags[i].getPosition() - movement);
		}
		player.move(player.getPosition() - movement);
	}




}


void C_Game_Example::restart() {
	//restart the game 
	isRunning = false;
	collectibles = 0;
	player_isJumping = false;
	player_isOnGround = false;
}

void C_Game_Example::initExample() {
	//create window
	if (isRunning == false) {

		gameWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

		//create player
		player.setID(1);
		player.setName("Player 1");
		player.setType(3);
		player.setTexture("Assets/Images/player.png");
		player.setSize(sf::Vector2f(50.f, 50.f));
		player.setFriction(sf::Vector2f(0.8f, 1.f));
		player.setVelocity(sf::Vector2f(0.f, 0.f));
		player.move(sf::Vector2f(100.f, 100.f));
		player.setGravity(1.f);
		player.setJumpSound("Assets/Sounds/jump.mp3");

		//create platforms in a strait line 
		for (int i = 0; i < 40; ++i) {
			list_platform.push_back(C_Object());
			list_platform[i].setID(1 + i);
			list_platform[i].setName("Platform " + std::to_string(i));
			list_platform[i].setType(2);
			list_platform[i].setTexture("Assets/Images/platform.png");
			list_platform[i].setSize(sf::Vector2f(50.f, 50.f));
			list_platform[i].setFriction(sf::Vector2f(0.8f, 1.f));
			list_platform[i].setVelocity(sf::Vector2f(0.f, 0.f));
			list_platform[i].move(sf::Vector2f( (i - 10) * 50.f, 500.f));
			list_platform[i].setGravity(0.f);
		}

		//create collectibles in a strait line

		for (int i = 0; i < 10; ++i) {
			list_collection.push_back(C_Object());
			list_collection[i].setID(1 + 15 + i);
			list_collection[i].setName("Cookie " + std::to_string(i));
			list_collection[i].setType(1);
			list_collection[i].setTexture("Assets/Images/cookie.png");
			list_collection[i].setSize(sf::Vector2f(50.f, 50.f));
			list_collection[i].setFriction(sf::Vector2f(0.8f, 1.f));
			list_collection[i].setVelocity(sf::Vector2f(0.f, 0.f));
			list_collection[i].move(sf::Vector2f(50.f + i * 100.f, 400.f));
			list_collection[i].setGravity(0.f);
			++totalCollectibles;
		}

		//create flag at the end of the level
		list_flags.push_back(C_Object());
		list_flags[0].setID(1 + 15 + 10 + 1);
		list_flags[0].setName("Flag");
		list_flags[0].setType(4);
		list_flags[0].setTexture("Assets/Images/finish.png");
		list_flags[0].setSize(sf::Vector2f(50.f, 50.f));
		list_flags[0].setFriction(sf::Vector2f(0.8f, 1.f));
		list_flags[0].setVelocity(sf::Vector2f(0.f, 0.f));
		list_flags[0].move(sf::Vector2f(29 * 50.f, 450.f));
		list_flags[0].setGravity(0.f);
	}
	isRunning = true;
}