#pragma once

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "Object.hpp"

class C_Scene {
private:
	sf::RectangleShape rect;
	sf::Text Title;
	sf::Text Play;
	sf::Font font;
	sf::RectangleShape reSizeObject;
	sf::RectangleShape reSizeObject_corner[4];

	const std::string types_name[4] = { "collectible", "platform", "player", "finish" };

	int size_list_obj = 0;

	int prev_button_state = 0;
	sf::Vector2i lastMousePos;
	int idObject = 0;

public:
	std::vector<C_Object> list_objects;
	C_Scene();
	bool buttonPlay(sf::Vector2i mouse_pos);
	void FloatObject(int Button, sf::Vector2i mouse_pos);
	void update(sf::RenderWindow& window);
	void drawObjects(sf::RenderWindow& window);
	std::vector<C_Object>* getListObjects() { return &list_objects; }
	void drawReSizeObject(int idObject);
	void removeObject(int idObject);
	int reSizeObjectFunc(int idObject, sf::Vector2i mouse_pos);
	int moveObject(int idObject, sf::Vector2i mouse_pos);
};