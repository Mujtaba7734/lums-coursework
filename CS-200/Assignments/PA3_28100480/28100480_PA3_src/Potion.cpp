//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Potion.cpp
#include "../include/Potion.hpp"

// Constructors
Potion::Potion()
{
    name = "Basic Potion";
    healAmount = 20;
    cost = 10;
    isUsed = false;
}

Potion::Potion(const string& name, int healAmount, int cost) 
{
    this->name = name;
    this->healAmount = healAmount;
    this->cost = cost;
    this->isUsed = false;
}

// Copy constructor
Potion::Potion(const Potion& other) 
{
    name = other.name;
    healAmount = other.healAmount;
    cost = other.cost;
    isUsed = other.isUsed;
}



// Getters
string Potion::getName() const 
{ 
    return name;
}
int Potion::getHealAmount() const 
{ 
    return healAmount;
}
int Potion::getCost() const 
{
    return cost;
}
bool Potion::getIsUsed() const 
{ 
    return isUsed;
}

// Mark potion as used
void Potion::use() 
{
    isUsed = true;
}

// Check if potion can be used
bool Potion::canUse() const 
{
    if (isUsed == false)
    {
        return true;
    }
    return false;
}
