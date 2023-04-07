#pragma once

#include "SFML/Graphics.hpp"
#include "MazeCell.h"

class Pathfinder {
public:
	virtual void findRoad(MazeCell **mazeTable, int rows, int columns, sf::Vector2i startPoint, sf::Vector2i endPoint) = 0;
};