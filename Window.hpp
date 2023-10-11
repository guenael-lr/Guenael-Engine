#pragma once
//class for the main window
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "utils.hpp"
#include "Inspector.hpp"
#include "Project.hpp"
#include "Hierarchy.hpp"
#include "Scene.hpp"

class C_Window {

	protected :
		sf::RenderWindow window;
		bool isRunning;	
		C_Inspector* Inspector;
		C_Project* Project;
		C_Hierarchy* Hierarchy;
		C_Scene* Scene;
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
