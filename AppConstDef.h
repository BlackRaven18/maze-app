#pragma once

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "Maze!"

#define SMALL_MAZE_ROWS 15
#define SMALL_MAZE_COLUMNS 24
#define SMALL_MAZE_CELL_SIZE 40
#define SMALL_MAZE_FILENAME "maze_examples/small_maze.txt"

#define MEDIUM_MAZE_ROWS 20
#define MEDIUM_MAZE_COLUMNS 32
#define MEDIUM_MAZE_CELL_SIZE 30
#define MEDIUM_MAZE_FILENAME "maze_examples/medium_maze.txt"


#define BIG_MAZE_ROWS 30
#define BIG_MAZE_COLUMNS 48
#define BIG_MAZE_CELL_SIZE 20
#define BIG_MAZE_FILENAME "maze_examples/big_maze.txt"


#define MAZE_AREA_X 0
#define MAZE_AREA_Y 0
#define MAZE_AREA_WIDTH SMALL_MAZE_COLUMNS * SMALL_MAZE_CELL_SIZE
#define MAZE_AREA_HEIGHT SMALL_MAZE_ROWS * SMALL_MAZE_CELL_SIZE

#define END_POINT_COLOR sf::Color{255, 0, 0}
#define START_POINT_COLOR sf::Color{0, 255, 0}

#define BACKGROUND_COLOR sf::Color{51, 51, 255}
#define MAZE_BACKGROUND_COLOR sf::Color{102, 0, 102}
#define MAZE_WALL_COLOR sf::Color{255, 255, 255}

/////////////////////////RESTART_BTN
#define MAZE_TRACK_COLOR sf::Color{0, 0, 255}
#define MAZE_VISITED_CELL_COLOR sf::Color::Cyan

#define PATHFINDER_CHECKED_CELLS_DELAY sf::seconds(0.01f)
#define PATHFINDER_DRAWING_PATH_DELAY sf::seconds(0.1f)
//////////////////////////

#define BUTTONS_NUM 11


enum MODE { PUT_WALL, PUT_END_POINT, PUT_START_POINT };
enum DIRECTION { LEFT = 5, RIGHT, UP, DOWN };
enum MAZE {SMALL = 9, MEDIUM, BIG};
enum ButtonName {
    START_BTN, RESTART_BTN, BOXWHITE_BTN, BOXGREEN_BTN, BOXRED_BTN, SAVE_BTN, BFS_BTN, DFS_BTN, ONEX_BTN, TWOX_BTN, FOURX_BTN
};