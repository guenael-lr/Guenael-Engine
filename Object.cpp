#include "Object.hpp"

void C_Object::move(sf::Vector2f pos) {
	position = pos;
	rect.setPosition(pos);
}

void C_Object::draw(sf::RenderWindow& window) {
	if(type == 1)
		rect.setTexture(&texture);
	window.draw(rect);
}

void C_Object::setParent(C_Object* parent) {
	this->parent = parent;
}

void C_Object::addChild(C_Object* child) {
	childs.push_back(*child);
}

void C_Object::removeChild(C_Object* child) {
	for (int i = 0; i < childs.size(); ++i) {
		if (childs[i].getName() == child->getName()) {
			childs.erase(childs.begin() + i);
			return;
		}
	}
}

void C_Object::setName(std::string name) {
	this->name = name;
}

void C_Object::setType(int type) {
	this->type = type;
	rect = sf::RectangleShape(); 
	//rect.setFillColor(sf::Color::Blue);
	texture = sf::Texture();
	
	if (type == 1)
		texture.loadFromFile("Assets/Images/cookie.png");
	else if (type == 2)
		texture.loadFromFile("Assets/Images/plateform.png");
	else if (type == 3)
		texture.loadFromFile("Assets/Images/player.png");
	else
		texture.loadFromFile("Assets/Images/finish.png");
		
	rect.setTexture(&texture);
}

void C_Object::setTexture(std::string path) {
	texture = sf::Texture();
	texture.loadFromFile(path);
	sprite = sf::Sprite();
	sprite.setTexture(texture);
}

void C_Object::setSize(sf::Vector2f size) {
	rect.setSize(size);
	this->size = size;
}

void C_Object::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

void C_Object::setFriction(sf::Vector2f friction) {
	this->friction = friction;
}

void C_Object::setID(int id) {
	this->id = id;
}

int C_Object::getID() {
	return id;
}


std::string C_Object::getName() {
	return name;
}

int C_Object::getType() {
	return type;
}

std::vector<C_Object> C_Object::getChilds() {
	return childs;
}

C_Object* C_Object::getParent() {
	return parent;
}

sf::Vector2f C_Object::getPosition() {
	return position;
}

sf::Vector2f C_Object::getSize() {

	return size;
}

sf::Vector2f C_Object::getVelocity() {
	return velocity;
}

sf::Vector2f C_Object::getFriction() {
	return friction;
}

sf::RectangleShape C_Object::getRect() {
	return rect;
}

void C_Object::setRotation(sf::Vector2f rotation) {
	rect.setRotation(rotation.x);
	this->rotation = rotation;
}

sf::Vector2f C_Object::getRotation() {
	return rotation;
}

void C_Object::setGravity(float gravity) {
	this->gravity = gravity;
}

float C_Object::getGravity() {
	return gravity;
}



