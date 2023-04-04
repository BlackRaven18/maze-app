#pragma once

#include <SFML/Graphics.hpp>
#include "AppConstDef.h"
#include "Rectangle.h"
#include "MazeCell.h"
#include "MazeCellTypes.h"
#include "Button.h"
#include <queue>
#include "BFSPathfinder.h"
#include "DFSPathfinder.h"


class Engine {
private:

	int MODE;
	
	sf::RenderWindow *window;
	MazeCell mazeTable[MAZE_TABLE_HEIGHT][MAZE_TABLE_WIDTH];
	MazeCell mazeTableCopy[MAZE_TABLE_HEIGHT][MAZE_TABLE_WIDTH];
	sf::Vector2f mousePosition;

	std::vector<sf::Vector2f> buttonsPos;
	std::vector<sf::Vector2f> buttonsSizes;
	std::vector<sf::Texture> buttonsTextures;
	std::vector<Button> buttons;
	
	bool isBfsButtonSelected;
	//sf::Font font;


	void updateMousePosition();
	void initializeMazeTable();
	//------------------
	BFSPathfinder bfsPathfinder;
	DFSPathfinder dfsPathfinder;
	sf::Vector2i startPos;
	sf::Vector2i endPos;

	//------------------

	//------------------
	void copyMazeTable(MazeCell src[][MAZE_TABLE_WIDTH], MazeCell dst[][MAZE_TABLE_WIDTH]);
	//------------------
	void initializeButtons();
	void addMazeElements();
	void removePoint(int pointId);
	void drawMazeTable();
	void saveMazeTable();
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

public:
	Engine();
	void start();
};
