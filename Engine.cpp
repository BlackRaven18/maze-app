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

	initializeMazeTable(SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS, SMALL_MAZE_CELL_SIZE, SMALL_MAZE_FILENAME);
	initializeButtons();
}

void Engine::startMainLoop() {
	while (window->isOpen()) {
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
			}

			if (buttons[1].isClicked(window))
			{
				if (isBfsButtonSelected) {
					bfsPathfinder.stop();
				}
				else {
					dfsPathfinder.stop();
				}
				
				copyMazeTable(mazeTableCopy, mazeTable);
			}

			//TODO: pomy�le� czy to powinno tu by�

			if (buttons[2].isClicked(window))
			{
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
			else if (buttons[6].isClicked(window)) {
				isBfsButtonSelected = true;
				std::cout << "BFS" << std::endl;
			}
			else if (buttons[7].isClicked(window)) {
				isBfsButtonSelected = false;
				std::cout << "DFS" << std::endl;
			}
			else if (buttons[8].isClicked(window)) {
				selectMaze(mazeSizeType, SMALL, SMALL_MAZE_ROWS, SMALL_MAZE_COLUMNS, SMALL_MAZE_CELL_SIZE, SMALL_MAZE_FILENAME);
			}
			else if (buttons[9].isClicked(window)) {
				selectMaze(mazeSizeType, MEDIUM, MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS, MEDIUM_MAZE_CELL_SIZE, MEDIUM_MAZE_FILENAME);
			}
			else if (buttons[10].isClicked(window)) {
				selectMaze(mazeSizeType, BIG, BIG_MAZE_ROWS, BIG_MAZE_COLUMNS, BIG_MAZE_CELL_SIZE, BIG_MAZE_FILENAME);
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

void Engine::update() {
	handleEvents();
	updateMousePosition();

	if (isBfsButtonSelected) {
		bfsPathfinder.findRoad(mazeTable, mazeTableRows, mazeTableColumns,startPoint, endPoint);
	}
	else {
		dfsPathfinder.findRoad(mazeTable, mazeTableRows, mazeTableColumns, startPoint, endPoint);
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
	buttonsTextures.resize(BUTTONS_NUM);
	buttonsTextures[0].loadFromFile("Textures/start.png");
	buttonsTextures[1].loadFromFile("Textures/restart.png");
	buttonsTextures[2].loadFromFile("Textures/boxwhite.png");
	buttonsTextures[3].loadFromFile("Textures/boxgreen.png");
	buttonsTextures[4].loadFromFile("Textures/boxred.png");
	buttonsTextures[5].loadFromFile("Textures/save.png");
	buttonsTextures[6].loadFromFile("Textures/BFS_BTN.png");
	buttonsTextures[7].loadFromFile("Textures/DFS_BTN.png");
	buttonsTextures[8].loadFromFile("Textures/1x.png");
	buttonsTextures[9].loadFromFile("Textures/2x.png");
	buttonsTextures[10].loadFromFile("Textures/4x.png");

	buttonsPos = { {100,630}, {250,630}, {1100,200}, {1100,300}, {1100,400}, {1100,500}, {400,630}, {482,630}, {1012, 100}, {1112, 100}, {1212, 100} };
	buttonsSizes = { {100,50}, {100,50}, {72,72}, {72,72}, {72,72}, {72,72}, {78,50}, {78,50}, {50,50}, {50,50}, {50, 50} };

	buttons.resize(BUTTONS_NUM);
	for (int i = 0; i < BUTTONS_NUM; i++) {
		buttons[i] = Button(buttonsTextures[i], buttonsPos[i], sf::Color::White, buttonsSizes[i]);
	}

	isBfsButtonSelected = true;
}


void Engine::drawButtons() {
	for (auto b : buttons) {
		window->draw(b);
	}
}

void Engine::drawButtonsIllumination() {
	for (int i = 0; i < BUTTONS_NUM; i++) {
		sf::RectangleShape rectangleIlumination = ShapesAndCollisionsRep::createRectangle(buttonsPos[i].x, buttonsPos[i].y,
			buttonsSizes[i].x, buttonsSizes[i].y, sf::Color(128, 128, 128, 128));


		if (ShapesAndCollisionsRep::isPointInRectangleArea(mousePosition.x, mousePosition.y, 
			buttonsPos[i].x, buttonsPos[i].y, buttonsSizes[i].x, buttonsSizes[i].y)) {
			window->draw(rectangleIlumination);

		}
	}
}

void Engine::buttonSelect() {
	if (isBfsButtonSelected == true) {
		sf::RectangleShape rectanglesel = ShapesAndCollisionsRep::createRectangle(buttonsPos[6].x, buttonsPos[6].y, buttonsSizes[6].x, buttonsSizes[6].y, sf::Color(0, 128, 0, 128));
		window->draw(rectanglesel);
	}
	else {
		sf::RectangleShape rectanglesel = ShapesAndCollisionsRep::createRectangle(buttonsPos[7].x, buttonsPos[7].y, buttonsSizes[7].x, buttonsSizes[7].y, sf::Color(0, 128, 0, 128));
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