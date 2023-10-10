#pragma once
#include "utils.hpp"
#include <SFML/Graphics.hpp>

class C_Object {
private:
	int id;
	std::string name;
	int type;
	sf::RectangleShape rect;
	sf::CircleShape circle;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	std::vector<C_Object> childs;
	C_Object* parent; //its position depends from its parent
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f friction;

public:
	void move(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	void setParent(C_Object* parent); //children list of the parent is incremented from here
	void addChild(C_Object* child); //add a child to the list of children
	void removeChild(C_Object* child); //remove a child from the list of children
	void setName(std::string name);
	void setType(int type);
	void setTexture(std::string path);
	void setSize(sf::Vector2f size);
	void setVelocity(sf::Vector2f velocity);
	void setFriction(sf::Vector2f friction);
	void setID(int id);
	int getID();
	std::string getName();
	int getType();
	sf::CircleShape getCircle();
	sf::RectangleShape getRect();
	std::vector<C_Object> getChilds();
	C_Object* getParent();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getFriction();
	sf::Vector2f getSize();
};