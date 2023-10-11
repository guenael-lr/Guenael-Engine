#include "Hierarchy.hpp"


C_Hierarchy::C_Hierarchy() {
	rect.setSize(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT));
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(sf::Vector2f(0, 0));

	

	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		exit(0);

	Title.setFont(font);
	Title.setString("Hierarchy");
	Title.setCharacterSize(24);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2 - Title.getGlobalBounds().width / 2, rect.getPosition().y + 10));
}

void C_Hierarchy::update(sf::RenderWindow& window) {
	//draw rectangle in the window
	window.draw(rect);
	window.draw(Title);
	for (int i = 0; i < ButtonText.size(); ++i)
		window.draw(ButtonText[i]);
}

void C_Hierarchy::listElement(std::vector<C_Object> listObject) {
	//make a text list of all the name of the object in the list
	//make a button for each object
	ButtonText.clear();
	ButtonID.clear();
	for (int i = ButtonText.size(); i < listObject.size(); ++i) {
		ButtonText.push_back(sf::Text());
		ButtonID.push_back(listObject[i].getID());
		ButtonText[i].setFont(font);
		ButtonText[i].setString(listObject[i].getName());
		ButtonText[i].setCharacterSize(24);
		//ButtonText[i].setStyle(sf::Text::Bold);
		ButtonText[i].setFillColor(sf::Color::White);
		ButtonText[i].setPosition(sf::Vector2f(rect.getPosition().x + 10, rect.getPosition().y + 50 + i * 30));

	}
}

int C_Hierarchy::hoverListElement(sf::Vector2i mouse_pos) {
	
	button = 0;
	for (int i = 0; i < ButtonText.size(); ++i) {
		if (ButtonText[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
			ButtonText[i].setFillColor(sf::Color::Red);
			button = ButtonID[i];
		}
		else {
			ButtonText[i].setFillColor(sf::Color::White);
		}
	}
	return button;
}

void C_Hierarchy::removeListElement(int id) {
	for (int i = 0; i < ButtonID.size(); ++i) {
		if (ButtonID[i] == id) {
			ButtonID.erase(ButtonID.begin() + i);
			ButtonText.erase(ButtonText.begin() + i);
		}
	}

}