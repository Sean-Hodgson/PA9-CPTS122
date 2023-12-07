#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include "Ship.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

class Board {
public:
	Board();
	~Board();

	int horizontal_is_empty(char board[10][10], int row, int start, int end);
	int vertical_is_empty(char board[10][10], int column, int start, int end);
	void horizontal_placer(char board[10][10], int row, int start, int end, char ship_initial);
	void vertical_placer(char board[10][10], int column, int start, int end, char ship_initial);
	int generate_rand_cell();
	int generate_rand_horver();
	char generate_rand_dir(int hor_ver);
	void print_board(int mask);
	void generateBoard();
	int check_and_place(int ship_size, char ship_initial);
	void enemy_ship_sunk( /*FILE* file,*/ );
	void player_ship_sunk( /*FILE* file, */ );
	int* getShipHitCount(void);
	void setShipHitCount(int hit_ship);
	void setBoard(int row, int column, char value);
	char getBoardElement(int row, int column);
private:
	int starting_cell[2];
	int hor_ver;
	char dir;
	char board[10][10];
	int ship_hit_count[5];
	int ship_hit_count_displayed[5];
};