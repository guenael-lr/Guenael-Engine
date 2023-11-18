#include "Object.hpp"

void C_Object::move(sf::Vector2f pos) {
	position = pos;
	rect.setPosition(pos);
}

void C_Object::draw(sf::RenderWindow& window) {
	rect.setTexture(&texture);
	window.draw(rect);
}

void C_Object::setName(std::string name) {
	this->name = name;
}

void C_Object::setType(int type) {
	this->type = type;
	rect = sf::RectangleShape(); 
	//rect.setFillColor(sf::Color::Blue);
	this->setTexture("Assets/Images/default.png");
	this->setGravity(0.f);
	this->pathSoundAction = "None";
	this->pathSoundJump = "None";
	if (type == 3) {
		this->setGravity(1.f);
		this->pathSoundAction = "Not used";
	}
	else
		this->pathSoundJump = "Not used";
}

void C_Object::setTexture(std::string path) {
	pathTexture = path;
	texture = sf::Texture();
	texture.loadFromFile(path);
	rect.setTexture(&texture);
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

void C_Object::translate(sf::Vector2f plus) {
	 this->position += plus;
	rect.setPosition(this->position);
}

std::string C_Object::getPathTexture() {
	return pathTexture;
}

void C_Object::setJumpSound(std::string path) {
	pathSoundJump = path;
	bufferJump.loadFromFile(path);
	jumpSound.setBuffer(bufferJump);
}

void C_Object::setActionSound(std::string path) {
	pathSoundAction = path;
	bufferAction.loadFromFile(path);
	actionSound.setBuffer(bufferAction);
}

std::string C_Object::getJumpSoundPath() {
	return pathSoundJump;
}

std::string C_Object::getActionSoundPath() {
	return pathSoundAction;
}

void C_Object::playJumpSound() {
	jumpSound.play();
}

void C_Object::playActionSound() {
	actionSound.play();
}
