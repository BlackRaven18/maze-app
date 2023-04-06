#include "BFSPathfinder.h"

BFSPathfinder::BFSPathfinder()
{
	this->running = false;
	this->initializedWithStartData = false;
	this->exitFound = false;
}

void BFSPathfinder::checkChamber(MazeCell **mazeTable, int chamberId, int x, int y)
{
	if (x < 0 || y < 0 || x >= MAZE_TABLE_ROWS || y >= MAZE_TABLE_COLUMNS) return;

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


void BFSPathfinder::findRoad(MazeCell **mazeTable, sf::Vector2i startPos, sf::Vector2i endPos)
{
	if (!isRunning()) {
		return;
	}


	if (!isInitializedWithStartData()) {
		mazeTable[startPos.x][startPos.y].setVisited(true);
		queue.push(startPos);

		setInitializedWithStartData(true);
	}

	if (isExitFound()) {
		if(!mazeTable[tmpPoint.x][tmpPoint.y].isVisited()) {
			switch (mazeTable[tmpPoint.x][tmpPoint.y].getId()) {
			case LEFT: mazeTable[tmpPoint.x++][tmpPoint.y].setVisited(true); break;
			case UP: mazeTable[tmpPoint.x][tmpPoint.y++].setVisited(true); break;
			case RIGHT: mazeTable[tmpPoint.x--][tmpPoint.y].setVisited(true); break;
			case DOWN: mazeTable[tmpPoint.x][tmpPoint.y--].setVisited(true); break;
			}
			mazeTable[tmpPoint.x][tmpPoint.y].setColor(MAZE_TRACK_COLOR);

			sf::sleep(PATHFINDER_DRAWING_PATH_DELAY);
		}

		if (tmpPoint == startPos) {

			std::cout << "Znaleziono droge!" << std::endl;
			stop();
		}

		return;
	}
	if (!isExitFound()) {

		if (queue.empty()) {
			stop();
			return;
		}

		sf::Vector2i point = queue.front();
		queue.pop();

		sf::sleep(PATHFINDER_CHECKED_CELLS_DELAY);

		if (point.x == endPos.x && point.y == endPos.y) {

			this->tmpPoint = point;
			setExitFound(true);
			return;
		}

		if (point.x - 1 >= 0) checkChamber(mazeTable, LEFT, point.x - 1, point.y);
		if (point.y - 1 >= 0) checkChamber(mazeTable, UP, point.x, point.y - 1);
		if (point.x + 1 < MAZE_TABLE_ROWS) checkChamber(mazeTable, RIGHT, point.x + 1, point.y);
		if (point.y + 1 < MAZE_TABLE_COLUMNS) checkChamber(mazeTable, DOWN, point.x, point.y + 1);

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
