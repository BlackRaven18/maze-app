#pragma once

#include "Rectangle.h"

class MazeCell: public virtual Rectangle {
private:
	int id;
	bool visited;
	bool checked;

public:
	MazeCell();
	MazeCell(int x, int y, int width, int height, sf::Color color, int id);

	int getId();
	void setId(int id);

	bool isVisited();
	void setVisited(bool visited);

	bool isChecked();
	void setChecked(bool checked);


};
