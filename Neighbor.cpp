#include "Neighbor.h"

void Neighbor::setPosition(sf::Vector2i position)
{
	this->position = position;
}

sf::Vector2i Neighbor::getPosition()
{
	return this->position;
}

void Neighbor::setUpNeighborPos(sf::Vector2i neighbourPosition)
{
	this->upNeighbourPos = neighbourPosition;

}

void Neighbor::setDownNeighborPos(sf::Vector2i neighbourPosition)
{
	this->downNeighbourPos = neighbourPosition;

}

void Neighbor::setLeftNeighborPos(sf::Vector2i neighbourPosition)
{
	this->leftNeighbourPos = neighbourPosition;

}

void Neighbor::setRightNeighborPos(sf::Vector2i neighbourPosition)
{
	this->rightNeighbourPos = neighbourPosition;

}

sf::Vector2i Neighbor::getUpNeighborPos()
{
	return this->upNeighbourPos;
}

sf::Vector2i Neighbor::getDownNeighborPos()
{
	return this->downNeighbourPos;
}

sf::Vector2i Neighbor::getLeftNeighborPos()
{
	return this->leftNeighbourPos;
}

sf::Vector2i Neighbor::getRightNeighborPos()
{
	return this->rightNeighbourPos;
}
