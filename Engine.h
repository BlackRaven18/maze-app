#pragma once

#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Button.h"

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "Maze!"

#define MAZE_TABLE_WIDTH 24
#define MAZE_TABLE_HEIGHT 15
#define MAZE_TABLE_CELL_SIZE 40

class Engine {
private:
	sf::RenderWindow *window;
	Rectangle mazeTable[MAZE_TABLE_WIDTH][MAZE_TABLE_HEIGHT];
	sf::Vector2f mousePosition;

	sf::Font font;
	Button textButton;

	void updateMousePosition();
	void initializeMazeTable();
	void initializeButtons();
	void drawMaze();
	void drawMazeTable();
	sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color color);

	void startMainLoop();
	void handleEvents();

	void initialize();
	void update();
	void draw();

public:
	Engine();
	void start();
};
