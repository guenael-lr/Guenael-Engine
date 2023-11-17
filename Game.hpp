#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"
//create a class C_Game with its own window that will run the game with the physic and the sounds
class C_Game {
	private:
		sf::RenderWindow gameWindow;
		bool isRunning;
		C_Object player;
		std::vector<C_Object> list_platform;
		std::vector<C_Object> list_collection;
		std::vector<C_Object> list_flags;

		bool player_isJumping = false;
		bool player_isOnGround = false;

		int collectibles = 0;
		int totalCollectibles = 0;

		sf::Text textCollectibles;
		sf::Font font;
		
	public:
		C_Game();
		bool getIsRunning();
		void setRunning(std::vector<C_Object>* list_objects);
		void getObjects(std::vector<C_Object> *list_objects);
		void run();
		void applyPhysics();
		void checkCollision();
		void restart();
};