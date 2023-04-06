#include "Engine.h"
#include <iostream>
#include <fstream>
//komentarz do usuniecia
Engine::Engine() {

	mazeTable = createTwoDimDynamicTable<MazeCell>(MAZE_TABLE_ROWS, MAZE_TABLE_COLUMNS);
	mazeTableCopy = createTwoDimDynamicTable<MazeCell>(MAZE_TABLE_ROWS, MAZE_TABLE_COLUMNS);

	this->mazeTableRows = MAZE_TABLE_ROWS;
	this->mazeTableColumns = MAZE_TABLE_COLUMNS;
	this->mazeTableCellSize = MAZE_TABLE_CELL_SIZE;

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

void Engine::initializeMazeTable(int rows, int columns, int cellSize, const char* filename) {
	std::ifstream mazeFile{ filename };

	int** TMP = createTwoDimDynamicTable<int>(rows, columns);

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

	deleteTwoDimDynamicTable<int>(TMP, rows);

	copyMazeTable(mazeTable, mazeTableCopy);
}

template <typename T>
T** Engine::createTwoDimDynamicTable(int rows, int columns) {
	T** table = new T*[rows];
	for (int i = 0; i < rows; i++) {
		table[i] = new T[columns];
	}

	return table;
}


template <typename T>
void Engine::deleteTwoDimDynamicTable(T** tab, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] tab[i];
	}

	delete[] tab;
}



void Engine::copyMazeTable(MazeCell **src, MazeCell **dst) {
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

void Engine::initialize() {
	this->window = new sf::RenderWindow(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE);


	initializeMazeTable(MAZE_TABLE_ROWS, MAZE_TABLE_COLUMNS, MAZE_TABLE_CELL_SIZE, MAZE_FILENAME);
	initializeButtons();
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
			dispose();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
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
				selectSmallMaze();
			}
			else if (buttons[9].isClicked(window)) {
				selectMediumMaze();
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
		bfsPathfinder.findRoad(mazeTable, startPos, endPos);
	}
	else {
		dfsPathfinder.findRoad(mazeTable, startPos, endPos);
	}
}

void Engine::drawButtons() {
	for (auto b : buttons) {
		window->draw(b);
	}
}

void Engine::drawButtonsIllumination() {
	for (int i = 0; i < BUTTONS_NUM; i++) {
		sf::RectangleShape rectangleil = Engine::createRectangle(buttonsPos[i].x, buttonsPos[i].y, buttonsSizes[i].x, buttonsSizes[i].y, sf::Color(128, 128, 128, 128));

		if (mousePosition.x > buttonsPos[i].x  && mousePosition.x < buttonsPos[i].x + buttonsSizes[i].x && mousePosition.y > buttonsPos[i].y  && mousePosition.y < buttonsPos[i].y + buttonsSizes[i].y) {
			window->draw(rectangleil);
		}
	}
}

void Engine::buttonSelect() {
	if (isBfsButtonSelected == true) {
		sf::RectangleShape rectanglesel = Engine::createRectangle(buttonsPos[6].x, buttonsPos[6].y, buttonsSizes[6].x, buttonsSizes[6].y, sf::Color(0, 128, 0, 128));
		window->draw(rectanglesel);
	}
	else {
		sf::RectangleShape rectanglesel = Engine::createRectangle(buttonsPos[7].x, buttonsPos[7].y, buttonsSizes[7].x, buttonsSizes[7].y, sf::Color(0, 128, 0, 128));
		window->draw(rectanglesel);
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

void Engine::addMazeElements()
{

	//checking if mouse is on the maze board

	if (!isPointInRectangleArea(mousePosition.x, mousePosition.y, MAZE_AREA_X, MAZE_AREA_Y, MAZE_AREA_WIDTH, MAZE_AREA_HEIGHT)) {
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
	std::ofstream mazeFile(MAZE_FILENAME);

	for (int i = 0; i < mazeTableRows; i++) {
		for (int j = 0; j < mazeTableColumns; j++) {
			int a = mazeTable[i][j].getId();
			mazeFile << a << " ";
		}
		mazeFile << std::endl;
	}

	mazeFile.close();
}

void Engine::selectMediumMaze() {

	std::cout << "aqui";
	deleteTwoDimDynamicTable(mazeTable, MAZE_TABLE_ROWS);
	deleteTwoDimDynamicTable(mazeTableCopy, MAZE_TABLE_ROWS);

	mazeTable = createTwoDimDynamicTable<MazeCell>(MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS);
	mazeTableCopy = createTwoDimDynamicTable<MazeCell>(MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS);

	this->mazeTableRows = MEDIUM_MAZE_ROWS;
	this->mazeTableColumns = MEDIUM_MAZE_COLUMNS;
	this->mazeTableCellSize = MEDIUM_MAZE_CELL_SIZE;

	initializeMazeTable(MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS, MEDIUM_MAZE_CELL_SIZE, MEDIUM_MAZE_FILENAME);
}

void Engine::selectSmallMaze() {
	/*deleteTwoDimDynamicTable(mazeTable);
	deleteTwoDimDynamicTable(mazeTableCopy, MAZE_TABLE_ROWS);

	mazeTable = createTwoDimDynamicTable<MazeCell>(MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS);
	mazeTableCopy = createTwoDimDynamicTable<MazeCell>(MEDIUM_MAZE_ROWS, MEDIUM_MAZE_COLUMNS);*/
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

void Engine::dispose() {
	deleteTwoDimDynamicTable(mazeTable, MAZE_TABLE_ROWS);
	deleteTwoDimDynamicTable(mazeTableCopy, MAZE_TABLE_ROWS);
}