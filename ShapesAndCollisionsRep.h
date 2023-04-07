#pragma once

#include "SFML/Graphics.hpp"

class ShapesAndCollisionsRep {
public:

	static sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color color);
	static bool isPointInRectangleArea(int pointX, int pointY, int recX, int recY, int recWidth, int recHeight);
};
