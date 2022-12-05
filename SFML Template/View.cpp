#include "View.h"

View::View(const sf::Vector2f _Size, const sf::Vector2f _Position)
{
	setSize(_Size);
	setPosition(_Position);
}

View::~View()
{
}

sf::Vector2f View::getPosition() const
{
	return position;
}

sf::Vector2f View::getSize() const
{
	return size;
}

void View::setPosition(const float _X, const float _Y)
{
	setPosition(sf::Vector2f(_X, _Y));
}

void View::setPosition(const sf::Vector2f _Position)
{
	position = _Position;
	updated = true;
}

void View::setSize(const float _X, const float _Y)
{
	setSize(sf::Vector2f(_X, _Y));
}

void View::setSize(const sf::Vector2f _Size)
{
	size = _Size;
	updated = true;
}

void View::move(const float _X, const float _Y)
{
	setPosition(position.x+_X, position.y+_Y);
}

void View::update()
{
	if (updated)
	{
		glViewport(position.x, position.y, size.x, size.y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, size.x, size.y, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		updated = false;
	}
}
