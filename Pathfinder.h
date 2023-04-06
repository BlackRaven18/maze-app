#pragma once

#include "SFML/Graphics.hpp"
#include "MazeCell.h"

class Pathfinder {
public:
	virtual void findRoad(MazeCell **mazeTable, sf::Vector2i startPos, sf::Vector2i endPos) = 0;
};