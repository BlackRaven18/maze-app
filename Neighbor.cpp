#include "Neighbor.h"

void Neighbor::setPosition(sf::Vector2i position)
{
	this->position = position;
}

sf::Vector2i Neighbor::getPosition()
{
	return this->position;
}

void Neighbor::addNewNeighbourPosition(sf::Vector2i position)
{
	this->neighbourPositions.push_back(position);
}

void Neighbor::removeNeighbour(int position)
{
	if (neighbourPositions.empty()) return;
	this->neighbourPositions.erase(neighbourPositions.begin() + position);
}

std::vector<sf::Vector2i> Neighbor::getNeighboursPositions()
{

	return this->neighbourPositions;
}

