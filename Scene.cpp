#include "Scene.hpp"


C_Scene::C_Scene() {
	list_objects.reserve(100);
	size_list_obj = 0;
	idObject = 0;
	prev_button_state = 0;


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

	Play.setFont(font);
	Play.setString("Play");
	Play.setCharacterSize(24);
	Play.setFillColor(sf::Color::White);
	Play.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x - Play.getGlobalBounds().width - 20.f, rect.getPosition().y + 10.f));

	ExampleLevel.setFont(font);
	ExampleLevel.setString("Example of Level");
	ExampleLevel.setCharacterSize(24);
	ExampleLevel.setFillColor(sf::Color::White);
	ExampleLevel.setPosition(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2 - ExampleLevel.getGlobalBounds().width / 2, rect.getPosition().y + rect.getSize().y - ExampleLevel.getGlobalBounds().height - 10.f));



	//place the lastMousePos in the middle of the rect
	lastMousePos = sf::Vector2i(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);

	reSizeObject.setFillColor(sf::Color::Transparent);
	reSizeObject.setOutlineThickness(2.5f);
	reSizeObject.setOutlineColor(sf::Color(0,125,0,255));

	for (int i = 0; i < 4; ++i) {
		reSizeObject_corner[i].setFillColor(sf::Color::Green);
		
	}

}

void C_Scene::update(sf::RenderWindow& window) {
	//draw rectangle in the window

	window.draw(rect);
	window.draw(Title);
	window.draw(Play);
	window.draw(ExampleLevel);
	drawObjects(window);
	window.draw(reSizeObject);
	for (int i = 0; i < 4; ++i)
		window.draw(reSizeObject_corner[i]);
}

void C_Scene::FloatObject(int Button, sf::Vector2i mouse_pos) {
	
	if (!Button) {
		prev_button_state = Button;
		lastMousePos = sf::Vector2i(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
		return;
	}

	int player = 0;
	if (Button == 3)
		for (int i = 0; i < list_objects.size(); ++i)
			if (list_objects[i].getType() == 3) {
				list_objects[i].move(sf::Vector2f(mouse_pos));
				if (!rect.getGlobalBounds().contains(list_objects[i].getPosition())
					|| mouse_pos.x > rect.getGlobalBounds().width + rect.getPosition().x - list_objects[i].getSize().x
					|| mouse_pos.y > rect.getGlobalBounds().height + rect.getPosition().y - list_objects[i].getSize().y
					) {
					list_objects[i].move(sf::Vector2f(lastMousePos));
				}
				else
					lastMousePos = mouse_pos;
				return;
			}

	if (!prev_button_state && !player) {
		++size_list_obj;
		++idObject;
		list_objects.push_back(C_Object());
		list_objects[size_list_obj - 1].setID(idObject);
		list_objects[size_list_obj - 1].setName(types_name[Button-1] + std::to_string(idObject));
		list_objects[size_list_obj - 1].setType(Button);
		list_objects[size_list_obj - 1].setSize(sf::Vector2f(50.f, 50.f));
		list_objects[size_list_obj - 1].setFriction(sf::Vector2f(0.8f,1.f));
		list_objects[size_list_obj - 1].setVelocity(sf::Vector2f(0.f, 0.f));

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
		for (int i = 0; i < 4; ++i)
			reSizeObject_corner[i].setSize(sf::Vector2f(0.f, 0.f));
		return;
	}

	for(int i = 0; i < size_list_obj; ++i)
		if (list_objects[i].getID() == idObject) {
			reSizeObject.setSize(list_objects[i].getSize() + sf::Vector2f(10.f,10.f));
			reSizeObject.setPosition(list_objects[i].getPosition() - sf::Vector2f(5.f, 5.f));
			for (int i = 0; i < 4; ++i)
				reSizeObject_corner[i].setSize(sf::Vector2f(15.f, 15.f));
			reSizeObject_corner[0].setPosition(reSizeObject.getPosition() - reSizeObject_corner[0].getSize());
			reSizeObject_corner[1].setPosition(reSizeObject.getPosition() + sf::Vector2f(reSizeObject.getSize().x, -reSizeObject_corner[0].getSize().y));
			reSizeObject_corner[2].setPosition(reSizeObject.getPosition() + sf::Vector2f(-reSizeObject_corner[0].getSize().x, reSizeObject.getSize().y));
			reSizeObject_corner[3].setPosition(reSizeObject.getPosition() + sf::Vector2f(reSizeObject.getSize().x, reSizeObject.getSize().y));
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


int C_Scene::reSizeObjectFunc(int idObject, sf::Vector2i mouse_pos) {
	if (idObject <= 0)
		return -1;
	for (int i = 0; i < size_list_obj; ++i)
		if (list_objects[i].getID() == idObject) {
			sf::Vector2f size = list_objects[i].getSize();
			sf::Vector2f pos = list_objects[i].getPosition();

			//check if mouse is in the rect
			if (!rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos))
				&& !rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x + size.x, mouse_pos.y + size.y)))
				return -1;

			if (reSizeObject_corner[0].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
				list_objects[i].setSize(sf::Vector2f(size.x - mouse_pos.x + pos.x -10.f, size.y - mouse_pos.y + pos.y -10.f));
				list_objects[i].move(sf::Vector2f(mouse_pos + sf::Vector2i(10,10)));
				return 0;
			}
			else if (reSizeObject_corner[1].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
				list_objects[i].setSize(sf::Vector2f(mouse_pos.x - pos.x - 10.f, size.y - mouse_pos.y + pos.y - 10.f));
				list_objects[i].move(sf::Vector2f(pos.x, mouse_pos.y + 10.f));
				return 1;
			}
			else if (reSizeObject_corner[2].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
				list_objects[i].setSize(sf::Vector2f(size.x - mouse_pos.x + pos.x - 10.f, mouse_pos.y - pos.y - 10.f));
				list_objects[i].move(sf::Vector2f(mouse_pos.x + 10.f, pos.y));
				return 2;
			}
			else if (reSizeObject_corner[3].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
				list_objects[i].setSize(sf::Vector2f(mouse_pos.x - pos.x - 10.f, mouse_pos.y - pos.y - 10.f));
				return 3;
			}
		}
	return -1;
}

int C_Scene::moveObject(int idObject, sf::Vector2i mouse_pos) {
	if (idObject <= 0)
		return -1;
	for (int i = 0; i < size_list_obj; ++i)
		if (list_objects[i].getID() == idObject) {
			if (rect.getGlobalBounds().contains(list_objects[i].getPosition()) && rect.getGlobalBounds().contains(list_objects[i].getPosition() + list_objects[i].getSize())) {
				if (rect.getGlobalBounds().contains(sf::Vector2f(mouse_pos))
					&& list_objects[i].getPosition().x < mouse_pos.x
					&& list_objects[i].getPosition().y < mouse_pos.y
					&& list_objects[i].getPosition().x + list_objects[i].getSize().x > mouse_pos.x
					&& list_objects[i].getPosition().y + list_objects[i].getSize().y > mouse_pos.y
					)

				{
					list_objects[i].move(sf::Vector2f(mouse_pos) - list_objects[i].getSize() / 2.f);
					return 1;
				}
			}
			else
				list_objects[i].move(rect.getPosition() + rect.getSize() / 2.f);

		}
	return -1;
}
 
bool C_Scene::buttonPlay(sf::Vector2i mouse_pos) {
	if (Play.getGlobalBounds().contains(sf::Vector2f(mouse_pos))) 
		return 1;
	return 0;
}

bool C_Scene::buttonExample(sf::Vector2i mouse_pos) {
	if (ExampleLevel.getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
		return 1;
	return 0;
}