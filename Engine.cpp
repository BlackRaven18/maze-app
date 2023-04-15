#include "Engine.h"
#include <iostream>
#include <fstream>
//komentarz do usuniecia
Engine::Engine() {

	this->MODE = PUT_WALL;

	mazeTable = DynamicArrayRepository<MazeCell>::createTwoDimDynamicTable(SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS);
	mazeTableCopy = DynamicArrayRepository<MazeCell>::createTwoDimDynamicTable(SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS);

	setMazeParameters(SMALL, SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS, SMALL_MAZE_CELL_SIZE);
}

void Engine::start() {
	initialize();
	startMainLoop();
}

void Engine::stop() {
	this->engineRunning = false;
}

void Engine::initialize() {
	this->window = new sf::RenderWindow(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE);

	this->engineRunning = true;

	isAlgorithmRunning = false;

	initializeMazeTable(SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS, SMALL_MAZE_CELL_SIZE, SMALL_MAZE_FILENAME);
	initializeButtons();
}

void Engine::startMainLoop() {
	elapsedTime = 0.0f;
	
	while (window->isOpen()) {
		elapsedTime += clock.restart().asSeconds();

		update();
		
		draw();
	}

	if (!engineRunning) {
		dispose();
	}
}

void Engine::handleEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{


		if (event.type == sf::Event::Closed) {
			stop();
			window->close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			stop();
			window->close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (buttons[RESTART_BTN]->isClicked(window))
			{
				if (isBfsButtonSelected) {
					bfsPathfinder.stop();
				}
				else {
					dfsPathfinder.stop();
				}
				isAlgorithmRunning = false;
				copyMazeTable(mazeTableCopy, mazeTable);
			}

			if (!isAlgorithmRunning) {
				if (buttons[START_BTN]->isClicked(window)) {
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
				}

				//TODO: pomy�le� czy to powinno tu by�

				if (buttons[BOXWHITE_BTN]->isClicked(window))
				{
					this->MODE = PUT_WALL;
				}
				else if (buttons[BOXGREEN_BTN]->isClicked(window)) {
					this->MODE = PUT_START_POINT;
				}
				else if (buttons[BOXRED_BTN]->isClicked(window)) {
					this->MODE = PUT_END_POINT;
				}
				else if (buttons[SAVE_BTN]->isClicked(window)) {
					saveMazeTable();
				}
				else if (buttons[BFS_BTN]->isClicked(window)) {
					isBfsButtonSelected = true;
				}
				else if (buttons[DFS_BTN]->isClicked(window)) {
					isBfsButtonSelected = false;
				}
				else if (buttons[ONEX_BTN]->isClicked(window)) {
					selectMaze(mazeSizeType, SMALL, SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS, SMALL_MAZE_CELL_SIZE, SMALL_MAZE_FILENAME);
				}
				else if (buttons[TWOX_BTN]->isClicked(window)) {
					selectMaze(mazeSizeType, MEDIUM, MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS, MEDIUM_MAZE_CELL_SIZE, MEDIUM_MAZE_FILENAME);
				}
				else if (buttons[FOURX_BTN]->isClicked(window)) {
					selectMaze(mazeSizeType, BIG, BIG_MAZE_ROWS, BIG_MAZE_COLUMNS, BIG_MAZE_CELL_SIZE, BIG_MAZE_FILENAME);
				}
			}
		}
	}
}


void Engine::update() {
	handleEvents();
	updateMousePosition();

	if ((bfsPathfinder.isRunning() == true) || (dfsPathfinder.isRunning() == true)) {
		isAlgorithmRunning = true;
	}

	if (isBfsButtonSelected) {
		if (bfsPathfinder.isExitFound()) {
			if (elapsedTime >= PATHFINDER_DRAWING_PATH_DELAY.asSeconds()) {
				bfsPathfinder.drawRoad(mazeTable, mazeTableRows, mazeTableColumns,startPoint);
				elapsedTime = 0.0f;
			}
		}
		else {
			if (elapsedTime >= PATHFINDER_CHECKED_CELLS_DELAY.asSeconds()) {
				bfsPathfinder.findRoad(mazeTable, mazeTableRows, mazeTableColumns, startPoint, endPoint);
				elapsedTime = 0.0f;
			}
		}
	}
	else {
		if (dfsPathfinder.isExitFound()) {
			if (elapsedTime >= PATHFINDER_DRAWING_PATH_DELAY.asSeconds()) {
				dfsPathfinder.drawRoad(mazeTable, mazeTableRows, mazeTableColumns, startPoint);
				elapsedTime = 0.0f;
			}
		}
		else {
			if (elapsedTime >= PATHFINDER_CHECKED_CELLS_DELAY.asSeconds()) {
				dfsPathfinder.findRoad(mazeTable, mazeTableRows, mazeTableColumns, startPoint, endPoint);
				elapsedTime = 0.0f;
			}
		}
	}
		
}

void Engine::draw() {
	window->clear(BACKGROUND_COLOR);

	drawMazeTable();
	addMazeElements();
	drawButtons();
	drawButtonsIllumination();
	buttonSelect();
	
	window->display();
}


void Engine::updateMousePosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}

void Engine::initializeMazeTable(int rows, int columns, int cellSize, const char* filename) {
	std::ifstream mazeFile{ filename };

	int** TMP = DynamicArrayRepository<int>::createTwoDimDynamicTable(rows, columns);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			mazeFile >> TMP[i][j];
		}
	}
	mazeFile.close();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mazeTable[i][j].setPosition(j * cellSize, i * cellSize);
			mazeTable[i][j].setSize(cellSize, cellSize);
			mazeTable[i][j].setId(TMP[i][j]);
			mazeTable[i][j].setVisited(false);
			mazeTable[i][j].setChecked(false);

			switch (mazeTable[i][j].getId()) {
			case MazeCellTypes::PATH: mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR); break;
			case MazeCellTypes::WALL: mazeTable[i][j].setColor(MAZE_WALL_COLOR); break;
			case MazeCellTypes::START_POINT: mazeTable[i][j].setColor(START_POINT_COLOR);
				startPoint.x = i;
				startPoint.y = j;
				break;
			case MazeCellTypes::END_POINT: mazeTable[i][j].setColor(END_POINT_COLOR);
				endPoint.x = i;
				endPoint.y = j;
				break;
			}
		}
	}

	DynamicArrayRepository<int>::deleteTwoDimDynamicTable(TMP, rows);

	copyMazeTable(mazeTable, mazeTableCopy);
}

void Engine::copyMazeTable(MazeCell** src, MazeCell** dst){
	for (int i = 0; i < mazeTableRows; i++) {
		for (int j = 0; j < mazeTableColumns; j++) {
			dst[i][j] = src[i][j];
		}
	}
}


void Engine::initializeButtons() {
	//font.loadFromFile("arial.ttf");
	buttons.resize(BUTTONS_NUM);

	buttons[START_BTN] = new Button("Textures/start.png", { 100,630 }, sf::Color::White, { 100,50 });
	buttons[RESTART_BTN] = new Button("Textures/restart.png", { 250,630 }, sf::Color::White, { 100,50 });
	buttons[BOXWHITE_BTN] = new Button("Textures/boxwhite.png", { 1100,200 }, sf::Color::White, { 72,72 });
	buttons[BOXGREEN_BTN] = new Button("Textures/boxgreen.png", { 1100,300 }, sf::Color::White, { 72,72 });
	buttons[BOXRED_BTN] = new Button("Textures/boxred.png", { 1100,400 }, sf::Color::White, { 72,72 });
	buttons[SAVE_BTN] = new Button("Textures/save.png", { 1100,500 }, sf::Color::White, { 72,72 });
	buttons[BFS_BTN] = new Button("Textures/BFS_BTN.png", { 400,630 }, sf::Color::White, { 78,50 });
	buttons[DFS_BTN] = new Button("Textures/DFS_BTN.png", { 482,630 }, sf::Color::White, { 78,50 });
	buttons[ONEX_BTN] = new Button("Textures/1x.png", { 1012,100 }, sf::Color::White, { 50,50 });
	buttons[TWOX_BTN] = new Button("Textures/2x.png", { 1112,100 }, sf::Color::White, { 50,50 });
	buttons[FOURX_BTN] = new Button("Textures/4x.png", { 1212,100 }, sf::Color::White, { 50,50 });

	isBfsButtonSelected = true;
}


void Engine::drawButtons() {
	for (auto b : buttons) {
		window->draw(*b);
	}
}

void Engine::drawButtonsIllumination() {
	for (int i = 0; i < BUTTONS_NUM; i++) {
		sf::RectangleShape rectangleIlumination = ShapesAndCollisionsRep::createRectangle(buttons[i]->getX(), buttons[i]->getY(),
			buttons[i]->getWidth(), buttons[i]->getHeight(), sf::Color(128, 128, 128, 128));


		if (ShapesAndCollisionsRep::isPointInRectangleArea(mousePosition.x, mousePosition.y, 
			buttons[i]->getX(), buttons[i]->getY(),buttons[i]->getWidth(), buttons[i]->getHeight())) {
			window->draw(rectangleIlumination);

		}
	}
}

void Engine::buttonSelect() {

	if (isBfsButtonSelected == true) {
		sf::RectangleShape rectanglesel = ShapesAndCollisionsRep::createRectangle(
			buttons[BFS_BTN]->getX(), buttons[BFS_BTN]->getY(), buttons[BFS_BTN]->getWidth(), buttons[BFS_BTN]->getHeight(), sf::Color(0, 128, 0, 128));
		window->draw(rectanglesel);
	}
	else {
		sf::RectangleShape rectanglesel = ShapesAndCollisionsRep::createRectangle(
			buttons[DFS_BTN]->getX(), buttons[DFS_BTN]->getY(), buttons[DFS_BTN]->getWidth(), buttons[DFS_BTN]->getHeight(), sf::Color(0, 128, 0, 128));
		window->draw(rectanglesel);
	}
}


void Engine::addMazeElements()
{

	//checking if mouse is on the maze board

	if (!ShapesAndCollisionsRep::isPointInRectangleArea(mousePosition.x, mousePosition.y, MAZE_AREA_X, MAZE_AREA_Y, MAZE_AREA_WIDTH, MAZE_AREA_HEIGHT)) {
		return;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		return;
	}

	//TODO: improve code structure to eliminate repetability
	int i = mousePosition.y / mazeTableCellSize;
	int j = mousePosition.x / mazeTableCellSize;

	if (isAlgorithmRunning) {
		return;
	}

	if (i < mazeTableRows && j < mazeTableColumns) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (MODE == PUT_WALL) {
				mazeTable[i][j].setId(MazeCellTypes::WALL);
				mazeTable[i][j].setColor(MAZE_WALL_COLOR);
			}
			else if (MODE == PUT_END_POINT) {
				removePoint(MazeCellTypes::END_POINT);
				mazeTable[i][j].setId(MazeCellTypes::END_POINT);
				mazeTable[i][j].setColor(END_POINT_COLOR);
				endPoint.x = i;
				endPoint.y = j;

			}
			else if (MODE == PUT_START_POINT) {
				removePoint(MazeCellTypes::START_POINT);
				mazeTable[i][j].setId(MazeCellTypes::START_POINT);
				mazeTable[i][j].setColor(START_POINT_COLOR);
				startPoint.x = i;
				startPoint.y = j;
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			mazeTable[i][j].setId(MazeCellTypes::PATH);
			mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR);
		}
	}
}

void Engine::removePoint(int pointId) {
	for (int i = 0; i < mazeTableRows; i++) {
		for (int j = 0; j < mazeTableColumns; j++) {
			if (mazeTable[i][j].getId() == pointId) {
				mazeTable[i][j].setId(MazeCellTypes::PATH);
				mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR);
			}
		}
	}
}

void Engine::drawMazeTable() {
	for (int i = 0; i < mazeTableRows; i++) {
		for (int j = j = 0; j < mazeTableColumns; j++) {
			mazeTable[i][j].draw(window);
		}
	}
}

void Engine::saveMazeTable() {

	std::ofstream mazeFile;

	switch (mazeSizeType) {
	case SMALL: mazeFile = std::ofstream(SMALL_MAZE_FILENAME); break;
	case MEDIUM: mazeFile = std::ofstream(MEDIUM_MAZE_FILENAME); break;
	case BIG: mazeFile = std::ofstream(BIG_MAZE_FILENAME); break;
	}

	//std::ofstream mazeFile(SMALL_MAZE_FILENAME);

	for (int i = 0; i < mazeTableRows; i++) {
		for (int j = 0; j < mazeTableColumns; j++) {
			int a = mazeTable[i][j].getId();
			mazeFile << a << " ";
		}
		mazeFile << std::endl;
	}

	mazeFile.close();
}

void Engine::selectMaze(int oldType, int newType, int rows, int columns, int cellSize, const char* filename) {
	int oldRows = 0;
	
	if (oldType == newType) return;

	switch (oldType) {
	case SMALL: oldRows = SMALL_MAZE_ROWS; break;
	case MEDIUM:oldRows = MEDIUM_MAZE_ROWS; break;
	case BIG:oldRows = BIG_MAZE_ROWS; break;
	}

	mazeTable = DynamicArrayRepository<MazeCell>::recreateTwoDimDynamicTable(mazeTable, oldRows, rows, columns);
	mazeTableCopy = DynamicArrayRepository<MazeCell>::recreateTwoDimDynamicTable(mazeTableCopy, oldRows, rows, columns);

	setMazeParameters(newType, rows, columns, cellSize);

	initializeMazeTable(rows, columns, cellSize, filename);

}


void Engine::setMazeParameters(int size, int rows, int columns, int cellSize) {
	this->mazeSizeType = size;
	this->mazeTableRows = rows;
	this->mazeTableColumns = columns;
	this->mazeTableCellSize = cellSize;
}

void Engine::dispose() {
	DynamicArrayRepository<MazeCell>::deleteTwoDimDynamicTable(mazeTable, SMALL_MAZE_ROWS);
	DynamicArrayRepository<MazeCell>::deleteTwoDimDynamicTable(mazeTableCopy, SMALL_MAZE_ROWS);
}