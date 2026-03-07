/// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Battle.cpp
#include "../include/Battle.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;



bool Battle::deterministic = true; // (Flag for testing, set to false for randomness, true for deterministic)

/*
    Ideally your battle class should be able to simulate a full battle between two Pokemon in both scenarios (deterministic & non-deterministic). 
    But for the case of simplicity, we will only implement the deterministic version of the battle class to make sure you win every battle
    BUT
    YOU MUST IMPLEMENT A NON DETERMINISTIC version of the battle for which a random seed is initialized within the constructors, which means you must pass the test sometimes and fail the test
    sometimes randomly.

    For the testing procedure, we will test the deterministic version of the battle class, and then we will test the non-deterministic version of the battle class.
    The deterministic version of the battle class should always pass the tests, and the non-deterministic version of the battle class should sometimes pass the tests and sometimes fail the tests.
*/




// Constructor
Battle::Battle(Pokemon &p1, Pokemon &p2)
    : pokemon1(p1), pokemon2(p2)
{

    isFinished = false;
    winner = nullptr;
    currentRound = 0;
    deterministic = false;
    //Initialize the variables here


    //Donot edit this condition ---------------------------------------------------
    if (!deterministic)
    {
        srand(time(0)); // Uses current time as seed for randomness
    }
}

// simulateRound: Simulate one round of battle
bool Battle::simulateRound()
{
    cout << "-------- Round "<< currentRound + 1 << " --------" << endl;
    
    if (isFinished)
    {
        return false;
    }

    if (currentRound >= MAX_ROUNDS)
    {
        history.addLog("Tie.");
        winner = nullptr;
        return false;
    }

    int index;
    int damage;
    Move *movepoki1 = nullptr;

    for (int i = 0; i < pokemon1.getMoveCount(); i++)
    {
        if (pokemon1.getMoveAtIndex(i) != nullptr)
        {
            movepoki1 = pokemon1.getMoveAtIndex(i); 
            index = i;
            break;
        }
    }
    
    Move defaultMove("tackle", 40, 100, 35);
    if (movepoki1 == nullptr || movepoki1->isOutOfPP()) 
    {
        movepoki1 = &defaultMove;
    }
    pokemon1.useMove(index);
    damage = calculateDamage(pokemon1, pokemon2, *movepoki1);
    pokemon2.takeDamage(damage);

    
    cout << "Round " << currentRound + 1 << ": " 
         << pokemon1.getName() << " deals " << damage 
         << " damage to " << pokemon2.getName() 
         << " (HP: " << pokemon2.getCurrentHP() << ")" << endl;
    
    history.addLog("Round " + to_string(currentRound + 1) + ": " 
                   + pokemon1.getName() + " deals " 
                   + to_string(damage) + " damage to " 
                   + pokemon2.getName() + " (HP: " 
                   + to_string(pokemon2.getCurrentHP()) + ")");

    if (pokemon2.isFainted()) 
    {
        isFinished = true;
        history.addLog("Pokemon 1 won.");
        winner = &pokemon1;
        return false;
    }


    Move *movepoki2 = NULL;

    for (int i = 0; i < pokemon2.getMoveCount(); i++)
    {
        if (pokemon2.getMoveAtIndex(i) != nullptr)
        {
            movepoki2 = pokemon2.getMoveAtIndex(i); 
            index = i;
            break;
        }
    }

    if (movepoki2 == NULL || movepoki2->isOutOfPP()) 
    {
        movepoki2 = &defaultMove;
    }

    pokemon2.useMove(index);
    damage = calculateDamage(pokemon2, pokemon1, *movepoki2);
    pokemon1.takeDamage(damage);

    cout << "Round " << currentRound + 1 << ": " 
         << pokemon2.getName() << " deals " << damage 
         << " damage to " << pokemon1.getName() 
         << " (HP: " << pokemon1.getCurrentHP() << ")" << endl;

         history.addLog("Round " + to_string(currentRound + 1) + ": " + pokemon2.getName() + " deals " 
         + to_string(damage) + " damage to " + pokemon1.getName() + " (HP: " 
         + to_string(pokemon1.getCurrentHP()) + ")");
         
    if (pokemon1.isFainted()) 
    {
        history.addLog("Pokemon 2 won.");
        winner = &pokemon2;
        isFinished = true;
        return false;
    }
    
    currentRound++;
    return true;

}

// simulateFullBattle: Run rounds until the battle is finished
void Battle::simulateFullBattle()
{
    while (!isFinished)
    {
        simulateRound();
    }
}

// getBattleHistory: Return a copy of the battle history
BattleHistory Battle::getBattleHistory() const
{
    BattleHistory newlogs;
    for(int i = 0; i<history.getLogCount(); i++)
    {
        newlogs.addLog(history.getLogAt(i));
    }
    return newlogs;
}

// getWinner: Returns pointer to the winning Pokemon, or nullptr on tie/incomplete
Pokemon *Battle::getWinner() const
{
    return winner;
}   

// calculateDamage: Compute damage given attacker, defender and move parameters.


int Battle::calculateDamage(Pokemon &attacker, Pokemon &defender, Move &move)
{
    int damage = 0;
    int randomvalue = 0;

    if (!deterministic)
    {
        randomvalue = rand() % 11 - 5;
    }

    damage = move.getPower();

    if (damage + randomvalue > 0)
    {
        damage += randomvalue;
    }

    return damage;
}