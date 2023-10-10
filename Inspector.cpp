#include "Inspector.hpp"


C_Inspector::C_Inspector() {
	rect.setSize(sf::Vector2f(SCREEN_WIDTH/4, SCREEN_HEIGHT));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(SCREEN_WIDTH - rect.getGlobalBounds().width, 0));
	
	
	if(!font.loadFromFile("Assets/Fonts/arial.ttf"))
		exit(0);

	Title.setFont(font); 
	Title.setString("Inspector");
	Title.setCharacterSize(24);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x/2 - Title.getGlobalBounds().width/2, rect.getPosition().y + 10));
}

void C_Inspector::update(sf::RenderWindow &window) {
	//draw rectangle in the window
	window.draw(rect);
	window.draw(Title);
}