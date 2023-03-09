#pragma once

#include <SFML/Graphics.hpp>

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "Maze!"

#define MAZE_TABLE_WIDTH 24
#define MAZE_TABLE_HEIGHT 15
#define MAZE_TABLE_CELL_SIZE 40

class Engine {
private:
	sf::RenderWindow *window;
	int mazeTable[MAZE_TABLE_WIDTH][MAZE_TABLE_HEIGHT];
	sf::Vector2i mousePosition;

	void initializeMazeTable();
	void startMainLoop();

	void initialize();
	void update();
	void draw();

	void drawMazeTable();
	sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color color);

public:
	void start();
};
