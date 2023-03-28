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
	this->visited = false;
	this->checked = false;
}

int MazeCell::getId() {
	return id;
}

void MazeCell::setId(int id) {
	this->id = id;
}

bool MazeCell::isVisited() {
	return this->visited;
}
void MazeCell::setVisited(bool visited) {
	this->visited = visited;
}

bool MazeCell::isChecked() {
	return checked;
}
void MazeCell::setChecked(bool checked) {
	this->checked = checked;
}