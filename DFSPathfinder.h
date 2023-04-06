#pragma once

#include "SFML/Graphics.hpp"
#include "AppConstDef.h"
#include <stack>
#include "Pathfinder.h"
#include "MazeCell.h"
#include "MazeCellTypes.h"

#include <iostream>

class DFSPathfinder : public virtual Pathfinder {
private:
	std::stack<sf::Vector2i> stack;
	sf::Vector2i tmpPoint;

	bool running;
	bool initializedWithStartData;
	bool exitFound;

	void checkChamber(MazeCell **mazeTable, int chamberId, int x, int y);
	void clearStack();

	void setInitializedWithStartData(bool initializedWithStartData);
	bool isInitializedWithStartData();

	void setExitFound(bool exitFound);
	bool isExitFound();
public:
	DFSPathfinder();

	void findRoad(MazeCell **mazeTable, sf::Vector2i startPos, sf::Vector2i endPos);

	bool isRunning();

	void start();
	void stop();
};