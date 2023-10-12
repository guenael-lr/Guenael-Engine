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
	state_Button_Mouse = sf::Vector2i(0.f,0.f);
	prev_state_Button_Mouse = sf::Vector2i(0.f, 0.f);
	mouse_pos = sf::Vector2i(0.f, 0.f);
	mouse_pos = sf::Vector2i(0.f, 0.f);

}

void C_Window::update() {
	window.clear();
	sf::Event event;
	prev_state_Button_Mouse = state_Button_Mouse;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			quit();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			state_Button_Mouse.y = event.mouseButton.button == sf::Mouse::Left;
			state_Button_Mouse.x = event.mouseButton.button == sf::Mouse::Right; 
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if(event.mouseButton.button == sf::Mouse::Left)  state_Button_Mouse.y = 0 ;
			if(event.mouseButton.button == sf::Mouse::Right) state_Button_Mouse.x = 0 ;
		}
					
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Delete) {
				(*Inspector).Inspect((*(*Scene).getListObjects()), 0);
				(*Scene).removeObject(selection_Hierarchy);
				(*Hierarchy).removeListElement(selection_Hierarchy);
				selection_Hierarchy = -1;
			}
		}

		
	}

	//get the mouse position in the window
	mouse_pos = sf::Mouse::getPosition(window);
	(*Scene).FloatObject((*Project).getButton(), sf::Mouse::getPosition(window));

	if (state_Button_Mouse.y == 1) {
		(*Project).isHoverAButton(mouse_pos);
		(*Inspector).changeValueObject((*Scene).getListObjects(), selection_Hierarchy, (*Inspector).changeValue(mouse_pos));
		if (-1 == (*Scene).reSizeObjectFunc(selection_Hierarchy, mouse_pos))
			if (-1 == (*Scene).moveObject(selection_Hierarchy, mouse_pos))
				selection_Hierarchy = (*Hierarchy).hoverListElement(mouse_pos);

	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		quit();
	}
	if(selection_Hierarchy != -1)
		(*Inspector).Inspect((*(*Scene).getListObjects()), selection_Hierarchy);
	(*Hierarchy).listElement((*(*Scene).getListObjects()));
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