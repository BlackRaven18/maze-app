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

	bool running;
	bool initializedWithStartData;
	bool exitFound;

	void checkChamber(MazeCell mazeTable[][MAZE_TABLE_WIDTH], int chamberId, int x, int y);
	void clearQueue();

	void setInitializedWithStartData(bool initializedWithStartData);
	bool isInitializedWithStartData();

	void setExitFound(bool exitFound);

public:

	BFSPathfinder();

	void findRoad(MazeCell mazeTable[][MAZE_TABLE_WIDTH], sf::Vector2i startPos, sf::Vector2i endPos);
	void drawRoad(MazeCell mazeTable[][MAZE_TABLE_WIDTH], sf::Vector2i startPos);
	bool isRunning();
	bool isExitFound();
	void start();
	void stop();


};
