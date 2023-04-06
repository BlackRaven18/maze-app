#pragma once

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "Maze!"

#define MAZE_TABLE_ROWS 15
#define MAZE_TABLE_COLUMNS 24
#define MAZE_TABLE_CELL_SIZE 40

#define MEDIUM_MAZE_ROWS 20
#define MEDIUM_MAZE_COLUMNS 32
#define MEDIUM_MAZE_CELL_SIZE 30
#define MEDIUM_MAZE_FILENAME "medium_maze.txt"


#define MAZE_AREA_X 0
#define MAZE_AREA_Y 0
#define MAZE_AREA_WIDTH MAZE_TABLE_COLUMNS * MAZE_TABLE_CELL_SIZE
#define MAZE_AREA_HEIGHT MAZE_TABLE_ROWS * MAZE_TABLE_CELL_SIZE

#define END_POINT_COLOR sf::Color{255, 0, 0}
#define START_POINT_COLOR sf::Color{0, 255, 0}

#define BACKGROUND_COLOR sf::Color{51, 51, 255}
#define MAZE_BACKGROUND_COLOR sf::Color{102, 0, 102}
#define MAZE_WALL_COLOR sf::Color{255, 255, 255}

/////////////////////////
#define MAZE_TRACK_COLOR sf::Color{0, 0, 255}
#define MAZE_VISITED_CELL_COLOR sf::Color::Cyan

#define PATHFINDER_CHECKED_CELLS_DELAY sf::seconds(0.01)
#define PATHFINDER_DRAWING_PATH_DELAY sf::seconds(0.2)
//////////////////////////

#define BUTTONS_NUM 11

#define MAZE_FILENAME "labirynt.txt"

enum MODE { PUT_WALL, PUT_END_POINT, PUT_START_POINT };
enum DIRECTION { LEFT = 5, RIGHT, UP, DOWN };
enum MAZE {SMALL = 9, MEDIUM, BIG};