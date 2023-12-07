#include "Board.h"

Board::Board() {
	starting_cell[0] = 0;
	starting_cell[1] = 0;
	hor_ver = 1; //1 for horizontal and 2 for vertical
	dir = 'l';
	//initialize board with '-' values
	for (int i = 0; i < 10; i++) {
		for (int j = 0;j < 10;j++) {
			board[i][j] = '-';
		};
	}

	for (int i = 0; i < 5; i++) {
		ship_hit_count[i] = 0;
	    ship_hit_count_displayed[i] = 0;
	}
}

Board::~Board() {

}

void get_current_ship(string* current_ship, char* ship_initial, int* ship_size, int position) {
	//get the current selected ship
	if (position == 0) {
		*current_ship = "Carrier";
		*ship_initial = 'c';
		*ship_size = 5;
	}
	else if (position == 1) {
		*current_ship = "Battleship";
		*ship_initial = 'b';
		*ship_size = 4;
	}
	else if (position == 2) {
		*current_ship = "Cruiser";
		*ship_initial = 'r';
		*ship_size = 3;
	}
	else if (position == 3) {
		*current_ship = "Submarine";
		*ship_initial = 's';
		*ship_size = 3;
	}
	else if (position == 4) {
		*current_ship = "Destroyer";
		*ship_initial = 'd';
		*ship_size = 2;
	}
}

int* Board::getShipHitCount(void) {
	return ship_hit_count;
}

void Board::setShipHitCount(int hit_ship) {
	ship_hit_count[hit_ship] += 1;
}


void Board::setBoard(int row, int column,char value) {
	board[row][column] = value;
};

char Board::getBoardElement(int row, int column) {
	return board[row][column];
};


int Board::vertical_is_empty(char board[10][10], int column, int start, int end) {
	// check if vertical cells are empty
	for (int i = start; i <= end; i++) {
		if (board[i][column] != '-') return 0;
	}
	return 1;
}

void Board::horizontal_placer(char board[10][10], int row, int start, int end, char ship_initial) {
	// place ship horizontally
	for (int i = start; i <= end; i++) {
		board[row][i] = ship_initial;
	}
}

int Board::horizontal_is_empty(char board[10][10], int row, int start, int end) {
	// check if horizontal cells are empty
	for (int i = start; i <= end; i++) {
		if (board[row][i] != '-') return 0;
	}
	return 1;
}

void Board::vertical_placer(char board[10][10], int column, int start, int end, char ship_initial) {
	// place ship vertically

	for (int i = start; i <= end; i++) {
		board[i][column] = ship_initial;
	}
}

int Board::generate_rand_cell() {
	//generate random cell number
	return rand() % 10;
}

int Board::generate_rand_horver() {
	//generate random number for horizontal or vertical direction
	return rand() % 2 + 1;
}

char Board::generate_rand_dir(int hor_ver) {
	//generate random number for left,right,up or down direction

	char dir_hor_options[] = { 'l','r' };
	char dir_ver_options[] = { 'u','d' };
	int rand_index = rand() % 2;

	if (hor_ver == 1) {
		return dir_hor_options[rand_index];
	}
	else if (hor_ver == 2) {
		return dir_ver_options[rand_index];
	}
}

int Board::check_and_place(int ship_size, char ship_initial) {
	//checks if given ship is in range
	//dir can be l,r,u or d  
	//h_or_v can 1 for horizontal or 2 for vertical

	int ship_length = ship_size - 1;

	if (hor_ver == 1 && dir == 'l') {
		int last_cell = starting_cell[1] + ship_length;
		if (last_cell > 9) return 0;
		int is_empty = horizontal_is_empty(board, starting_cell[0], starting_cell[1], last_cell);
		if (is_empty == 0) return 0;

		horizontal_placer(board, starting_cell[0], starting_cell[1], last_cell, ship_initial);

	}
	else if (hor_ver == 1 && dir == 'r') {
		int last_cell = starting_cell[1] - ship_length;
		if (last_cell < 0) return 0;
		int is_empty = horizontal_is_empty(board, starting_cell[0], last_cell, starting_cell[1]);
		if (is_empty == 0) return 0;
		horizontal_placer(board, starting_cell[0], last_cell, starting_cell[1], ship_initial);
	}
	else if (hor_ver == 2 && dir == 'u') {
		int last_cell = starting_cell[0] - ship_length;
		if (last_cell < 0) return 0;
		int is_empty = vertical_is_empty(board, starting_cell[1], last_cell, starting_cell[0]);
		if (is_empty == 0) return 0;
		vertical_placer(board, starting_cell[1], last_cell, starting_cell[0], ship_initial);
	}
	else if (hor_ver == 2 && dir == 'd') {
		int last_cell = starting_cell[0] + ship_length;
		if (last_cell > 9) return 0;
		int is_empty = vertical_is_empty(board, starting_cell[1], starting_cell[0], last_cell);
		if (is_empty == 0) return 0;
		vertical_placer(board, starting_cell[1], starting_cell[0], last_cell, ship_initial);
	}

	return 1;
}

void Board::generateBoard() {
	for (int i = 0; i < 5; i++) {
		string current_ship = "Carrier";
		char ship_initial = 'c';
		int ship_size = 5;
		int valid_position = 0;

		while (valid_position == 0) {
			get_current_ship(&current_ship, &ship_initial, &ship_size, i);

			starting_cell[0] = generate_rand_cell();
			starting_cell[1] = generate_rand_cell();

			hor_ver = generate_rand_horver();

			dir = generate_rand_dir(hor_ver);

			valid_position = check_and_place(ship_size, ship_initial);
		}
	};

}

void Board::print_board(int mask) {
	//print board
	for (int x = 0; x < 11; x++) {
		if (x == 0) cout << "  ";
		else cout << x - 1 << " ";
	}

	cout << "\n";

	for (int i = 0; i < 10; i++) {
		cout << i << " ";
		for (int j = 0; j < 10; j++) {
			int ok_to_display = board[i][j] == '-' || board[i][j] == 'm' || board[i][j] == '*';

			if (mask == 1 && ok_to_display == 0) {
				if (j == 9) cout << "-" << endl;
				else cout << "-,";
			}
			else {
				if (j == 9) cout << board[i][j] << endl;
				else cout << board[i][j] << ",";
			}
		}
	}
}

void Board::enemy_ship_sunk(/*FILE* file,*/) {
	//check and display messages if any enemy ship is sunk
	if (ship_hit_count[0] == 5 && ship_hit_count_displayed[0] == 0) {
		ship_hit_count_displayed[0] = 1;
		cout << "Carrier successfully destroyed!\n" << endl;
		//fprintf(file, "Carrier sunk!\n");
	}
	else if (ship_hit_count[1] == 4 && ship_hit_count_displayed[1] == 0) {
		ship_hit_count_displayed[1] = 1;
		cout << "Enemy's Battleship is no more a battleship!\n" << endl;
		//fprintf(file, "Battleship sunk!\n");
	}
	else if (ship_hit_count[2] == 3 && ship_hit_count_displayed[2] == 0) {
		ship_hit_count_displayed[2] = 1;
		cout << "Enemy's cruiser ain't cruising anymore!\n" << endl;
		//fprintf(file, "Cruiser sunk!\n");
	}
	else if (ship_hit_count[3] == 3 && ship_hit_count_displayed[3] == 0) {
		ship_hit_count_displayed[3] = 1;
		cout << "Enemy's submarine is in submission, not in summersion!\n" << endl;
		//fprintf(file, "Submarine sunk!\n");
	}
	else if (ship_hit_count[4] == 2 && ship_hit_count_displayed[4] == 0) {
		ship_hit_count_displayed[4] = 1;
		cout << "Enemy's destroyer ain't living upto it's name no more!\n" << endl;
		//fprintf(file, "Destroyer sunk!\n");
	}
}

void Board::player_ship_sunk(/*FILE* file,*/) {
	//check and display messages if any of player's ship is sunk

	if (ship_hit_count[0] == 5 && ship_hit_count_displayed[0] == 0) {
		ship_hit_count_displayed[0] = 1;
		cout << "Oops your carrier is gone\n" << endl;
		//fprintf(file, "Carrier sunk!\n");
	}
	else if (ship_hit_count[1] == 4 && ship_hit_count_displayed[1] == 0) {
		ship_hit_count_displayed[1] = 1;
		cout << "Battleship just retired:(\n" << endl;
		//fprintf(file, "Battleship sunk!\n");

	}
	else if (ship_hit_count[2] == 3 && ship_hit_count_displayed[2] == 0) {
		ship_hit_count_displayed[2] = 1;
		cout << "Cruiser served its mission, died a hero!\n" << endl;
		//fprintf(file, "Cruiser sunk!\n");

	}
	else if (ship_hit_count[3] == 3 && ship_hit_count_displayed[3] == 0) {
		ship_hit_count_displayed[3] = 1;
		cout << "Submarine is gone:(\n" << endl;
		//fprintf(file, "Submarine sunk!\n");

	}
	else if (ship_hit_count[4] == 2 && ship_hit_count_displayed[4] == 0) {
		ship_hit_count_displayed[4] = 1;
		cout << "Destroyer did it's best,RIP!\n" << endl;
		//fprintf(file, "Destroyer sunk!\n");
	}
}