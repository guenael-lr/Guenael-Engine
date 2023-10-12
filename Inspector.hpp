#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"

class C_Inspector {
private : 
	sf::RectangleShape rect;
	sf::Text Title;
	sf::Font font;

	std::vector<sf::Text> List_Text;
	std::vector<sf::Text> List_Value;
	std::vector<sf::RectangleShape> List_Button;
	sf::RenderWindow windowInspector;

public : 
	C_Inspector();
	void update(sf::RenderWindow &window);
	void Inspect(std::vector<C_Object> list_object, int id);
	std::string changeValue(sf::Vector2i mouse_pos);
	void changeValueObject(std::vector<C_Object> *list_object, int id, std::string value);
};