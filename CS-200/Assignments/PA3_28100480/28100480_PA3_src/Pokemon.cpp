//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Pokemon.cpp
#include "../include/Pokemon.hpp"
#include <algorithm> // For std::max

// Private expand function
void Pokemon::expandMoves(){

}

// Constructors
Pokemon::Pokemon()
{
    name = "Pikachu";
    type = "Electric";
    maxHP = 100;
    currentHP = 100;
    moves = NULL;
    moveCount = 0;
    moveCapacity = 0;
    equippedArmor = nullptr;
    fainted = false;
    // Set defaults
}

Pokemon::Pokemon(const string& name, const string& type, int hp)
{
    this->name = name;
    this->type = type;
    this->maxHP = hp;
    this->currentHP = hp;
    this->moveCount = 0;
    this->moveCapacity = 5;
    this->moves = new Move [moveCapacity];
    this->equippedArmor = new Armor;
    fainted = false;
    // Initialize values
}

// Copy constructor
Pokemon::Pokemon(const Pokemon& other)
{
    this->name = other.name;
    this->type = other.type;
    this->maxHP = other.maxHP;
    this->currentHP = other.currentHP;
    this->moveCount = other.moveCount;
    this->moveCapacity = other.moveCapacity;
    this->moves = new Move [other.moveCapacity];
    for (int i = 0; i < other.moveCount; i++)
    {
        this->moves[i] = other.moves[i];
    }
    this->equippedArmor = new Armor (*other.equippedArmor);
    this->fainted = other.fainted;
    // Copy basic data
}

// Assignment operator
void Pokemon::copyFrom(const Pokemon &other)
{
    if(this == &other)
    {
        return;
    }
    name = other.name;
    type = other.type;
    maxHP = other.maxHP;
    currentHP = other.currentHP;
    moveCount = other.moveCount;
    moveCapacity = other.moveCapacity;
    delete[] moves;
    if(other.moves == NULL)                          
    {
        moves = NULL;
    }
    else
    {
        moves = new Move[moveCapacity];
        for(int i = 0; i<moveCount; i++)
        {
            moves[i] = other.moves[i];
        }
    }
    delete equippedArmor;
    if(other.equippedArmor == NULL)
    {
        equippedArmor = NULL;
    }
    else
    {
        equippedArmor = new Armor;
        *equippedArmor = *other.equippedArmor;
    }
    fainted = other.fainted;

}

// Destructor
Pokemon::~Pokemon()
{
    if (moves != NULL)
    {
        delete [] moves;
        moves = NULL;
    }
    if (equippedArmor != NULL)
    {
        delete equippedArmor;
        equippedArmor = NULL;
    }
}

// Getters
string Pokemon::getName() const 
{ 
    return name;
}
string Pokemon::getType() const 
{ 
    return type;
}
int Pokemon::getMaxHP() const 
{ 
    return maxHP;
}
int Pokemon::getCurrentHP() const 
{ 
    return currentHP;
}
int Pokemon::getMoveCount() const
{ 
    return moveCount;
}
bool Pokemon::isFainted() const 
{ 
    return fainted;
}
Armor* Pokemon::getEquippedArmor() const 
{ 
    return equippedArmor;
}

Move* Pokemon::getMoveAtIndex(int index)
{
    return &moves[index];
}
// Move management
bool Pokemon::addMove(const Move& m)
{
    if (moveCount >= moveCapacity)
    {
        int new_capacity = moveCapacity * 2;
        Move *new_moves = new Move [new_capacity];
        if (new_moves == NULL)
        {
            return false;
        }
        for (int i = 0; i < moveCount; i++)
        {
            new_moves[i] =moves[i];
        }
        delete [] moves;
        moves = new_moves;
        moveCapacity = new_capacity; 
    }
    this->moves[moveCount] = m;
    moveCount++;
    return true;
}

bool Pokemon::removeMove(int index)
{
    if (index < 0 || index > moveCount)
    {
        return false;
    }
    for (int j = index; j < moveCount-1; j++)
    {
        moves[j] = moves[j+ 1];
    } 
    moveCount--;
    return true;
}

bool Pokemon::hasMove(const string& moveName) const 
{
    for (int i = 0; i < moveCount; i++)
    {
       if (moves[i].getName() == moveName)
       {
            return true;
       } 
    }
    return false;
}

// Battle functionality
void Pokemon::takeDamage(int amount)
{
    amount -= equippedArmor->getDefenseBonus();

    if (amount < 0)
    {
        amount = 0;
    }
    currentHP -= amount;
    
    if (currentHP <= 0)
    {
        currentHP = 0;
        fainted = true;
    }
    return;
}

void Pokemon::heal(int amount)
{
    currentHP+= amount;
    if (currentHP >= maxHP)
    {
        currentHP = maxHP;
    }
    if (currentHP > 0)
    {
        fainted = false;
    }
    else
    {
        fainted = true;
    }
    
    return;
}

void Pokemon::equipArmor(const Armor& a)
{
    if (equippedArmor != NULL)
    {
        delete equippedArmor;
    }
    equippedArmor = new Armor(a);
    return;
}

void Pokemon::removeArmor()
{
    delete equippedArmor;
    return;
}

bool Pokemon::useMove(int moveIndex)
{
    if ((moves[moveIndex].isOutOfPP() == true) || fainted == true)
    {
        return false;
    }
    moves[moveIndex].use();
}

bool Pokemon::usePotion(Potion& p)
{
    if (!p.canUse())
    {
        return false;
    }
    p.use(); // Mark potion as used
    currentHP += p.getHealAmount();
    if (currentHP > maxHP)
    {
        currentHP = maxHP;
    }
    return true;
}

void Pokemon::resetHP()
{
    currentHP = maxHP;
    fainted = false;
    return;
}