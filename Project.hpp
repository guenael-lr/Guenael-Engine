#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"

class C_Project {
private:
	const int List_Button_Size = 4;
	sf::RectangleShape rect;
	sf::Text Title;
	std::vector<sf::RectangleShape> List_Button;
	std::vector<sf::Text> List_Text;
	sf::Font font;
	const std::string List_Button_Text[4] = { "collectible", "platform", "player", "finish"};
	int Button = 0;
	


public:
	C_Project();
	void update(sf::RenderWindow& window);
	int isHoverAButton(sf::Vector2i mouse_pos);
	int getButton() { return this->Button; } 
};