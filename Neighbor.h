#pragma once

#include "SFML/Graphics.hpp"

class Neighbor {
private:
	sf::Vector2i position;

	std::vector<sf::Vector2i> neighbourPositions;

public:

	void setPosition(sf::Vector2i position);
	sf::Vector2i getPosition();

	void addNewNeighbourPosition(sf::Vector2i position);
	void removeNeighbour(int position);

	std::vector<sf::Vector2i> getNeighboursPositions();


};