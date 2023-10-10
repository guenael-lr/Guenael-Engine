#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"

class C_Hierarchy {
private:
	sf::RectangleShape rect;
	sf::Text Title;
	std::vector<sf::RectangleShape> Buttons;
	std::vector<sf::Text> ButtonText;
	std::vector<int> ButtonID;
	sf::Font font;
	int button = 0;

public:
	C_Hierarchy();
	void update(sf::RenderWindow& window);
	void listElement(std::vector<C_Object>);
	int hoverListElement(sf::Vector2i mouse_pos); //returns the Id of the object
	void removeListElement(int id);
};

