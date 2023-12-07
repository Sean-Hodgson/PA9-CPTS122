#pragma once

#include <iostream>

#include "Node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//stores the history of moves taken by each player
class HisData
{
public:
    HisData();
    ~HisData();
    HisData(const HisData& origData);
    HisData& operator = (const HisData& origData);

    // getters
    int getMoveNum() const;
    string getUser() const;
    int getCol() const;
    int getRow() const;
    int getHitOrMiss() const;

    //setters
    void setMoveNum(const int num);
    void setUser(const string& NewUser);
    void setCol(const int newCol);
    void setRow(const int newRow);
    void setHitOrMiss(const int num);


private:
    int moveNum; // integer that +1 with each move taken
    string user; // stores the user that made the move
    int col; // cell that was attacked
    int row;
    int hitOrMiss; // 1 for hit, 0 for miss
};

std::ostream& operator<<(std::ostream& os, const HisData& data);