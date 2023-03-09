#include "Engine.h"


void Engine::start() {
	initialize();
	startMainLoop();
}

void Engine::initializeMazeTable() {
	for (int i = 0; i < MAZE_TABLE_WIDTH; i++) {
		for (int j = j = 0; j < MAZE_TABLE_HEIGHT; j++) {
			mazeTable[i][j] = 1;
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

void Engine::update() {
	mousePosition = sf::Mouse::getPosition(*window);
	sf::Event event;
	while (window -> pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window -> close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window -> close();
		}
	}
}

void Engine::draw() {
	window->clear();

	window->display();

}