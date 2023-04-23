#pragma once

#include "SFML/Graphics.hpp"
#include <stack>
#include "MazeCell.h"
#include "MazeCellTypes.h"
#include "AppConstDef.h"

class DFSMazeGenerator {
private:

	std::stack<sf::Vector2i> stack;
	std::stack<std::vector<int>> dirStack;

	void clearMazeTable(MazeCell** mazeTable, int rows, int columns);
	sf::Vector2i randSeedPoint(int rows, int columns);
	void clearVisited(MazeCell** mazeTable, int rows, int columns);
	void breakWall(MazeCell** mazeTable, int rows, int columns, int direction, sf::Vector2i wallPosition);
	std::vector<int> createVectorWithPositions();
	void setCellParameters(MazeCell* mazeCell, bool visited, int id, sf::Color color);
	void clearStacks();

	void setStartPoint(MazeCell* mazeCell, int row, int column, sf::Vector2i *startPoint);
	void setEndPoint(MazeCell* mazeCell, int row, int column, sf::Vector2i *endPoint);


public:


	void generateMaze(MazeCell** mazeTable, int rows, int columns, sf::Vector2i *startPoint, sf::Vector2i *endPoint);
};
