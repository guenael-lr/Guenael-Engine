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

	for (int i = 0; i < list_spikes.size(); i++)
		list_spikes[i].draw(gameWindow);

	player.draw(gameWindow);
	textCollectibles.setString("Kouquiz : " + std::to_string(collectibles) + " / " + std::to_string(totalCollectibles));
	gameWindow.draw(textCollectibles);
	gameWindow.display();
}

void C_Game_Example::checkCollision() {
	for (int i = 0; i < list_collection.size(); i++) {
		if (player.getRect().getGlobalBounds().intersects(list_collection[i].getRect().getGlobalBounds())) {
			++collectibles;
			list_collection[0].playActionSound();
			list_collection[i].move(sf::Vector2f(10000.f, 10000.f));
		}
	}
	for (int i = 0; i < list_spikes.size(); i++) {
		if (player.getRect().getGlobalBounds().intersects(list_spikes[i].getRect().getGlobalBounds())) {
			soundDeath.play();
			this->restart();
			gameWindow.close();
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
	
	
	if (player.getVelocity().y >= 0) {
		player.setVelocity(sf::Vector2f(player.getVelocity().x * player.getFriction().x, (player.getVelocity().y + player.getGravity()) * player.getFriction().y));
		player_isJumping = false;
	}
	else
		player.setVelocity(sf::Vector2f(player.getVelocity().x * player.getFriction().x *1.2, (player.getVelocity().y + player.getGravity()) * player.getFriction().y));
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
	for (int i = 0; i < list_spikes.size(); i++) {
		list_spikes[i].translate(list_spikes[i].getVelocity());
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
		for (int i = 0; i < list_spikes.size(); i++) {
			list_spikes[i].move(list_spikes[i].getPosition() - movement);
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
		for (int i = 0; i < list_spikes.size(); i++) {
			list_spikes[i].move(list_spikes[i].getPosition() - movement);
		}
		player.move(player.getPosition() - movement);
	}

	//camera joueur hauteur
	if (player.getPosition().y < 300.f) {
		movement = sf::Vector2f(0.f, player.getPosition().y - 300.f);

		//move every object in the list to the bottom
		for (int i = 0; i < list_collection.size(); i++) {
			list_collection[i].move(list_collection[i].getPosition() - movement);
		}
		for (int i = 0; i < list_platform.size(); i++) {
			list_platform[i].move(list_platform[i].getPosition() - movement);
		}
		for (int i = 0; i < list_flags.size(); i++) {
			list_flags[i].move(list_flags[i].getPosition() - movement);
		}
		for (int i = 0; i < list_spikes.size(); i++) {
			list_spikes[i].move(list_spikes[i].getPosition() - movement);
		}
		player.move(player.getPosition() - movement);
	}

	if (player.getPosition().y > SCREEN_HEIGHT - 300.f) {
		movement = sf::Vector2f(0.f, player.getPosition().y - (SCREEN_HEIGHT - 300.f));

		//move every object in the list to the top
		for (int i = 0; i < list_collection.size(); i++) {
			list_collection[i].move(list_collection[i].getPosition() - movement);
		}
		for (int i = 0; i < list_platform.size(); i++) {
			list_platform[i].move(list_platform[i].getPosition() - movement);
		}
		for (int i = 0; i < list_flags.size(); i++) {
			list_flags[i].move(list_flags[i].getPosition() - movement);
		}
		for (int i = 0; i < list_spikes.size(); i++) {
			list_spikes[i].move(list_spikes[i].getPosition() - movement);
		}
		player.move(player.getPosition() - movement);
	}

	//set the player texture by the velocity
	if (player.getVelocity().x > 0.1)
		player.setTexture("Assets/Images/runright1.png");
	else if (player.getVelocity().x < -0.1)
		player.setTexture("Assets/Images/runleft1.png");
	else
		player.setTexture("Assets/Images/idle.png");

	//same for jumping
	if (player_isJumping)
		if (player.getVelocity().y < 0)
			player.setTexture("Assets/Images/jump.png");
		else
			player.setTexture("Assets/Images/idle.png");


}


void C_Game_Example::restart() {
	//restart the game 
	isRunning = false;
	collectibles = 0;
	totalCollectibles = 0;
	player_isJumping = false;
	player_isOnGround = false;
	//reset all the lists
	list_platform.clear();
	list_collection.clear();
	list_flags.clear();
	list_spikes.clear();
}

void C_Game_Example::initExample() {
	//create window
	if (isRunning == false) {

		gameWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

		const char* map[8] = {
			"########################################################################",
			"############################################S##########################F",
			"B#######################B#B#S##############BB#C##B###############CC###BB",
			"B#######C##C########C#B#B#B#B###C#####C###BBBBBBBBB#######C#####BBBB####",
			"B######BBBBBB#######B#B#B#B#B###B#####B##################BBBB###########",
			"B#P#S####C####S###B#B#B#B#B#B#B#B##B##S#C####C#SS##C#####SSSS#####C#####",
			"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
			"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		};

		for(int i = 0; i < 8; ++i)
			for(int j = 0; j < 76; ++j)
				switch (map[i][j]) {
					case 'B':
						list_platform.push_back(C_Object());
						list_platform[list_platform.size() - 1].setID(10 + list_platform.size() - 1);
						list_platform[list_platform.size() - 1].setName("Platform " + std::to_string(list_platform.size() - 1));
						list_platform[list_platform.size() - 1].setType(2);
						list_platform[list_platform.size() - 1].setTexture("Assets/Images/platform.png");
						list_platform[list_platform.size() - 1].setSize(sf::Vector2f(50.f, 50.f));
						list_platform[list_platform.size() - 1].setFriction(sf::Vector2f(0.8f, 1.f));
						list_platform[list_platform.size() - 1].setVelocity(sf::Vector2f(0.f, 0.f));
						list_platform[list_platform.size() - 1].move(sf::Vector2f(j * 50.f, i * 50.f));
						list_platform[list_platform.size() - 1].setGravity(0.f);
						break;
					case 'C':
						list_collection.push_back(C_Object());
						list_collection[list_collection.size() - 1].setID(100 + list_collection.size() - 1);
						list_collection[list_collection.size() - 1].setName("Cookie " + std::to_string(list_collection.size() - 1));
						list_collection[list_collection.size() - 1].setType(1);
						list_collection[list_collection.size() - 1].setTexture("Assets/Images/cookie.png");
						list_collection[list_collection.size() - 1].setSize(sf::Vector2f(50.f, 50.f));
						list_collection[list_collection.size() - 1].setFriction(sf::Vector2f(0.8f, 1.f));
						list_collection[list_collection.size() - 1].setVelocity(sf::Vector2f(0.f, 0.f));
						list_collection[list_collection.size() - 1].move(sf::Vector2f(j * 50.f, i * 50.f));
						list_collection[list_collection.size() - 1].setGravity(0.f);
						
						++totalCollectibles;
						break;
					case 'P':
						player.setID(1);
						player.setName("Player 1");
						player.setType(3);
						player.setTexture("Assets/Images/idle.png");
						player.setSize(sf::Vector2f(40.f, 40.f));
						player.setFriction(sf::Vector2f(0.8f, 1.f));
						player.setVelocity(sf::Vector2f(0.f, 0.f));
						player.move(sf::Vector2f(j * 50.f, i * 50.f));
						player.setGravity(1.f);
						player.setJumpSound("Assets/Sounds/jump.mp3");
						break;
					case 'F':
						list_flags.push_back(C_Object());
						list_flags[list_flags.size() - 1].setID(1000 + list_flags.size() - 1);
						list_flags[list_flags.size() - 1].setName("Flag");
						list_flags[list_flags.size() - 1].setType(4);
						list_flags[list_flags.size() - 1].setTexture("Assets/Images/finish.png");
						list_flags[list_flags.size() - 1].setSize(sf::Vector2f(50.f, 50.f));
						list_flags[list_flags.size() - 1].setFriction(sf::Vector2f(0.8f, 1.f));
						list_flags[list_flags.size() - 1].setVelocity(sf::Vector2f(0.f, 0.f));
						list_flags[list_flags.size() - 1].move(sf::Vector2f(j * 50.f, i * 50.f));
						list_flags[list_flags.size() - 1].setGravity(0.f);
						break;
					case 'S':
						list_spikes.push_back(C_Object());
						list_spikes[list_spikes.size() - 1].setID(10000 + list_spikes.size() - 1);
						list_spikes[list_spikes.size() - 1].setName("Spike " + std::to_string(list_spikes.size() - 1));
						list_spikes[list_spikes.size() - 1].setType(5);
						list_spikes[list_spikes.size() - 1].setTexture("Assets/Images/spike.png");
						list_spikes[list_spikes.size() - 1].setSize(sf::Vector2f(30.f, 25.f));
						list_spikes[list_spikes.size() - 1].setFriction(sf::Vector2f(0.8f, 1.f));
						list_spikes[list_spikes.size() - 1].setVelocity(sf::Vector2f(0.f, 0.f));
						list_spikes[list_spikes.size() - 1].move(sf::Vector2f(j * 50.f, i * 50.f + 30.f));
						list_spikes[list_spikes.size() - 1].setGravity(0.f);
						break;
				}
		list_collection[0].setActionSound("Assets/Sounds/collect.mp3");

	}
	isRunning = true;
}