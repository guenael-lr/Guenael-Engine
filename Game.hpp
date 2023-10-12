#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"
//create a class C_Game with its own window that will run the game with the physic and the sounds
class C_Game {
	private:
		sf::RenderWindow gameWindow;
		bool isRunning;
		
	public:
		C_Game();
		bool getIsRunning();
		void setRunning();
		void run(std::vector<C_Object> *list_objects);
};