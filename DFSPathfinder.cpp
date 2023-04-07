#include "DFSPathfinder.h"

DFSPathfinder::DFSPathfinder()
{
    this->running = false;
    this->initializedWithStartData = false;
    this->exitFound = false;
}

void DFSPathfinder::checkChamber(MazeCell **mazeTable, int rows, int columns, int chamberId, int x, int y)
{
    if (x < 0 || y < 0 || x >= rows || y >= columns) return;

    if (mazeTable[x][y].getId() == MazeCellTypes::WALL) return;
    if (mazeTable[x][y].getId() == MazeCellTypes::START_POINT) return;
    if (mazeTable[x][y].isChecked()) return;

    if (mazeTable[x][y].getId() == MazeCellTypes::PATH) {
        mazeTable[x][y].setColor(MAZE_VISITED_CELL_COLOR);
    }

    mazeTable[x][y].setId(chamberId);
    mazeTable[x][y].setChecked(true);

    stack.push(sf::Vector2i(x, y));
}

void DFSPathfinder::findRoad(MazeCell **mazeTable, int rows, int columns, sf::Vector2i startPoint, sf::Vector2i endPoint)
{
    if (!isRunning()) {
        return;
    }

    if (!isInitializedWithStartData()) {
        mazeTable[startPoint.x][startPoint.y].setVisited(true);
        stack.push(startPoint);

        setInitializedWithStartData(true);
    }

    if (isExitFound()) {
        if (!mazeTable[tmpPoint.x][tmpPoint.y].isVisited()) {
            switch (mazeTable[tmpPoint.x][tmpPoint.y].getId()) {
            case UP: mazeTable[tmpPoint.x][tmpPoint.y++].setVisited(true); break;
            case RIGHT: mazeTable[tmpPoint.x--][tmpPoint.y].setVisited(true); break;
            case DOWN: mazeTable[tmpPoint.x][tmpPoint.y--].setVisited(true); break;
            case LEFT: mazeTable[tmpPoint.x++][tmpPoint.y].setVisited(true); break;
            }
            mazeTable[tmpPoint.x][tmpPoint.y].setColor(MAZE_TRACK_COLOR);

            sf::sleep(PATHFINDER_DRAWING_PATH_DELAY);
        }

        if (tmpPoint == startPoint) {
            std::cout << "Znaleziono droge!" << std::endl;
            stop();
        }

        return;
    }

    if (!isExitFound()) {

        if (stack.empty()) {
            stop();
            return;
        }

        sf::Vector2i point = stack.top();
        stack.pop();

        sf::sleep(PATHFINDER_CHECKED_CELLS_DELAY);

        if (point.x == endPoint.x && point.y == endPoint.y) {
            this->tmpPoint = point;
            setExitFound(true);
            return;
        }

        if (point.y - 1 < columns) checkChamber(mazeTable, rows, columns, UP, point.x, point.y - 1);
        if (point.x + 1 < rows) checkChamber(mazeTable, rows, columns, RIGHT, point.x + 1, point.y);
        if (point.y + 1 >= 0) checkChamber(mazeTable, rows, columns, DOWN, point.x, point.y + 1);
        if (point.x - 1 >= 0) checkChamber(mazeTable, rows, columns, LEFT, point.x - 1, point.y);
    }
}

bool DFSPathfinder::isRunning()
{
    return this->running;
}

void DFSPathfinder::start() {
    this->running = true;
}

void DFSPathfinder::stop()
{
    this->running = false;
    this->initializedWithStartData = false;
    this->exitFound = false;
    this->tmpPoint.x = this->tmpPoint.y = -1;
    clearStack();
}

void DFSPathfinder::clearStack()
{
    while (!stack.empty()) {
        stack.pop();
    }
}

void DFSPathfinder::setInitializedWithStartData(bool initializedWithStartData)
{
    this->initializedWithStartData = initializedWithStartData;
}

bool DFSPathfinder::isInitializedWithStartData()
{
    return this->initializedWithStartData;
}

void DFSPathfinder::setExitFound(bool exitFound) {
    this->exitFound = exitFound;
}

bool DFSPathfinder::isExitFound()
{
    return this->exitFound;
}