#include "DFSMazeGenerator.h"


void DFSMazeGenerator::generateMaze(MazeCell** mazeTable, int rows, int columns, sf::Vector2i* startPoint, sf::Vector2i* endPoint)
{
	clearMazeTable(mazeTable, rows, columns);

	//start point is not a wall
	sf::Vector2i seedPoint = randSeedPoint(rows, columns);
	setCellParameters(&mazeTable[seedPoint.x][seedPoint.y],
		true, MazeCellTypes::PATH, MAZE_BACKGROUND_COLOR);

	stack.push(seedPoint);
	dirStack.push(createVectorWithPositions());

	while (!stack.empty() && !dirStack.empty()) {
		sf::Vector2i point = stack.top(); stack.pop();
		std::vector<int> pointDir = dirStack.top(); dirStack.pop();

		if (pointDir.empty()) continue;

		int randedDirectionPosition = rand() % pointDir.size();
		int randedDirection = pointDir[randedDirectionPosition];
		pointDir.erase(pointDir.begin() + randedDirectionPosition);

		stack.push(point);
		dirStack.push(pointDir);


		switch (randedDirection) {
		case LEFT:
			breakWall(mazeTable, rows, columns, LEFT, sf::Vector2i(point.x, point.y - 1)); break;
		case RIGHT:
			breakWall(mazeTable, rows, columns, RIGHT, sf::Vector2i(point.x, point.y + 1)); break;
		case UP:
			breakWall(mazeTable, rows, columns, UP, sf::Vector2i(point.x - 1, point.y)); break;
		case DOWN:
			breakWall(mazeTable, rows, columns, DOWN, sf::Vector2i(point.x + 1, point.y)); break;
		}

	}

	//clearing visited to be used by pathfinding algorithms

	clearVisited(mazeTable, rows, columns);

	//adding start and end points
	setStartPoint(&mazeTable[rows - 1][0], rows, startPoint);
	setEndPoint(&mazeTable[0][columns - 1], columns, endPoint);

	clearStacks();
}

void DFSMazeGenerator::clearMazeTable(MazeCell** mazeTable, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mazeTable[i][j].setId(MazeCellTypes::WALL);
			mazeTable[i][j].setColor(MAZE_WALL_COLOR);
			mazeTable[i][j].setVisited(false);
			mazeTable[i][j].setChecked(false);
		}
	}

}

sf::Vector2i DFSMazeGenerator::randSeedPoint(int rows, int columns)
{
	sf::Vector2i seedPoint;
	seedPoint.x = rand() % rows;
	seedPoint.y = rand() % columns;
	return seedPoint;
}

void DFSMazeGenerator::clearVisited(MazeCell** mazeTable, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mazeTable[i][j].setVisited(false);
		}
	}
}

void DFSMazeGenerator::breakWall(MazeCell** mazeTable, int rows, int columns, int direction, sf::Vector2i wallPosition)
{
	sf::Vector2i *cellBehindWallPosition = new sf::Vector2i(0, 0);
	switch (direction) {
	case LEFT: cellBehindWallPosition = new sf::Vector2i(wallPosition.x, wallPosition.y - 1); break;
	case RIGHT:cellBehindWallPosition = new sf::Vector2i(wallPosition.x, wallPosition.y + 1); break;
	case UP: cellBehindWallPosition = new sf::Vector2i(wallPosition.x - 1, wallPosition.y ); break;
	case DOWN:cellBehindWallPosition = new sf::Vector2i(wallPosition.x + 1, wallPosition.y); break;
	}

	if (cellBehindWallPosition->x >= rows || cellBehindWallPosition->x < 0
		|| cellBehindWallPosition->y >= columns || cellBehindWallPosition->y < 0) return;

	if (mazeTable[cellBehindWallPosition->x][cellBehindWallPosition->y].isVisited()) return;

	setCellParameters(&mazeTable[cellBehindWallPosition->x][cellBehindWallPosition->y],
		true, MazeCellTypes::PATH, MAZE_BACKGROUND_COLOR);

	setCellParameters(&mazeTable[wallPosition.x][wallPosition.y],
		true, MazeCellTypes::PATH, MAZE_BACKGROUND_COLOR);

	stack.push(sf::Vector2i(cellBehindWallPosition -> x, cellBehindWallPosition -> y));
	dirStack.push(createVectorWithPositions());

}


std::vector<int> DFSMazeGenerator::createVectorWithPositions() {
	std::vector<int> dir;
	dir.push_back(LEFT);
	dir.push_back(RIGHT);
	dir.push_back(UP);
	dir.push_back(DOWN);

	return dir;
}

void DFSMazeGenerator::setCellParameters(MazeCell* mazeCell, bool visited, int id, sf::Color color)
{
	mazeCell -> setVisited(visited);
	mazeCell -> setId(id);
	mazeCell -> setColor(color);
}

void DFSMazeGenerator::clearStacks()
{
	while (!stack.empty()) stack.pop();
	while (!dirStack.empty()) dirStack.pop();
}

void DFSMazeGenerator::setStartPoint(MazeCell* mazeCell, int rows, sf::Vector2i *startPoint)
{
	setCellParameters(mazeCell, true, MazeCellTypes::START_POINT, START_POINT_COLOR);
	startPoint->x = rows - 1;
	startPoint->y = 0;
}

void DFSMazeGenerator::setEndPoint(MazeCell* mazeCell, int columns, sf::Vector2i* endPoint)
{
	setCellParameters(mazeCell, false, MazeCellTypes::END_POINT, END_POINT_COLOR);
	endPoint->x = 0;
	endPoint->y = columns - 1;
}

