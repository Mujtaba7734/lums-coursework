//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Move.cpp
#include "../include/Move.hpp"

// Constructors
Move::Move() 
{
    name = "Tackle";
    power = 40;
    accuracy = 100;
    pp = 35;
    maxPP = 35;
}

Move::Move(const string& name, int power, int accuracy, int uses) 
{
    this->name = name;
    this->power = power;
    this->accuracy = accuracy;
    this->maxPP = uses;
    this->pp = uses;

}

Move::Move(const Move& other) 
{
    
    this->name = other.name;
    this->power = other.power;
    this->accuracy = other.accuracy;
    this->pp = other.pp;
    this->maxPP = other.maxPP;
}


// Getters (Initialize the getters before you start testing)
string Move::getName() const 
{ 
    return name;
}
int Move::getPower() const 
{ 
    return power;
}
int Move::getAccuracy() const 
{ 
    return accuracy;
}
int Move::getPP() const 
{ 
    return pp;
}
int Move::getMaxPP() const 
{ 
    return maxPP;
}

// Use move
bool Move::use()
{
    if (pp <= 0)
    {
        return false;
    }
    pp--;
    return true;
}

// Restore PP to max
void Move::restore()
{
    pp = maxPP;
}

// Check if out of PP
bool Move::isOutOfPP() const 
{
    if (pp == 0)
    {
        return true;
    }
    return false;
}