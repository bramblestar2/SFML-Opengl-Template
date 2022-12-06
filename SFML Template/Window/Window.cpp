#include "Window.h"

Window::Window()
{
	initWindow();

	c1 = Camera(sf::Vector2f(window->getSize()), sf::Vector3f(0, 0, 3));

	cameraPaused = false;

	c1.setMouseSensitivity(0.25f);
	c1.enableDepth();
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
	if (!cameraPaused)
	{
		c1.updateMovement(dt);
		c1.updateMouseMovement(window, dt);
		c1.update(dt);
	}
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
				case sf::Keyboard::Tab:
					cameraPaused = cameraPaused ? false : true;
					if (!cameraPaused)
						c1.setLastMouse(sf::Vector2f(sf::Mouse::getPosition(*window)));
					break;
			}
			break;

		case sf::Event::MouseMoved:
			break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::Window(sf::VideoMode(500, 400), "SFML/OpenGL Template", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	window->setActive(true);
}
