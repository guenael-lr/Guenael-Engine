#include "Scene.hpp"


C_Scene::C_Scene() {
	rect.setSize(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3));
	rect.setFillColor(sf::Color(252,255,255,125));
	rect.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, 0));



	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		std::cout <<  "pas youpi"  << std::endl;;

	Title.setFont(font);
	Title.setString("Scene");
	Title.setCharacterSize(24);
	Title.setFillColor(sf::Color::Black);
	Title.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2 - Title.getGlobalBounds().width / 2, rect.getPosition().y + 10));

	//place the lastMousePos in the middle of the rect
	lastMousePos = sf::Vector2i(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);

	reSizeObject.setFillColor(sf::Color::Transparent);
	reSizeObject.setOutlineThickness(5.f);
	reSizeObject.setOutlineColor(sf::Color::Green);
	
}

void C_Scene::update(sf::RenderWindow& window) {
	//draw rectangle in the window

	window.draw(rect);
	window.draw(Title);
	drawObjects(window);
	window.draw(reSizeObject);
}

void C_Scene::FloatObject(int Button, sf::Vector2i mouse_pos) {
	
	if (!Button) {
		prev_button_state = Button;
		lastMousePos = sf::Vector2i(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
		return;
	}
	if (!prev_button_state) {
		++size_list_obj;
		++idObject;
		list_objects.push_back(C_Object());
		list_objects[size_list_obj - 1].setID(idObject);
		list_objects[size_list_obj - 1].setName("Object " + std::to_string(idObject));
		list_objects[size_list_obj - 1].setType(Button);
		list_objects[size_list_obj - 1].setSize(sf::Vector2f(50.f, 50.f));
		list_objects[size_list_obj - 1].setParent(nullptr);
	}
		list_objects[size_list_obj - 1].move(sf::Vector2f(mouse_pos));
		if (!rect.getGlobalBounds().contains(list_objects[size_list_obj - 1].getPosition())
			|| mouse_pos.x > rect.getGlobalBounds().width + rect.getPosition().x - list_objects[size_list_obj - 1].getSize().x
			|| mouse_pos.y > rect.getGlobalBounds().height + rect.getPosition().y - list_objects[size_list_obj - 1].getSize().y
			) {
			list_objects[size_list_obj - 1].move(sf::Vector2f(lastMousePos));
		}
		else
			lastMousePos = mouse_pos;
	
	prev_button_state = Button;
}

void C_Scene::drawObjects(sf::RenderWindow& window) {
	for (int i = 0; i < size_list_obj; ++i)
		list_objects[i].draw(window);
}

void C_Scene::drawReSizeObject(int idObject) {
	if (idObject <= 0) {
		reSizeObject.setSize(sf::Vector2f(0.f, 0.f));
		reSizeObject.setPosition( sf::Vector2f(0.f, 0.f));
		return;
	}

	for(int i = 0; i < size_list_obj; ++i)
		if (list_objects[i].getID() == idObject) {
			reSizeObject.setSize(list_objects[i].getSize() + sf::Vector2f(10.f,10.f));
			reSizeObject.setPosition(list_objects[i].getPosition() - sf::Vector2f(5.f, 5.f));

		}
}

void C_Scene::removeObject(int idObject) {
	for (int i = 0; i < size_list_obj; ++i)
		if (list_objects[i].getID() == idObject) {
			list_objects.erase(list_objects.begin() + i);
			--size_list_obj;
			return;
		}
}

 