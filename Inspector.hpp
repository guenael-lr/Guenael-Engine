#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"

class C_Inspector {
private : 
	sf::RectangleShape rect;
	sf::Text Title;
	sf::Font font;

public : 
	C_Inspector();
	void update(sf::RenderWindow &window);
};