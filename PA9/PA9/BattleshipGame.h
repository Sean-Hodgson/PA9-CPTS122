#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include<time.h>
#include<cstdlib>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

#include "Board.h"
#include "List.h"
#include "HisData.h"
#include "Ship.h"

class BattleshipGame
{
public:
	BattleshipGame();
	~BattleshipGame();
	int generate_current_player();
	void print_boards();
	void display_rules();
	int alternate_players();
	int shoot(Board &opponentBoard, Board &playerBoard, int *hitOrMiss);
	int all_ship_sunk(int ship_hit_count[]);
	int get_targeted_ship(char ship_initial);

	void runApp();

private:
	Board player1Board;
	Board player2Board;
	int current_player;
	int target[2];
	List<HisData> history;
	std::ofstream gamelog;
};