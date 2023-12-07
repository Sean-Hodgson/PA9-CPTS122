#include "HisData.h"

//Construcotrs, copiers, destructor
HisData::HisData()
{
    moveNum = 0;
    user = "";
    col = 0;
    row = 0;
    hitOrMiss = 0;

}

HisData::~HisData()
{

}

HisData::HisData(const HisData& origData)
{
    // Copy members
    this->moveNum = origData.moveNum;
    this->user = origData.user;
    this->col = origData.col;
    this->row = origData.row;
    this->hitOrMiss = origData.hitOrMiss;
}

HisData& HisData::operator=(const HisData& origData) // standard, absences can use = becuase = is overloaded from that function and returns a reference
{
    // Copy members
    this->moveNum = origData.moveNum;
    this->user = origData.user;
    this->col = origData.col;
    this->row = origData.row;
    this->hitOrMiss = origData.hitOrMiss;


    return *this;
}


// getters
int HisData::getMoveNum() const
{
    return moveNum;
}
string HisData::getUser() const
{
    return user;
}
int HisData::getCol() const
{
    return col;
}
int HisData::getRow() const
{
    return row;
}
int HisData::getHitOrMiss() const
{
    return hitOrMiss;
}

//setters
void HisData::setMoveNum(const int num)
{
    this->moveNum = num;
}
void HisData::setUser(const string& NewUser)
{
    this->user = NewUser;
}
void HisData::setCol(const int newCol)
{
    this->col = newCol;
}
void HisData::setRow(const int newRow)
{
    this->row = newRow;
}
void HisData::setHitOrMiss(const int num)
{
    this->hitOrMiss = num;
}

std::ostream& operator<<(std::ostream& os, const HisData& data)
{
    os << "Move Number: " << data.getMoveNum() << endl;
    os << "User: " << data.getUser() << endl;
    os << "Column: " << data.getCol() << endl;
    os << "Row: " << data.getRow() << endl;
    os << "Hit or Miss: " << data.getHitOrMiss() << endl;
    return os;
}