#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"

class C_Scene {
private:
	sf::RectangleShape rect;
	sf::Text Title;
	sf::Font font;
	sf::RectangleShape reSizeObject;

	std::vector<C_Object> list_objects;
	int size_list_obj = 0;

	int prev_button_state = 0;
	sf::Vector2i lastMousePos;
	int idObject = 0;

public:
	C_Scene();
	void FloatObject(int Button, sf::Vector2i mouse_pos);
	void update(sf::RenderWindow& window);
	void drawObjects(sf::RenderWindow& window);
	std::vector<C_Object> getListObjects() { return list_objects; }
	void drawReSizeObject(int idObject);
	void removeObject(int idObject);
};