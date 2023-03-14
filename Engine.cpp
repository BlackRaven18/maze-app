#include "Engine.h"
#include <iostream>

Engine::Engine() {

}

void Engine::start() {
	initialize();
	startMainLoop();
}

void Engine::updateMousePosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}

void Engine::initializeMazeTable() {
	for (int i = 0; i < MAZE_TABLE_WIDTH; i++) {
		for (int j = j = 0; j < MAZE_TABLE_HEIGHT; j++) {
			mazeTable[i][j].setPosition(i * MAZE_TABLE_CELL_SIZE, j * MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setSize(MAZE_TABLE_CELL_SIZE, MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setColor(sf::Color::White);
			mazeTable[i][j].setId(MazeCellTypes::PATH);	
		}
	}
}

void Engine::initialize() {
	this->window = new sf::RenderWindow(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE);

	initializeMazeTable();
}

void Engine::startMainLoop() {
	while (window->isOpen()) {
		update();
		draw();
	}
}

void Engine::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window->close();
		}

		//if (event.type == sf::Event::Resized)
		//{
		//	// update the view to the new size of the window
		//	sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		//	window -> setView(sf::View(visibleArea));
		//}
	}
}

void Engine::update() {
	handleEvents();
	updateMousePosition();
}



void Engine::draw() {
	window->clear();

	drawMazeTable();
	drawMaze();

	window->display();

}

void Engine::drawMaze()
{

	//TODO: napisaæ funkcje która sprawdzi czy punkt(albo myszka) jest aktualnie wewn¹trz danego obszaru; przyda sie do 
	//sprawdzania czy myszka jest na obszarze do rysowania i do znalezienia elementu tablicy do pokolorowania 
	
	//checking if mouse is on the maze board

	if (mousePosition.x > MAZE_TABLE_WIDTH * MAZE_TABLE_CELL_SIZE && mousePosition.y > MAZE_TABLE_HEIGHT * MAZE_TABLE_CELL_SIZE) {
		return;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return;
	}

	int i = mousePosition.x / MAZE_TABLE_CELL_SIZE;
	int j = mousePosition.y / MAZE_TABLE_CELL_SIZE;

	if (i < MAZE_TABLE_WIDTH && j < MAZE_TABLE_HEIGHT)
		mazeTable[i][j].setColor(sf::Color::Green);
}

void Engine::drawMazeTable() {
	for(int i = 0; i < MAZE_TABLE_WIDTH; i++)
		for (int j = 0; j < MAZE_TABLE_HEIGHT; j++) {
			mazeTable[i][j].draw(window);

		}

}

sf::RectangleShape Engine::createRectangle(int x, int y, int width, int height, sf::Color color) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(color);
	return rectangle;
}