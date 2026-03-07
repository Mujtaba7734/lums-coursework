//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Gym.cpp
#include "../include/Gym.hpp"
#include <iostream>
#include <sstream>

// Private expand function
void Gym::expandGym()
{
    // TODO: If you are using a dynamic array to store gym Pokémon,
    // expand the array by allocating a new array with larger capacity,
    // copy the existing pointers, then delete the old array.
    return;
}

// Constructor
Gym::Gym(Trainer *gymLeader, const string &badgeName, int difficulty)
{
    // TODO: Initialize member variables, e.g.,
    // - Set the gym leader pointer.
    // - Save the badge name and difficulty level.
    // - Initialize the storage for gym Pokémon
    this->gymLeader = gymLeader;
    this->pokemonCount = 0;
    this->capacity = 0;
    this->gymPokemon = new Pokemon * [capacity];
    this->badgeName = badgeName;
    this->difficulty = difficulty;
}

// Destructor
Gym::~Gym()
{
    if (gymPokemon != NULL)
    {
        delete [] gymPokemon;
        gymPokemon = NULL;
    }
    // TODO: Clean up any dynamically allocated memory if the Gym owns the Pokémon.
    // If the Gym does not own them, be careful not to double-delete.
}

// Getters
string Gym::getBadgeName() const 
{ 
    return badgeName;
}
int Gym::getDifficulty() const 
{ 
    return difficulty;
}
int Gym::getPokemonCount() const 
{ 
    return pokemonCount;
}
Trainer *Gym::getGymLeader() const 
{ 
    return gymLeader;
}
Pokemon *Gym::getGymPokemonAtIndex(int index) const
{
    return gymPokemon[index];
}
BattleHistory Gym::getGymHistory() const
{
    return gymHistory;
    // TODO: Return a copy of the gym's BattleHistory
}

// Gym management
void Gym::addGymPokemon(Pokemon *p)
{
    if (pokemonCount >= capacity)
    {
        int new_capacity;
        if(capacity == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = 2*capacity;
        }

        Pokemon **new_pokemon = new Pokemon*[new_capacity];
        if (new_pokemon == NULL)
        {
            return;
        }
        for (int i = 0; i < pokemonCount; i++)
        {
            new_pokemon[i] = gymPokemon[i]; 
        }
        delete [] gymPokemon;
        gymPokemon = new_pokemon;
        capacity = new_capacity; 
    }
    this->gymPokemon[pokemonCount] = p;
    pokemonCount++;

    return;
}

bool Gym::removeGymPokemon(int index)
{
    if (index < 0 || index > pokemonCount)
    {
        return false;
    }
    delete this->gymPokemon[index];  
    for (int j = index; j < pokemonCount-1; j++)
    {
        gymPokemon[j] = gymPokemon[j+ 1];
    } 
    pokemonCount--;
    return true;
}

// Battle functionality (There will be hidden test cases for this portion, to test multiple scenarios in both deterministic and non-deterministic methods)
bool Gym::battle(Trainer *challenger)
{
    // Simple simulation: challenger wins if every gym Pokemon is defeated in order to win.
    // For now, this return value is a placeholder.
    // A proper implementation would involve simulating a battle using the Battle class
    // If your test case passes for the correct implementation.
        // Simple simulation: challenger wins if every gym Pokemon is defeated in order to win.
    // For now, this return value is a placeholder.
    // A proper implementation would involve simulating a battle using the Battle class
    // If your test case passes for the correct implementation.

    
   

    int g =0;
    int c =0;

    while (g < pokemonCount && c < challenger->getPartyCount())
    {
        Pokemon* challengerPokemon = challenger->getPokemonAtIndex(c);
        if (challengerPokemon == nullptr) return false;

        cout << "---------------------" << endl;
        cout << "     Match Start     " << endl;
        cout << "---------------------" << endl;
        cout << "Challenger Pokemon: " << challengerPokemon->getName() << " with " << challengerPokemon->getCurrentHP() << "hp" << endl;
        cout << "Gym Pokemon: " << gymPokemon[g]->getName() << " with " << gymPokemon[g]->getCurrentHP() << "hp" << endl << endl;

        if (gymPokemon[g] == nullptr) 
        {
            g++;
            continue;
        }

        Battle battle(*challengerPokemon, *gymPokemon[g]);

        battle.simulateFullBattle();

        if (battle.getWinner() == challengerPokemon)
        {
            cout << gymPokemon[g]->getName() << " fainted. " << challengerPokemon->getName() << " wins!" << endl << endl;
        }
        g++;
    }
    return true;
}

void Gym::healAllPokemon()
{
    for (int i =0; i < pokemonCount; i++)
    {
        gymPokemon[i]->heal(gymPokemon[i]->getMaxHP());
        gymPokemon[i]->isFainted();
        
    }
    return;
}