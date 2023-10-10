#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"

class C_Project {
private:
	const int List_Button_Size = 3;
	sf::RectangleShape rect;
	sf::Text Title;
	sf::RectangleShape List_Button[3];
	sf::Text List_Text[3];
	sf::Font font;
	const std::string List_Button_Text[3] = { "circle", "rectangle", "player" };
	int Button = 0;
	


public:
	C_Project();
	void update(sf::RenderWindow& window);
	int isHoverAButton(sf::Vector2i mouse_pos);
	int getButton() { return Button; } 
};