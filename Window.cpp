#include "Window.hpp"


C_Window::C_Window() {
	isRunning = true;
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Guenael Engine");
	window.setFramerateLimit(60);

	Scene = new C_Scene();
	Inspector = new C_Inspector();
	Project = new C_Project();
	Hierarchy = new C_Hierarchy();

	selection_Hierarchy = -1;

}

void C_Window::update() {
	window.clear();
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			quit();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				(*Project).isHoverAButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				selection_Hierarchy = (*Hierarchy).hoverListElement(sf::Vector2i(sf::Mouse::getPosition(window)));
				std::cout << "click" << std::endl;
			}
					
					//Project.setIsPressed(true);
		}

		//if button suppr is pressed delete the object
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Delete) {
				(*Scene).removeObject(selection_Hierarchy);
				(*Hierarchy).removeListElement(selection_Hierarchy);
				selection_Hierarchy = -1;
			}
		}
			
	}
	(*Scene).FloatObject((*Project).getButton(), sf::Mouse::getPosition(window));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		quit();
	}

	(*Hierarchy).listElement((*Scene).getListObjects());
	(*Scene).drawReSizeObject(selection_Hierarchy);
	
	(*Inspector).update(window);
	(*Project).update(window);
	(*Hierarchy).update(window);
	(*Scene).update(window);
	window.display();
}

void C_Window::quit() {
	window.close();
	exit(0);
}

bool C_Window::getIsRunning() {
	return this->isRunning;
}

void C_Window::FixedUpdate() {
	//nthin
}

void C_Window::run() {
	while (window.isOpen()) {
		update();
		FixedUpdate();
	}
}