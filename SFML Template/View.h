#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>

class View
{
public:
	View(const sf::Vector2f _Size = sf::Vector2f(), const sf::Vector2f _Position = sf::Vector2f());
	~View();

	//Gets
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	//Sets
	void setPosition(const float _X, const float _Y);
	void setPosition(const sf::Vector2f _Position);
	void setSize(const float _X, const float _Y);
	void setSize(const sf::Vector2f _Size);

	void move(const float _X, const float _Y);

	void update();

private:
	sf::Vector2f position;
	sf::Vector2f size;

	bool updated;
};

