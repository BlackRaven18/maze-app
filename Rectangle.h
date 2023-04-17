#pragma once
#include "SFML/Graphics.hpp"

class Rectangle {
protected:
	sf::RectangleShape rectangle;
	int x, y;
	int width, height;
	sf::Color color;

public:

	Rectangle();
	Rectangle(int x, int y, int width, int height, sf::Color color);

	void draw(sf::RenderWindow* window);

	int getX();
	int getY();

	sf::Vector2i getPosition();

	void setX(int x);
	void setY(int y);


	int getWidth();
	void setWidth(int width);

	int getHeight();
	void setHeight(int height);

	void setPosition(int x, int y);
	void setSize(int width, int height);

	sf::Color getColor();
	void setColor(sf::Color color);
};