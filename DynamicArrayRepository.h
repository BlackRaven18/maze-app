#pragma once

#include "MazeCell.h"
#include "MazeCellTypes.h"

template <typename T>
class DynamicArrayRepository {

public:

	static T** createTwoDimDynamicTable(int rows, int columns);
	static void deleteTwoDimDynamicTable(T**, int rows);
	static T** recreateTwoDimDynamicTable(T** oldTable, int oldRows, int newRows, int newColumns);
};

template <typename T>
T** DynamicArrayRepository<T>::createTwoDimDynamicTable(int rows, int columns) {
	T** table = new T * [rows];
	for (int i = 0; i < rows; i++) {
		table[i] = new T[columns];
	}

	return table;
}


template <typename T>
void DynamicArrayRepository<T>::deleteTwoDimDynamicTable(T** tab, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] tab[i];
	}

	delete[] tab;
}

template <typename T>
T** DynamicArrayRepository<T>::recreateTwoDimDynamicTable(T** oldTable, int oldRows, int newRows, int newColumns) {
	deleteTwoDimDynamicTable(oldTable, oldRows);
	return createTwoDimDynamicTable(newRows, newColumns);
}


