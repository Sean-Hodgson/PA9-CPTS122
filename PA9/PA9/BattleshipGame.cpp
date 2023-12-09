#include "BattleshipGame.h"

BattleshipGame::BattleshipGame()
{
	gamelog.open("gamelog.txt", std::ofstream::out | std::ofstream::trunc); // open the gamelog for writing and overwrite if already stats
	current_player = 1;
	target[0] = 0;
	target[1] = 0;
}

BattleshipGame::~BattleshipGame()
{
	gamelog.close();

}

void BattleshipGame::runApp()
{
	int main_option = 0;
	while (main_option != 3) {

		while (main_option < 1 || main_option > 3) {
			system("cls");
			cout << "1.Print Game Rules" << endl;
			cout << "2.Start the game of Battleship" <<endl;
			cout << "3.Exit" << endl;
			cin >> main_option;
		};

		system("pause");
		system("cls");
		if (main_option == 1) {
			display_rules();
			system("pause");
			main_option = 0;
		}
		else if (main_option == 3) {
			cout << "Exiting game, goodbye!" << endl;
			main_option = 3;
		}
		else if (main_option == 2) {
			sf::RenderWindow window(sf::VideoMode(2020, 1080), "Battleship", sf::Style::Close | sf::Style::Titlebar);
			sf::Texture waterTex, shipTex, hitTex, missTex;
			waterTex.loadFromFile("water.png");
			shipTex.loadFromFile("ship.png");
			hitTex.loadFromFile("hitmarker.png");

			sf::Image icon;
			icon.loadFromFile("icon.png");
			window.setIcon(200, 200, icon.getPixelsPtr());
			missTex.loadFromFile("miss.png");

			sf::Font font;
			if (!font.loadFromFile("arial.ttf"))
				std::cout << "Font not found!\n";

			int game_over = 0;
			current_player = generate_current_player();
			cout << "Player " << current_player << " has been randomly selected to go first.\n" << endl;
			
			player1Board.generateBoard();
			player2Board.generateBoard();

			while (game_over == 0) {
				sf::Sprite BoardGraphics[10][10];

				int x = 35;
				for (int c = 0; c < 10; c++) {
					sf::Text counter;
					counter.setFont(font);
					counter.setCharacterSize(12);
					counter.setFillColor(sf::Color::White);
					counter.setString(to_string(c));
					int y = 35;
					for (int b = 0; b < 10; b++) {

						sf::Text counterd;
						counterd.setFont(font);
						counterd.setCharacterSize(12);
						counterd.setFillColor(sf::Color::White);
						counterd.setString(to_string(b));


						counter.setPosition(x+25, y);


						counterd.setPosition(15, y + 40);

						window.draw(counterd);

						if (y == 35) {
							window.draw(counter);
						}
						
						if (player1Board.getBoardElement(b, c) == '-') {
							BoardGraphics[b][c].setTexture(waterTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						else if (player1Board.getBoardElement(b, c) == '*') {
							BoardGraphics[b][c].setTexture(hitTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						else if (player1Board.getBoardElement(b, c) == 'm') {
							BoardGraphics[b][c].setTexture(missTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						else {
							BoardGraphics[b][c].setTexture(shipTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						y = y + 70;
						window.draw(BoardGraphics[b][c]);
					}
					// window.draw(Board[i][j]);

					cout << endl;
					x += 75;
				}
				x += 475;

				bool rowDone = false;
				
				for (int c = 0; c < 10; c++) {
					sf::Text counter;
						counter.setFont(font);
						counter.setCharacterSize(12);
						counter.setFillColor(sf::Color::White);
						counter.setString(to_string(c));
				


					int y = 10;
					for (int b = 0; b < 10; b++) {

						sf::Text counterd;
						counterd.setFont(font);
						counterd.setCharacterSize(12);
						counterd.setFillColor(sf::Color::White);
						counterd.setString(to_string(b));

			
						counter.setPosition(x + 25, y);
						
						
						counterd.setPosition(1200, y+40);

						window.draw(counterd);

						if (y == 10) {
							window.draw(counter);
						}

						if (player2Board.getBoardElement(b, c) == 'c'|| player2Board.getBoardElement(b, c) == 'b' || player2Board.getBoardElement(b, c) == 'r' || player2Board.getBoardElement(b, c) == 's' || player2Board.getBoardElement(b, c) == 'd' || player2Board.getBoardElement(b, c) == '-') {
							BoardGraphics[b][c].setTexture(waterTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						else if (player2Board.getBoardElement(b, c) == '*') {
							BoardGraphics[b][c].setTexture(hitTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						else if (player2Board.getBoardElement(b, c) == 'm') {
							BoardGraphics[b][c].setTexture(missTex);
							BoardGraphics[b][c].setPosition(x, y);
							BoardGraphics[b][c].setScale(sf::Vector2f(0.15f, 0.15f));
						}
						y = y + 70;
						window.draw(BoardGraphics[b][c]);
					}
					// window.draw(Board[i][j]);

					x += 75;
				}

			window.display();
			// print_boards();
			system("pause");
			system("cls");

			int moveCounter = 1;
			int hitOrMiss;
			//shoot!
			if (current_player == 1) {
				cout << "Enter a target row number: ";
				cin >> target[0];
				cout << "\nEnter a target column number: ";
				cin >> target[1];
				system("cls");

				int is_new_target = 0;
				is_new_target = shoot(player2Board,player1Board,&hitOrMiss);

				while (is_new_target == 0) {
					cout << "!  Please enter unselected new target  !" << endl;
					cout << "Enter a target row number: ";
					cin >> target[0];
					cout << "\nEnter a target column number: ";
					cin >> target[1];
					system("cls");
					is_new_target = shoot(player2Board, player1Board,&hitOrMiss);
				};

				//create a new instance of HisData class to end to the end of the linked list
				HisData* move = new HisData();
				move->setUser("Player 1");
				move->setMoveNum(moveCounter);
				move->setRow(target[0]);
				move->setCol(target[1]);
				move->setHitOrMiss(hitOrMiss);
				history.insertAtEnd(*move); //add it to the linked list

				//player1.total_num_shots += 1;
				player1Board.enemy_ship_sunk();
				system("pause");


				if (all_ship_sunk(player1Board.getShipHitCount()) == 1) {
					cout << "Player 1 won!" << endl;
					/*strcpy(player1.won_lost, "Won");
					strcpy(player2.won_lost, "Lost");*/
					game_over = 1;
				}
				moveCounter++;
			}
			else if (current_player == 2) {
				target[0] = player2Board.generate_rand_cell();
				target[1] = player2Board.generate_rand_cell();
				int is_new_target = 0;
				is_new_target = shoot(player1Board,player2Board,&hitOrMiss);

				while (is_new_target == 0) {
					target[0] = player2Board.generate_rand_cell();
					target[1] = player2Board.generate_rand_cell();
					is_new_target = shoot(player1Board, player2Board,&hitOrMiss);
				};
				//player2.total_num_shots += 1;
				player2Board.player_ship_sunk();
				system("pause");
				system("cls");

				//create a new instance of HisData class to end to the end of the linked list
				HisData* move = new HisData();
				move->setUser("Player 2");
				move->setMoveNum(moveCounter);
				move->setRow(target[0]);
				move->setCol(target[1]);
				move->setHitOrMiss(hitOrMiss);
				history.insertAtEnd(*move); //add it to the linked list

				if (all_ship_sunk(player2Board.getShipHitCount()) == 1) {
					cout << "Computer won!" << endl;
					/*strcpy(player2.won_lost, "Won");
					strcpy(player1.won_lost, "Lost");*/
					game_over = 1;
				}
				moveCounter++;

		
			};
			//===end of shoot section==




			if (game_over == 1) {
				window.close();
				cout << "The game is over!" << endl;

				history.printList(gamelog); //print all the moves from the game onto the gamelog

				/*player1.hit_to_miss_ratio = (player1.total_num_hits / player1.total_num_mises) * 100;
				player2.hit_to_miss_ratio = (player2.total_num_hits / player2.total_num_mises) * 100;

				write_stats(&player1, &player2, file);
				printf("Statistics outputted to logfile succesfully!\n");*/
				cout << "Let's play again!" << endl;
				system("pause");
			}

			current_player = alternate_players();
			}
			
		}
	}
}

int BattleshipGame::shoot(Board &opponentBoard,Board &playerBoard, int *hitOrMiss) {
	//shoot on targeted section
	int row = target[0];
	int column = target[1];
	if (row > 9 || row < 0 || column > 9 || column < 0) return 0;

	//fprintf(file, "Player %d selects: %d,%d\n", curnt_plr, target[0], target[1]);

	if (opponentBoard.getBoardElement(row,column) == '*' || opponentBoard.getBoardElement(row,column) == 'm') {
		return 0;
	}
	else if (opponentBoard.getBoardElement(row,column) == '-') {
		*hitOrMiss = 0;
		opponentBoard.setBoard(row,column,'m');
		//player->total_num_mises = player->total_num_mises + 1;

		if (current_player == 2) cout << "Player selects: " << row << "," << column << endl;
		cout << row << "," << column << " is a miss\n" << endl;
		//fprintf(file, "It was a miss.\n");

	}
	else {
		*hitOrMiss = 1;
		char targeted_ship = opponentBoard.getBoardElement(row,column);
		opponentBoard.setBoard(row,column,'*');
		//player->total_num_hits = player->total_num_hits + 1;
		int hit_ship = get_targeted_ship(targeted_ship);
		playerBoard.setShipHitCount(hit_ship);

		if (current_player == 2) cout << "Player selects: " << row << "," << column << endl;
		cout << row << "," << column << " is a hit!\n" << endl;
		//fprintf(file, "It was a hit!\n");
	}

	return 1;
}

int BattleshipGame::alternate_players() {
	//change players
	if (current_player == 1) {
		return 2;
	}
	else if (current_player == 2) {
		return 1;
	}
}

int BattleshipGame::get_targeted_ship(char ship_initial) {
	//get the index of targeted ship
	int index = 0;
	if (ship_initial == 'c') {
		index = 0;
	}
	else if (ship_initial == 'b') {
		index = 1;
	}
	else if (ship_initial == 'r') {
		index = 2;
	}
	else if (ship_initial == 's') {
		index = 3;
	}
	else if (ship_initial == 'd') {
		index = 4;
	}

	return index;
}

void BattleshipGame::display_rules() {
	cout << "                    *******Welcome to Battleship captain!*******\n" << endl;
	cout << "Rules of the game:" << endl;
	cout << "1. This is a two player game." << endl;
	cout << "2. Player 1 is you and player 2 is the computer." << endl;
	cout << "3. It's a battle of fleets on the sea!." << endl;
	cout << "4. Each player has 5 ships: Carrier(5 cells long), Destroyer(2 cells long),Battleship(4 cells long),\nCruiser(3 cells long) & Submarine(3 cells long)." << endl;
	cout << "5. The first player to sink enemy's all 5 ships wins the game." << endl;
	cout << "6. Random player will be picked to start the game." << endl;
	cout << "7. You will shoot your guns by entering the cell position of your target" << endl;
	cout << "                   **************LET'S BATTLE!*******************" << endl;
};

int BattleshipGame::generate_current_player() {
	//get the current player
	return rand() % 2 + 1;
}

void BattleshipGame::print_boards() {
	//print both boards
	cout << "Player 1's board" << endl;
	player1Board.print_board(0);
	cout << "\n";
	cout << "Player 2's board" << endl;
    player2Board.print_board(1);
}

int BattleshipGame::all_ship_sunk(int ship_hit_count[]) {
	//check if all ships sunk
	if (ship_hit_count[0] == 5 && ship_hit_count[1] == 4 && ship_hit_count[2] == 3 && ship_hit_count[3] == 3 && ship_hit_count[4] == 2) return 1;
	return 0;
}