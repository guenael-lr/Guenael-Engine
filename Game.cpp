#include "Game.hpp"

C_Game::C_Game() {
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

bool C_Game::getIsRunning() {
	return isRunning;
}

void C_Game::setRunning(std::vector<C_Object>* list_objects) {
	if (isRunning == false) {
		gameWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
		this->getObjects(list_objects);
	}
	isRunning = true;
}


void C_Game::run() {
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		player.setVelocity(sf::Vector2f(player.getVelocity().x * 2, player.getVelocity().y));
	}
	gameWindow.clear(sf::Color(135, 206, 250));
	this->applyPhysics();
	
	//draw all the lists of the C_game
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

void C_Game::getObjects(std::vector<C_Object> *list_objects) {
	int type = 0;
	list_collection.clear();
	totalCollectibles = 0;
	list_flags.clear();
	list_platform.clear();
	for (int i = 0; i < (*list_objects).size(); i++) {
		type = (*list_objects)[i].getType();
		if (type == 1) {
			++totalCollectibles;
			list_collection.push_back((*list_objects)[i]);

		}
		else if (type == 2)
			list_platform.push_back((*list_objects)[i]);
		else if (type == 4)
			list_flags.push_back((*list_objects)[i]);
		else if (type == 3)
			player = (*list_objects)[i];

	
	}
}

void C_Game::checkCollision() {
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
				player.move(sf::Vector2f(player.getPosition().x,list_platform[i].getPosition().y + 5.f - player.getRect().getGlobalBounds().height));
				player_isOnGround = true;
			}
			else if(!player_isJumping)
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

void C_Game::applyPhysics() {	
	if (player.getVelocity().y >= 0) {
		player.setVelocity(sf::Vector2f(player.getVelocity().x * player.getFriction().x, (player.getVelocity().y + player.getGravity()) * player.getFriction().y));
		player_isJumping = false;
	}
	else
		player.setVelocity(sf::Vector2f(player.getVelocity().x * player.getFriction().x * 1.2, (player.getVelocity().y + player.getGravity()) * player.getFriction().y));
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
	//tout changer
	//player->getVelocity().x *= player->getFriction().x;
	//player->getVelocity().y *= player->getFriction().y;
	//player->move(player->getVelocity()); //change to translate
}


void C_Game::restart() {
	//restart the game 
	isRunning = false;
	collectibles = 0;
	player_isJumping = false;
	player_isOnGround = false;
}