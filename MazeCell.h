#pragma once

#include "Rectangle.h"

class MazeCell: public virtual Rectangle {
private:
	int id;

public:
	MazeCell();
	MazeCell(int x, int y, int width, int height, sf::Color color, int id);

	int getId();
	void setId(int id);


};
