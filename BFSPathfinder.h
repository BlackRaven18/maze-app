#pragma once

#include "SFML/Graphics.hpp"
#include "AppConstDef.h"
#include <queue>
#include "Pathfinder.h"
#include "MazeCell.h"
#include "MazeCellTypes.h"

//TODO: delete this later, include for test only!
#include <iostream>


class BFSPathfinder : public virtual Pathfinder {
private:

	std::queue<sf::Vector2i> queue;
	sf::Vector2i tmpPoint;

	int steps;

	bool running;
	bool initializedWithStartData;
	bool exitFound;

	void checkChamber(MazeCell **mazeTable, int rows, int columns, int chamberId, int x, int y);
	void clearQueue();

	void setInitializedWithStartData(bool initializedWithStartData);
	bool isInitializedWithStartData();

	void setExitFound(bool exitFound);

public:

	BFSPathfinder();

	void findRoad(MazeCell** mazeTable, int rows, int columns, sf::Vector2i startPoint, sf::Vector2i endPoint);
	void drawRoad(MazeCell** mazeTable, int rows, int columns, sf::Vector2i startPoint);
	bool isRunning();
	bool isExitFound();
	void start();
	void stop();


};
