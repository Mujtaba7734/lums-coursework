//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/BattleHistory.cpp
#include "../include/BattleHistory.hpp"
#include <iostream>

// Private expansion
void BattleHistory::expandLogs()
{
    int new_capacity = capacity * 2;
    string* new_logs = new string[new_capacity];
    for (int i = 0; i < count; i++)
    {
        new_logs[i] = logs[i];
    }
    delete[] logs;
    logs = new_logs;
    capacity = new_capacity;
}

// Constructor
BattleHistory::BattleHistory() 
{
    count  = 0;
    capacity = 1;
    logs = new string [capacity];
}

// Copy constructor
BattleHistory::BattleHistory(const BattleHistory &other) 
{
    count = other.count;
    capacity = other.capacity;
    logs = new string [other.capacity];
    for (int i = 0; i < other.count; i++)
    {
        this->logs[i] = other.logs[i];
    }
}

// Destructor
BattleHistory::~BattleHistory()
{
    if (logs != NULL)
    {
        delete [] logs;
        logs = NULL;
    }
}

// Log management
void BattleHistory::addLog(const string &entry)
{
    if (count >= capacity)
    {
        expandLogs(); 
    }
    logs[count] = entry;
    count++;

    return;
}

string BattleHistory::getLogAt(int index) const
{
    if(index >= count || index < 0)
    {
        return "";
    }
    return this->logs[index];

}

int BattleHistory::getLogCount() const
{
    return count;
}

void BattleHistory::clearLogs()
{
    if (logs)
    {
        delete []logs;
    }
    count=0;

}

//This function will be used to return all logs in a single "multiline" string
string BattleHistory::getAllLogs() const
{
    string result;

    for (int i = 0; i < count; i++) 
    {
        result += logs[i] + "\n";  
    }
    return result;
}

void BattleHistory::copyFrom(const BattleHistory &other)
{
    count = other.count;
    capacity = other.capacity;
    delete[] logs;
    if(other.logs != NULL)
    {
        logs = new string[capacity];
        for(int i = 0; i<count; i++)
        {
            logs[i] = other.logs[i];
        }
    }
    else
    {
        logs = NULL;
    }
}