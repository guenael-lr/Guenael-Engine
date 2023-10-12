#include "Game.hpp"

C_Game::C_Game() {
	isRunning = false;
}

bool C_Game::getIsRunning() {
	return isRunning;
}

void C_Game::setRunning() {
	if(isRunning == false)
		gameWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	isRunning = true;
}


void C_Game::run(std::vector<C_Object> *list_objects) {
	//make background light blue
	
	sf::Event event;
	while (gameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isRunning = false;
			gameWindow.close();
		}
	}
	gameWindow.clear(sf::Color(135, 206, 250));
	//gameWindow.draw(scene.getSprite());
	for (int i = 0; i < (*list_objects).size(); i++) {
		(*list_objects)[i].draw(gameWindow);
	}
	gameWindow.display();
}