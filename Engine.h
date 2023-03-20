#pragma once

#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "MazeCell.h"
#include "MazeCellTypes.h"
#include "Button.h"

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "Maze!"

#define MAZE_TABLE_WIDTH 24
#define MAZE_TABLE_HEIGHT 15
#define MAZE_TABLE_CELL_SIZE 40
#define MAZE_AREA_X 0
#define MAZE_AREA_Y 0
#define MAZE_AREA_WIDTH MAZE_TABLE_WIDTH * MAZE_TABLE_CELL_SIZE
#define MAZE_AREA_HEIGHT MAZE_TABLE_HEIGHT * MAZE_TABLE_CELL_SIZE

#define END_POINT_COLOR sf::Color{255, 0, 0}
#define START_POINT_COLOR sf::Color{0, 255, 0}

#define BACKGROUND_COLOR sf::Color{51, 51, 255}
#define MAZE_BACKGROUND_COLOR sf::Color{102, 0, 102}
#define MAZE_WALL_COLOR sf::Color{255, 255, 255}

#define BUTTONS_NUM 5

enum MODE{PUT_WALL, PUT_END_POINT, PUT_START_POINT};

class Engine {
private:

	int MODE;
	
	sf::RenderWindow *window;
	MazeCell mazeTable[MAZE_TABLE_WIDTH][MAZE_TABLE_HEIGHT];
	sf::Vector2f mousePosition;

	std::vector<sf::Vector2f> buttonsPos;
	std::vector<sf::Vector2f> buttonsSizes;
	std::vector<sf::Texture> buttonsTextures;
	std::vector<Button> buttons;
	//sf::Font font;


	void updateMousePosition();
	void initializeMazeTable();
	void initializeButtons();
	void addMazeWalls();
	void drawMazeTable();
	sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color color);
	bool isPointInRectangleArea(int pointX, int pointY, int recX, int recY, int recWidth, int recHeight);

	void startMainLoop();
	void handleEvents();

	void initialize();
	void update();
	void draw();

public:
	Engine();
	void start();
};
