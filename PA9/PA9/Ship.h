#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

//generic class ship that encompases behavior for all ships
class Ship
{
public:

	Ship(string cell, char letter = 'A', char direction = 'N', int length = '1');
	virtual ~Ship();

	virtual void printPlaced();

	// Getters
	string getCell() const;
	char getLetter() const;
	char getDirection() const;
	int getLength() const;

	// Setters
	void setCell(const string& newCell);
	void setLetter(const char newLetter);
	void setDirection(const char newDirection);
	void setLength(const int newLength);

protected:
	string cell;
	char letter;
	char direction;
	int length;

};

class Carrier : public Ship
{
public:
	Carrier(string cell, char direction);

	virtual void printPlaced() override;

private:
};

class Battleship : public Ship
{
public:
	Battleship(string cell, char direction);

	virtual void printPlaced() override;

private:
};

class Cruiser : public Ship
{
public:
	Cruiser(string cell, char direction);

	virtual void printPlaced() override;

private:
};

class Submarine : public Ship
{
public:
	Submarine(string cell, char direction);

	virtual void printPlaced() override;

private:
};

class Destroyer : public Ship
{
public:
	Destroyer(string cell, char direction);

	virtual void printPlaced() override;

private:
};