#pragma once
#include "utils.hpp"
#include <SFML/Graphics.hpp>

class C_Object {
private:
	int id;
	std::string name;
	std::string pathTexture;
	int type;
	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	std::vector<C_Object> childs;
	C_Object* parent; //its position depends from its parent
	sf::Vector2f position;
	sf::Vector2f rotation;
	sf::Vector2f velocity;
	sf::Vector2f friction;
	float gravity = 0;

public:
	void move(sf::Vector2f pos);
	void translate(sf::Vector2f plus);
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
	void setGravity(float gravity);
	void setRotation(sf::Vector2f rotation);
	void setID(int id);
	int getID();
	std::string getName();
	std::string getPathTexture();
	int getType();
	sf::RectangleShape getRect();
	std::vector<C_Object> getChilds();
	C_Object* getParent();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getFriction();
	sf::Vector2f getSize();
	sf::Vector2f getRotation();
	float getGravity();
	
};