#pragma once
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "../View.h"

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateDt();
	void updateSFMLEvents();
private:
	void initWindow();
	
	sf::Clock dtClock;
	double dt;

	sf::Window* window;
	sf::Event event;

	View v1;
};

