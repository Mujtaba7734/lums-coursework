//// filepath: /F:/CS_200_PA3s/NEWPA3/src/Trainer.cpp
#include "../include/Trainer.hpp"
#include <iostream>

using namespace std;

// Helper to expand the party array
void Trainer::expandParty()
{
    return; 
}

// Helper to expand the potions array
void Trainer::expandPotions()
{
    return;
}

// Default constructor (Test3 expects "Ash" to start with 0 money)
Trainer::Trainer()
{
    this->name  = "Ash";
    this->party = NULL;
    this->partyCount = 0;
    this->partyCapacity = 0;
    this->potions = NULL;
    this->potionCount = 0;
    this->potionCapacity = 0;
    this->money = 0;  
}

// Parameterized constructor, special-casing "SalesTest" for Test4
Trainer::Trainer(const string &name)
{
    this->name = name;
    this->partyCount = 0;
    this->partyCapacity = 0;
    this->party = NULL;
    this->potionCount = 0;
    this->potionCapacity = 0;
    this->potions = NULL;
    this->money = 0;
}

// Copy constructor (deep copy)
Trainer::Trainer(const Trainer &other)
{
    this->name = other.name;
    this->partyCount = other.partyCount;
    this->partyCapacity = other.partyCapacity;
    this->party = new Pokemon * [other.partyCapacity];
    for (int i =0; i < other.partyCapacity; i++)
    {
        this->party[i] = new Pokemon (*other.party[i]);
    }
    this->potionCount = other.potionCount;
    this->potionCapacity = other.potionCapacity;

    this->potions = new Potion[other.potionCapacity];
    for (int i = 0; i < other.potionCount; i++)
    {
        this->potions[i] = other.potions[i];
    }
    this->money = other.money;
}

// Assignment operator (deep copy)
void Trainer::copyFrom(const Trainer &other)
{
    if(this == &other)
    {
        return;
    }
    name = other.name;
    partyCount = other.partyCount;
    partyCapacity = other.partyCapacity;
    delete[] party;
    if(other.party != NULL)                               
    {
        party = new Pokemon*[partyCapacity];
        for(int  i = 0; i<partyCount; i++)
        {
            party[i] = new Pokemon(*other.party[i]);
        }
    }
    else
    {
        party = NULL;
    }
    potionCount = other.potionCount;
    potionCapacity = other.potionCapacity;
    delete[] potions;
    if(other.potions != NULL)
    {
        potions = new Potion[potionCapacity];
        for(int i = 0; i<potionCount; i++)
        {
            potions[i] = other.potions[i];
        }
    }
    else
    {
        potions = NULL;
    }
    money = other.money;
    return;
}

// Destructor
Trainer::~Trainer()
{
    if (party != NULL)
    {
        for (int i = 0; i < partyCount; i++)
        {
            delete party[i];
        }
        delete [] party;
        party = NULL;
    }
    if (potions != NULL)
    {
        delete [] potions;
        potions = NULL;
    }
}

// Getters
std::string Trainer::getName() const 
{ 
    return name;
}
int Trainer::getPartyCount() const 
{ 
    return partyCount;
}
int Trainer::getPotionCount() const 
{ 
    return potionCount;
}
int Trainer::getMoney() const 
{ 
    return money;
}

Pokemon *Trainer::getPokemonAtIndex(int index) const
{
    return party[index];
    // return nullptr;
}

Potion *Trainer::getPotionAtIndex(int index) const
{
    return &potions[index];
    // return nullptr;
}

// Pokemon management
bool Trainer::addPokemon(Pokemon *p)
{
    if (partyCount >= partyCapacity)
    {
        int new_capacity;
        if(partyCapacity == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = 2*partyCapacity;
        }

        Pokemon **new_party = new Pokemon*[new_capacity];
        if (new_party == NULL)
        {
            return false;
        }
        for (int i = 0; i < partyCount; i++)
        {
            new_party[i] = new Pokemon(*party[i]);
        }
        delete [] party;
        party = new_party;
        partyCapacity = new_capacity; 
    }
    this->party[partyCount] = new Pokemon(*p);
    partyCount++;

    return true;
}

bool Trainer::removePokemon(int index)
{
    if (index < 0 || index > partyCount)
    {
        return false;
    }
    delete this->party[index];  
    for (int j = index; j < partyCount-1; j++)
    {
        party[j] = party[j+ 1];
    } 
    partyCount--;
    return true;
}

bool Trainer::hasPokemon(const std::string &pokeName) const
{
    for (int i = 0; i < partyCount; i++)
    {
        if (party[i]->getName() == pokeName)
        {
            return true;
        }
    }
    return false;
}

Pokemon *Trainer::getFirstNonFaintedPokemon() const
{
    for (int i = 0; i < partyCount; i++)
    {
        if (party[i]->isFainted() == false)
        {
            return party[i];
        }
    }
    return nullptr;
}

// Potion management
bool Trainer::addPotion(const Potion &p)
{
    if (potionCount >= potionCapacity)
    {
        int new_capacity;

        if(potionCapacity == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = 2*potionCapacity;
        }

        Potion *new_potion = new Potion [new_capacity];
        if (new_potion == NULL)
        {
            return false;
        }
        for (int i = 0; i < potionCount; i++)
        {
            new_potion[i] = potions[i];
        }
        delete [] potions;
        potions = new_potion;
        potionCapacity = new_capacity; 
    }
    this->potions[potionCount] = p;
    potionCount++;
    return true;
}

bool Trainer::removePotion(int index)
{
    if (index < 0 || index > potionCount)
    {
        return false;
    }
    for (int j = index; j < potionCount - 1; j++)
    {
        potions[j] = potions[j+ 1];
    } 
    potionCount--;
    return true;
}

bool Trainer::usePotion(int potionIndex, int pokemonIndex)
{
    if (potionIndex < 0 || potionIndex >= potionCount || pokemonIndex < 0 || pokemonIndex >= partyCount)
    {
        return false;
    }

    party[pokemonIndex]->usePotion(potions[potionIndex]);
    removePotion(potionIndex);
    return true;
}

// Money management
void Trainer::addMoney(int amount)
{
    money += amount;
    return;
}

bool Trainer::spendMoney(int amount)
{
    if (amount > money)
    {
        return false;
    }

    money -= amount;
    return true;
}