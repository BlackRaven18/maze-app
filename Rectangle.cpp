#include "Rectangle.h"

Rectangle::Rectangle() {
	
}
Rectangle::Rectangle(int x, int y, int width, int height, sf::Color color) {
	rectangle.setPosition(x, y);
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setFillColor(color);
}

void Rectangle::draw(sf::RenderWindow* window) {
	window->draw(rectangle);
}

int Rectangle::getX() {
	return rectangle.getPosition().x;
}

int Rectangle::getY() {
	return rectangle.getPosition().y;
}

void Rectangle::setX(int x) {
	rectangle.setPosition(x, rectangle.getPosition().y);
}

void Rectangle::setY(int y) {
	rectangle.setPosition(rectangle.getPosition().x, y);
}

int Rectangle::getWidth() {
	return rectangle.getSize().x;
}

void Rectangle::setWidth(int width) {
	rectangle.setSize(sf::Vector2f(width, rectangle.getSize().y));
}


int Rectangle::getHeight() {
	return rectangle.getSize().y;
}

void Rectangle::setHeight(int height) {
	rectangle.setSize(sf::Vector2f(rectangle.getSize().x, y));
}

void Rectangle::setPosition(int x, int y) {
	rectangle.setPosition(x, y);
}
void Rectangle::setSize(int width, int height) {
	rectangle.setSize(sf::Vector2f(width, height));
}

sf::Color Rectangle::getColor() {
	return rectangle.getFillColor();
}
void Rectangle::setColor(sf::Color color) {
	rectangle.setFillColor(color);
}