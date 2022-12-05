#include "Window.h"

Window::Window()
{
	initWindow();
	v1 = View(sf::Vector2f(400, 400), sf::Vector2f(0, 0));
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	window->display();
}

void Window::update()
{
	v1.update();
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
						window->close();
						break;
				}
				break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::Window(sf::VideoMode(400, 400), "SFML/OpenGL Template", sf::Style::Default, sf::ContextSettings());
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	window->setActive(true);
}
