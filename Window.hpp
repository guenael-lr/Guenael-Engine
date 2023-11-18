#pragma once
//class for the main window
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "utils.hpp"
#include "Inspector.hpp"
#include "Project.hpp"
#include "Hierarchy.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "ExampleLevel.hpp"

class C_Window {

	protected :
		sf::RenderWindow window;
		bool isRunning;	
		C_Scene* Scene = new C_Scene;
		C_Inspector* Inspector = new C_Inspector;
		C_Project* Project = new C_Project;
		C_Hierarchy* Hierarchy = new C_Hierarchy;
		C_Game* Game = new C_Game;
		C_Game_Example* GameExample = new C_Game_Example;
		sf::Vector2i state_Button_Mouse;
		sf::Vector2i prev_state_Button_Mouse;
		sf::Vector2i mouse_pos;
		int selection_Hierarchy;

	public :
		C_Window();
		bool getIsRunning();
		void update();
		void FixedUpdate();
		void quit();
		void run();
};
