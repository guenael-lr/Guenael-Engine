#include "Project.hpp"


C_Project::C_Project() {
	
	rect.setSize(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT * 2 / 3));

	for (int i = 0; i < List_Button_Size; ++i) {
		List_Button.push_back(sf::RectangleShape());
		List_Text.push_back(sf::Text());
	}
		

	if (!font.loadFromFile("Assets/Fonts/arial2.ttf"))
		exit(0);

	Title.setFont(font);
	Title.setString("Project");
	Title.setCharacterSize(24);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2 - Title.getGlobalBounds().width / 2, rect.getPosition().y + 10));
	
	//draw List_Button in the rect 
	float offset = 20.f;

	for (int i = 0; i < List_Button_Size; ++i) {
		List_Button[i].setSize(sf::Vector2f(SCREEN_WIDTH / 2 / 3 - offset, SCREEN_HEIGHT / 3 / 3 - offset));
		List_Button[i].setFillColor(sf::Color::Magenta);
		List_Button[i].setPosition(sf::Vector2f(rect.getPosition().x + offset * (i%3) + 10 + (i%3) * List_Button[i].getSize().x, rect.getPosition().y + 50  + (List_Button[i].getSize().y + 50) * (i/3) ));
		List_Button[i].setOutlineThickness(5.f);
		List_Button[i].setOutlineColor(sf::Color::Black);
		List_Text[i].setFont(font);
		List_Text[i].setString(List_Button_Text[i]);
		List_Text[i].setCharacterSize(24);
		List_Text[i].setFillColor(sf::Color::Black);
		List_Text[i].setPosition(sf::Vector2f(List_Button[i].getPosition().x + List_Button[i].getSize().x / 2 - List_Text[i].getGlobalBounds().width / 2, List_Button[i].getPosition().y + List_Button[i].getSize().y / 2 - List_Text[i].getGlobalBounds().height / 2));
	}

}

void C_Project::update(sf::RenderWindow& window) {
	//draw rectangle in the window
	window.draw(rect);
	window.draw(Title);
	
	for (int i = 0; i < List_Button_Size; ++i) {
		window.draw(List_Button[i]);
		window.draw(List_Text[i]);
	}
}


int C_Project::isHoverAButton(sf::Vector2i mouse_pos) {
	this->Button = 0;
	for (int i = 0; i < List_Button_Size; ++i) {
		if (List_Button[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
			List_Button[i].setOutlineColor(sf::Color::Red); //faire une var state ds button
			this->Button = i + 1;
		}
		else
			List_Button[i].setOutlineColor(sf::Color::Black);
			
	}
	return this->Button;
}