#include "BFSPathfinder.h"

BFSPathfinder::BFSPathfinder()
{
	this->running = false;
	this->initializedWithStartData = false;
	this->exitFound = false;
}


void BFSPathfinder::checkChamber(MazeCell **mazeTable, int rows, int columns, int chamberId, int x, int y)
{
	if (x < 0 || y < 0 || x >= rows || y >= columns) return;

	if (mazeTable[x][y].getId() == MazeCellTypes::WALL) return;
	if (mazeTable[x][y].getId() == MazeCellTypes::START_POINT) return;
	if (mazeTable[x][y].isChecked()) return;

	if (mazeTable[x][y].getId() == MazeCellTypes::PATH) {
		mazeTable[x][y].setColor(MAZE_VISITED_CELL_COLOR);
	}

	mazeTable[x][y].setId(chamberId);
	mazeTable[x][y].setChecked(true);

	queue.push(sf::Vector2i(x, y));
}


void BFSPathfinder::findRoad(MazeCell **mazeTable, int rows, int columns, sf::Vector2i startPoint, sf::Vector2i endPoint)
{
	if (!isRunning()) {
		return;
	}

	if (!isInitializedWithStartData()) {
		mazeTable[startPoint.x][startPoint.y].setVisited(true);
		queue.push(startPoint);
		steps = 0;

		setInitializedWithStartData(true);
	}

	if (!isExitFound()) {

		if (queue.empty()) {
			stop();
			return;
		}

		sf::Vector2i point = queue.front();
		queue.pop();

		if (point.x == endPoint.x && point.y == endPoint.y) {

			this->tmpPoint = point;
			setExitFound(true);
			return;
		}

		if (point.x - 1 >= 0) checkChamber(mazeTable, rows, columns, LEFT, point.x - 1, point.y);
		if (point.y - 1 >= 0) checkChamber(mazeTable, rows, columns, UP, point.x, point.y - 1);
		if (point.x + 1 < rows) checkChamber(mazeTable, rows, columns, RIGHT, point.x + 1, point.y);
		if (point.y + 1 < columns) checkChamber(mazeTable, rows, columns, DOWN, point.x, point.y + 1);

	}
}

void BFSPathfinder::drawRoad(MazeCell** mazeTable, int rows, int columns, sf::Vector2i startPoint)
{
	if (!mazeTable[tmpPoint.x][tmpPoint.y].isVisited()) {
		switch (mazeTable[tmpPoint.x][tmpPoint.y].getId()) {
		case LEFT: mazeTable[tmpPoint.x++][tmpPoint.y].setVisited(true); break;
		case UP: mazeTable[tmpPoint.x][tmpPoint.y++].setVisited(true); break;
		case RIGHT: mazeTable[tmpPoint.x--][tmpPoint.y].setVisited(true); break;
		case DOWN: mazeTable[tmpPoint.x][tmpPoint.y--].setVisited(true); break;
		}
		mazeTable[tmpPoint.x][tmpPoint.y].setColor(MAZE_TRACK_COLOR);
		steps++;
	}

	if (tmpPoint == startPoint) {

		std::cout << "Znaleziono droge!; liczba krokow: " << steps  << std::endl;
		stop();
	}
}


bool BFSPathfinder::isRunning()
{
	return this->running;
}

void BFSPathfinder::start()
{
	this->running = true;
}

void BFSPathfinder::stop()
{
	this->running = false;
	this->initializedWithStartData = false;
	this->exitFound = false;
	this->tmpPoint.x = this->tmpPoint.y = -1;
	clearQueue();
}

void BFSPathfinder::clearQueue()
{
	while (!queue.empty()) {
		queue.pop();
	}
}

void BFSPathfinder::setInitializedWithStartData(bool initializedWithStartData)
{
	this->initializedWithStartData = initializedWithStartData;
}

bool BFSPathfinder::isInitializedWithStartData()
{
	return this->initializedWithStartData;
}

void BFSPathfinder::setExitFound(bool exitFound){
	this->exitFound = exitFound;
}

bool BFSPathfinder::isExitFound()
{
	return this->exitFound;
}
