#include "Ship.h"

Ship::Ship(string cell, char letter, char direction, int length)
	: cell(cell), letter(letter), direction(direction), length(length) {}

Ship::~Ship() {

}

void Ship::printPlaced() {

	cout << "Ship Placed!" << endl;
}


Carrier::Carrier(string cell, char direction) : Ship(cell, 'c', direction, 5) {}

void Carrier::printPlaced() {

	cout << "Carrier Placed!";
}



Battleship::Battleship(string cell, char direction) : Ship(cell, 'b', direction, 4) {}

void Battleship::printPlaced() {

	cout << "Battleship Placed!";
}



Cruiser::Cruiser(string cell, char direction) : Ship(cell, 'r', direction, 3) {}

void Cruiser::printPlaced() {

	cout << "Cruiser Placed!";
}



Submarine::Submarine(string cell, char direction) : Ship(cell, 's', direction, 3) {}

void Submarine::printPlaced() {

	cout << "Submarine Placed!";
}



Destroyer::Destroyer(string cell, char direction) : Ship(cell, 'd', direction, 2) {}

void Destroyer::printPlaced() {

	cout << "Destroyer Placed!";
}

// Getters
string Ship::getCell() const {
	return cell;
}

char Ship::getLetter() const {
	return letter;
}

char Ship::getDirection() const {
	return direction;
}

int Ship::getLength() const {
	return length;
}

// Setters
void Ship::setCell(const string& newCell) {
	cell = newCell;
}

void Ship::setLetter(const char newLetter) {
	letter = newLetter;
}

void Ship::setDirection(const char newDirection) {
	direction = newDirection;
}

void Ship::setLength(const int newLength) {
	length = newLength;
}