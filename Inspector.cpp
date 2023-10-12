#include "Inspector.hpp"
void setText(sf::Text& text, sf::Font& font, std::string str, int size, sf::Color color, sf::Vector2f pos);
std::string precision2(std::string input);

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

	for(int i = 0; i < List_Text.size(); ++i)
		window.draw(List_Text[i]);
	for (int i = 0; i < List_Value.size(); ++i)
		window.draw(List_Value[i]);
	for (int i = 0; i < List_Button.size(); ++i)
		window.draw(List_Button[i]);

}


void C_Inspector::Inspect(std::vector<C_Object> list_object, int id) {
	C_Object* obj = nullptr;
	List_Button.clear();
	List_Text.clear();
	List_Value.clear();
	if (!id)
		return;
	for (int i = 0; i < list_object.size(); ++i) {
		if (list_object[i].getID() == id) {
			obj = &list_object[i];
			break;
		}
	}

	//draw in the rect the name of the object obj

	List_Text.push_back(sf::Text());
	setText(List_Text[0], font, "Name : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, rect.getPosition().y + 50));

	List_Value.push_back(sf::Text());
	setText(List_Value[0], font, obj->getName(), 24, sf::Color::White, sf::Vector2f(List_Text[0].getPosition().x + List_Text[0].getGlobalBounds().width, List_Text[0].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[1], font, "Type : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[0].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[1], font, std::to_string(obj->getType()), 24, sf::Color::White, sf::Vector2f(List_Text[1].getPosition().x + List_Text[1].getGlobalBounds().width, List_Text[1].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[2], font, "Position : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[1].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[2], font, precision2(std::to_string(obj->getPosition().x)), 24, sf::Color::White, sf::Vector2f(List_Text[2].getPosition().x + List_Text[2].getGlobalBounds().width, List_Text[2].getPosition().y));
	
	List_Value.push_back(sf::Text());
	setText(List_Value[3], font, precision2(std::to_string(obj->getPosition().y)), 24, sf::Color::White, sf::Vector2f(List_Value[2].getPosition().x + List_Value[2].getGlobalBounds().width + 10, List_Value[2].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[3], font, "Size : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[2].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[4], font, precision2(std::to_string(obj->getSize().x)), 24, sf::Color::White, sf::Vector2f(List_Text[3].getPosition().x + List_Text[3].getGlobalBounds().width, List_Text[3].getPosition().y));

	List_Value.push_back(sf::Text());
	setText(List_Value[5], font, precision2(std::to_string(obj->getSize().y)), 24, sf::Color::White, sf::Vector2f(List_Value[4].getPosition().x + List_Value[4].getGlobalBounds().width + 10, List_Value[4].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[4], font, "Rotation : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[3].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[6], font, precision2(std::to_string(obj->getRotation().x)), 24, sf::Color::White, sf::Vector2f(List_Text[4].getPosition().x + List_Text[4].getGlobalBounds().width, List_Text[4].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[5], font, "Velocity : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[4].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[7], font, precision2(std::to_string(obj->getVelocity().x)), 24, sf::Color::White, sf::Vector2f(List_Text[5].getPosition().x + List_Text[5].getGlobalBounds().width, List_Text[5].getPosition().y));

	List_Value.push_back(sf::Text());
	setText(List_Value[8], font, precision2(std::to_string(obj->getVelocity().y)), 24, sf::Color::White, sf::Vector2f(List_Value[7].getPosition().x + List_Value[7].getGlobalBounds().width + 10, List_Value[7].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[6], font, "Friction : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[5].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[9], font, precision2(std::to_string(obj->getFriction().x)), 24, sf::Color::White, sf::Vector2f(List_Text[6].getPosition().x + List_Text[6].getGlobalBounds().width, List_Text[6].getPosition().y));

	List_Value.push_back(sf::Text());
	setText(List_Value[10], font, precision2(std::to_string(obj->getFriction().y)), 24, sf::Color::White, sf::Vector2f(List_Value[9].getPosition().x + List_Value[9].getGlobalBounds().width + 10, List_Value[9].getPosition().y));

	List_Text.push_back(sf::Text());
	setText(List_Text[7], font, "Gravity : ", 24, sf::Color::White, sf::Vector2f(rect.getPosition().x + 10, List_Text[6].getPosition().y + 30));

	List_Value.push_back(sf::Text());
	setText(List_Value[11], font, precision2(std::to_string(obj->getGravity())), 24, sf::Color::White, sf::Vector2f(List_Text[7].getPosition().x + List_Text[7].getGlobalBounds().width, List_Text[7].getPosition().y));

}

void setText(sf::Text& text, sf::Font& font, std::string str, int size, sf::Color color, sf::Vector2f pos) {
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(pos);
}


std::string precision2(std::string input)
{
	std::string result;
	std::string delimiter = ".";
	for (std::size_t i = 0; i < input.size(); ++i)
	{
		if (input[i] != delimiter[0])
		{
			result.push_back(input[i]);
		}
		else
		{
			result.push_back(input[i]);
			result.push_back(input[i+1]);
			result.push_back(input[i+2]);
			return result;
		}
	}

	return result;
}

std::string C_Inspector::changeValue(sf::Vector2i mouse_pos) {
	
	std::string str = "";
	int i = 0;
	for (i = 0; i < List_Value.size(); ++i) {
		if (List_Value[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
			str = List_Value[i].getString();
			break;
		}
	}
	if (str == "")
		return str;
	
	windowInspector.create(sf::VideoMode(500, 250), "Change value of " + str);
	windowInspector.setFramerateLimit(30);
	sf::Event event;
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		exit(0);
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(0, 0));
	
	text.setString(str);
	while (windowInspector.isOpen()) {
		while (windowInspector.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				windowInspector.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 8) {
					if (str.size() > 0)
						str.pop_back();
				}
				else if (event.text.unicode == 13) {
					windowInspector.close();
				}
				else {
					str.push_back(event.text.unicode);
				}
				text.setString(str);
			}
		}
		windowInspector.clear(sf::Color::Black);
		windowInspector.draw(text);
		windowInspector.display();
	}
	
	return std::to_string(i) + ":" + str;
}

void C_Inspector::changeValueObject(std::vector<C_Object> *list_object, int id, std::string value) {
	if (!id || value == "")
		return;
	std::string info = "";
	std::string what = "";
	std::string delimiter = ":";
	for (std::size_t i = 0; i < value.size(); ++i)
	{
		if (value[i] != delimiter[0]) {
			info.push_back(value[i]);
		}
		else
			break;
	}
	what = value.substr(info.size()+1, value.size());
	for(int i = 0; i < (*list_object).size(); ++i)
		if ((*list_object)[i].getID() == id) {
			switch (atoi(info.c_str())) {
			case 0:
				(*list_object)[i].setName(what);
				break;
			case 1:
				(*list_object)[i].setType(atoi(what.c_str()));
				break;
			case 2:
				(*list_object)[i].move(sf::Vector2f(atof(what.c_str()), (*list_object)[i].getPosition().y));
				break;
			case 3:
				(*list_object)[i].move(sf::Vector2f((*list_object)[i].getPosition().x, atof(what.c_str())));
				break;
			case 4:
				(*list_object)[i].setSize(sf::Vector2f(atof(what.c_str()), (*list_object)[i].getSize().y));
				break;
			case 5:
				(*list_object)[i].setSize(sf::Vector2f((*list_object)[i].getSize().x, atof(what.c_str())));
				break;
			case 6:
				(*list_object)[i].setRotation(sf::Vector2f(atof(what.c_str()), (*list_object)[i].getRotation().y));
				break;
			case 7:
				(*list_object)[i].setVelocity(sf::Vector2f(atof(what.c_str()), (*list_object)[i].getVelocity().y));
				break;
			case 8:
				(*list_object)[i].setVelocity(sf::Vector2f((*list_object)[i].getVelocity().x, atof(what.c_str())));
				break;
			case 9:
				(*list_object)[i].setFriction(sf::Vector2f(atof(what.c_str()), (*list_object)[i].getFriction().y));
				break;
			case 10:
				(*list_object)[i].setFriction(sf::Vector2f((*list_object)[i].getFriction().x, atof(what.c_str())));
				break;
			case 11:
				(*list_object)[i].setGravity(atof(what.c_str()));
				break;

			}
		}
			
}
