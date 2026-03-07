//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Armor.cpp
#include "../include/Armor.hpp"

// Constructors
Armor::Armor() 
{
    name = "Cloth"; // Default name
    defenseBonus = 0;
    weight = 0.0;
}

Armor::Armor(const string &name, int defenseBonus, double weight) 
{
    this->name = name;
    this->weight = weight;
    this->defenseBonus = defenseBonus;
}

// Copy constructor
Armor::Armor(const Armor &other) 
{
    this->name = other.name;
    this->weight = other.weight;
    this->defenseBonus = other.defenseBonus;
}

// Deep copies the contents of another Armor 
void Armor::copyFrom(const Armor &other)
{
    if (this != NULL)
    {
        delete [] this;
    }
    this->name = other.name;
    this->weight = other.weight;
    this->defenseBonus = other.defenseBonus;
}

// Getters
string Armor::getName() const 
{ 
    return name;
}
int Armor::getDefenseBonus() const 
{ 
    return defenseBonus;
}
double Armor::getWeight() const 
{ 
    return weight;
}

// Check if armor is heavy
bool Armor::isHeavy() const
{
    if (weight > 10.0)
    {
        return true;
    }
    return false;
}