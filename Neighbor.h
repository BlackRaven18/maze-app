#pragma once

#include "SFML/Graphics.hpp"

class Neighbor {
private:
	sf::Vector2i position;

	sf::Vector2i upNeighbourPos;
	sf::Vector2i downNeighbourPos;
	sf::Vector2i leftNeighbourPos;
	sf::Vector2i rightNeighbourPos;

public:

	void setPosition(sf::Vector2i position);
	sf::Vector2i getPosition();

	void setUpNeighborPos(sf::Vector2i neighbourPosition);
	void setDownNeighborPos(sf::Vector2i neighbourPosition);
	void setLeftNeighborPos(sf::Vector2i neighbourPosition);
	void setRightNeighborPos(sf::Vector2i neighbourPosition);

	sf::Vector2i getUpNeighborPos();
	sf::Vector2i getDownNeighborPos();
	sf::Vector2i getLeftNeighborPos();
	sf::Vector2i getRightNeighborPos();
};