#include "Engine.h"
#include <iostream>
#include <fstream>
//komentarz do usuniecia
Engine::Engine() {
	this->MODE = PUT_WALL;
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
	std::ifstream mazeFile{ MAZE_FILENAME };
	int TMP[MAZE_TABLE_HEIGHT][MAZE_TABLE_WIDTH]{};
	for (int i{}; i != MAZE_TABLE_HEIGHT; ++i) {
		for (int j{}; j != MAZE_TABLE_WIDTH; ++j) {
			mazeFile >> TMP[i][j];
		}
	}
	mazeFile.close();

	for (int i = 0; i < MAZE_TABLE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_TABLE_WIDTH; j++) {
			mazeTable[i][j].setPosition(j * MAZE_TABLE_CELL_SIZE, i * MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setSize(MAZE_TABLE_CELL_SIZE, MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setId(TMP[i][j]);
			mazeTable[i][j].setVisited(false);

			switch (mazeTable[i][j].getId()) {
			case MazeCellTypes::PATH: mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR); break;
			case MazeCellTypes::WALL: mazeTable[i][j].setColor(MAZE_WALL_COLOR); break;
			case MazeCellTypes::START_POINT: mazeTable[i][j].setColor(START_POINT_COLOR);
				startPos.x = i;
				startPos.y = j;
				break;
			case MazeCellTypes::END_POINT: mazeTable[i][j].setColor(END_POINT_COLOR);
				endPos.x = i;
				endPos.y = j;
				break;
			}
		}
	}

	copyMazeTable(mazeTable, mazeTableCopy);
}



void Engine::copyMazeTable(MazeCell src[][MAZE_TABLE_WIDTH], MazeCell dst[][MAZE_TABLE_WIDTH]) {
	for (int i = 0; i < MAZE_TABLE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_TABLE_WIDTH; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

void Engine::initializeButtons() {
	//font.loadFromFile("arial.ttf");
	buttonsTextures.resize(BUTTONS_NUM);
	buttonsTextures[0].loadFromFile("Textures/start.png");
	buttonsTextures[1].loadFromFile("Textures/restart.png");
	buttonsTextures[2].loadFromFile("Textures/boxwhite.png");
	buttonsTextures[3].loadFromFile("Textures/boxgreen.png");
	buttonsTextures[4].loadFromFile("Textures/boxred.png");
	buttonsTextures[5].loadFromFile("Textures/save.png");
	buttonsTextures[6].loadFromFile("Textures/BFS_BTN.png");
	buttonsTextures[7].loadFromFile("Textures/DFS_BTN.png");

	buttonsPos = { {100,630}, {250,630}, {1100, 200}, {1100,300}, {1100,400}, {1100,500}, { 400, 630 }, {482, 630} };
	buttonsSizes = { {100,50}, {100,50}, {72,72}, {72,72}, {72,72}, {72,72}, {78, 50}, {78, 50} };

	buttons.resize(BUTTONS_NUM);
	for (int i = 0; i < BUTTONS_NUM; i++) {
		buttons[i] = Button(buttonsTextures[i], buttonsPos[i], sf::Color::White, buttonsSizes[i]);
	}

	isBfsButtonSelected = true;
}

void Engine::initialize() {
	this->window = new sf::RenderWindow(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE);

	initializeMazeTable();
	initializeButtons();
}

void Engine::startMainLoop() {
	while (window->isOpen()) {
		update();
		draw();
	}
}

void Engine::handleEvents() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window->close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (buttons[0].isClicked(window)) {
				if (isBfsButtonSelected == true) {
					// BFS algorithm
					if (!bfsPathfinder.isRunning()) {
						copyMazeTable(mazeTable, mazeTableCopy);
						bfsPathfinder.start();
					}
				}

				if (isBfsButtonSelected == false) {
					// DFS algorithm
					if (!dfsPathfinder.isRunning()) {
						copyMazeTable(mazeTable, mazeTableCopy);
						dfsPathfinder.start();
					}
				}

				if (buttons[1].isClicked(window)) {
					if (isBfsButtonSelected) {
						bfsPathfinder.stop();
					}
					else {
						dfsPathfinder.stop();
					}

					copyMazeTable(mazeTableCopy, mazeTable);
				}

				//TODO: pomyœleæ czy to powinno tu byæ

				if (buttons[2].isClicked(window)) {
					this->MODE = PUT_WALL;
				}
				else if (buttons[3].isClicked(window)) {
					this->MODE = PUT_START_POINT;
				}
				else if (buttons[4].isClicked(window)) {
					this->MODE = PUT_END_POINT;
				}
				else if (buttons[5].isClicked(window)) {
					saveMazeTable();
				}

				if (buttons[6].isClicked(window)) {
					isBfsButtonSelected = true;
					std::cout << "BFS" << std::endl;
				}

				if (buttons[7].isClicked(window)) {
					isBfsButtonSelected = false;
					std::cout << "DFS" << std::endl;
				}
			}

			//if (event.type == sf::Event::Resized)
			//{
			//	// update the view to the new size of the window
			//	sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			//	window -> setView(sf::View(visibleArea));
			//}
		}
	}
}

void Engine::update() {
	handleEvents();
	updateMousePosition();

	if (isBfsButtonSelected) {
		bfsPathfinder.findRoad(mazeTable, startPos, endPos);
	}
	else {
		dfsPathfinder.findRoad(mazeTable, startPos, endPos);
	}
}



void Engine::draw() {
	window->clear(BACKGROUND_COLOR);

	drawMazeTable();
	addMazeElements();

	for (auto b : buttons) {
		window->draw(b);
	}

	window->display();
}

void Engine::addMazeElements() {

	//checking if mouse is on the maze board

	if (!isPointInRectangleArea(mousePosition.x, mousePosition.y, MAZE_AREA_X, MAZE_AREA_Y, MAZE_AREA_WIDTH, MAZE_AREA_HEIGHT)) {
		return;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		return;
	}

	//TODO: improve code structure to eliminate repetability
	int i = mousePosition.y / MAZE_TABLE_CELL_SIZE;
	int j = mousePosition.x / MAZE_TABLE_CELL_SIZE;

	if (i < MAZE_TABLE_HEIGHT && j < MAZE_TABLE_WIDTH) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (MODE == PUT_WALL) {
				mazeTable[i][j].setId(MazeCellTypes::WALL);
				mazeTable[i][j].setColor(MAZE_WALL_COLOR);
			}
			else if (MODE == PUT_END_POINT) {
				removePoint(MazeCellTypes::END_POINT);
				mazeTable[i][j].setId(MazeCellTypes::END_POINT);
				mazeTable[i][j].setColor(END_POINT_COLOR);
				endPos.x = i;
				endPos.y = j;

			}
			else if (MODE == PUT_START_POINT) {
				removePoint(MazeCellTypes::START_POINT);
				mazeTable[i][j].setId(MazeCellTypes::START_POINT);
				mazeTable[i][j].setColor(START_POINT_COLOR);
				startPos.x = i;
				startPos.y = j;
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			mazeTable[i][j].setId(MazeCellTypes::PATH);
			mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR);
		}
	}
}

void Engine::removePoint(int pointId) {
	for (int i = 0; i < MAZE_TABLE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_TABLE_WIDTH; j++) {
			if (mazeTable[i][j].getId() == pointId) {
				mazeTable[i][j].setId(MazeCellTypes::PATH);
				mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR);
			}
		}
	}
}

void Engine::drawMazeTable() {
	for (int i = 0; i < MAZE_TABLE_HEIGHT; i++) {
		for (int j = j = 0; j < MAZE_TABLE_WIDTH; j++) {
			mazeTable[i][j].draw(window);
		}
	}


}

void Engine::saveMazeTable() {
	std::ofstream mazeFile(MAZE_FILENAME);

	for (int i = 0; i < MAZE_TABLE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_TABLE_WIDTH; j++) {
			int a = mazeTable[i][j].getId();
			mazeFile << a << " ";
		}
		mazeFile << std::endl;
	}

	mazeFile.close();
}


sf::RectangleShape Engine::createRectangle(int x, int y, int width, int height, sf::Color color) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(color);
	return rectangle;
}

bool Engine::isPointInRectangleArea(int pointX, int pointY, int recX, int recY, int recWidth, int recHeight) {
	if (pointX >= recX && pointX <= recX + recWidth
		&& pointY >= recY && pointY <= recY + recHeight) {
		return true;
	}

	return false;
}