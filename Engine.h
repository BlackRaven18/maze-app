#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include "AppConstDef.h"
#include "Rectangle.h"
#include "MazeCell.h"
#include "MazeCellTypes.h"
#include "Button.h"
#include "BFSPathfinder.h"
#include "DFSPathfinder.h"
#include "DynamicArrayRepository.h"


class Engine {
private:

	int MODE;
	bool engineRunning;
	
	sf::RenderWindow *window;
	MazeCell **mazeTable;
	MazeCell **mazeTableCopy;
	sf::Vector2f mousePosition;

	std::vector<sf::Vector2f> buttonsPos;
	std::vector<sf::Vector2f> buttonsSizes;
	std::vector<sf::Texture> buttonsTextures;
	std::vector<Button> buttons;
	
	bool isBfsButtonSelected;
	
	BFSPathfinder bfsPathfinder;
	DFSPathfinder dfsPathfinder;

	sf::Vector2i startPoint;
	sf::Vector2i endPoint;

	int mazeSizeType;
	int mazeTableRows;
	int mazeTableColumns;
	int mazeTableCellSize;
	

	void updateMousePosition();
	void initializeMazeTable(int rows, int columns, int cellSize, const char* filename);
	//------------------


	void setMazeParameters(int size, int rows, int columns, int cellSize);

	void copyMazeTable(MazeCell **src, MazeCell **dst);
	//------------------
	void initializeButtons();
	void addMazeElements();
	void removePoint(int pointId);
	void drawMazeTable();
	void saveMazeTable();

	void selectSmallMaze();
	void selectMediumMaze();
	void selectBigMaze();

	void drawButtonsIllumination();
	void drawButtons();
	sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color color);
	bool isPointInRectangleArea(int pointX, int pointY, int recX, int recY, int recWidth, int recHeight);

	void startMainLoop();
	void handleEvents();
	void buttonSelect();

	void initialize();
	void update();
	void draw();

	void dispose();

public:
	Engine();
	void start();
	void stop();
};
