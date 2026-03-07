//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/GameState.cpp
#include "../include/GameState.hpp"
#include <iostream>

// Constructor
GameState::GameState(Trainer *p, Gym *g, Shop *s)
{
    player = p;
    currentGym = g;
    shop = s;
    badges = 0;
    playerName = "Player";
    gameActive = true;
}

// Destructor
GameState::~GameState()
{
    // We may or may not own these pointers. If we do, we delete them:
    // delete player;
    // delete currentGym;
    // delete shop;
}

// Getters
Trainer *GameState::getPlayer() const 
{ 
    return player;
}
Gym *GameState::getCurrentGym() const 
{   
    return currentGym;
}
Shop *GameState::getShop() const 
{ 
    return shop;
}
int GameState::getBadges() const 
{ 
    return badges;
}
string GameState::getPlayerName() const 
{ 
    return playerName;
}
bool GameState::isGameActive() const 
{ 
    return gameActive;
}

// Setters
void GameState::setPlayer(Trainer *p) 
{ 
    player = p;
    return;
}
void GameState::setCurrentGym(Gym *g) 
{ 
    currentGym = g;
    return;
}
void GameState::setShop(Shop *s) 
{ 
    shop = s;
    return;
}
void GameState::addBadge() 
{ 
    badges++;
    return;
}
void GameState::setPlayerName(const string &name) 
{ 
    playerName = name;
    return;
}
void GameState::setGameActive(bool active) 
{ 
    gameActive = active;
    return;
}

// Save game
bool GameState::saveGame(const string &filename)
{
    ofstream file(filename);
    if (!file) 
    {
        cerr << "Error opening file for writing.\n";
        return false;
    }
    file << playerName << endl;
    file << badges << endl;
    file << gameActive << endl;
    file.close();
    return true;
}

// Load game
bool GameState::loadGame(const string &filename)
{
    ifstream file(filename);
    if (!file) 
    {
        cerr << "Error opening file for reading.\n";
        return false;
    }
    getline(file, playerName);
    file >> badges;
    file >> gameActive;
    file.close();
    return true;
}

// Reset game
void GameState::resetGame()
{
    badges = 0;
    gameActive = false;
    return;
}