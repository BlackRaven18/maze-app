#include "MazeCell.h"

MazeCell::MazeCell() {

}

MazeCell::MazeCell(int x, int y, int width, int height, sf::Color color, int id) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
	this->id = id;
}

int MazeCell::getId() {
	return id;
}

void MazeCell::setId(int id) {
	this->id = id;
}