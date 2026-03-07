#include "SehriLab.hpp"
#include <iostream>
using namespace std;

// ------------------------------
// SehriItem class implementations
// ------------------------------

// Default constructor
SehriItem::SehriItem() : id(0), name(""), baseCost(0.0f) 
{
}

// Parameterized constructor
SehriItem::SehriItem(int id, string name, float baseCost)
{
    this->id = id;
    this->name = name;
    this->baseCost = baseCost;
}

// Copy constructor
SehriItem::SehriItem(const SehriItem &other)
    : id(other.id), name(other.name), baseCost(other.baseCost) {}

void SehriItem::displayDetails() 
{
    cout << "Id: " << this->id;
    cout << ", Name: " << this->name;
    cout << ", Base Cose: " << this->baseCost;
}
float SehriItem::getBaseCost() 
{
    return baseCost;
}
string SehriItem::getName() 
{
    return name;
}
float SehriItem::calculateDiscount(int quantity) { return 0.0f; }

// ------------------------------
// Paratha class implementations
// ------------------------------

// Default constructor
Paratha::Paratha() : SehriItem(), stuffingType(""), spiceLevel(0), oil(0.0f) {}

// Parameterized constructor
Paratha::Paratha(int id, string stuffingType, float baseCost, int spiceLevel, float oil)
    : SehriItem(id, "Paratha", baseCost), stuffingType(stuffingType), spiceLevel(spiceLevel), oil(oil) {}

// Copy constructor
Paratha::Paratha(const Paratha &other)
    : SehriItem(other), stuffingType(other.stuffingType), spiceLevel(other.spiceLevel), oil(other.oil) {}

void Paratha::displayDetails() 
{
    SehriItem::displayDetails();
    cout << "Stuffing type: " << this->stuffingType;
    cout << ", Spice Level: " << this->spiceLevel;
    cout << ", oil: " << this->oil << endl;
}
float Paratha::calculateDiscount() 
{ 
    if (this->stuffingType == "Aloo")
    {
        return (getBaseCost() * 0.90f);
    }
    return getBaseCost();
}

int Paratha::getSpiceLevel() { return spiceLevel; }
string Paratha::getStuffingType() { return stuffingType; }
float Paratha::getOil() { return oil; }

// ------------------------------
// Chai class implementations
// ------------------------------

// Default constructor
Chai::Chai() : SehriItem(), sugarAmount(0), chaiType("") {}

// Parameterized constructor
Chai::Chai(int id, float baseCost, int sugarAmount, string chaiType)
    : SehriItem(id, "Chai", baseCost), sugarAmount(sugarAmount), chaiType(chaiType) {}

// Copy constructor
Chai::Chai(const Chai &other)
    : SehriItem(other), sugarAmount(other.sugarAmount), chaiType(other.chaiType) {}

void Chai::displayDetails() 
{
    SehriItem::displayDetails();
    cout << "Sugar Amount: " << this->sugarAmount;
    cout << ", Type of chai: " << this->chaiType;
}
float Chai::calculateDiscount() 
{
    if (this->chaiType == "Ilaichi")
    {
        return (baseCost * 0.95f);
    }
    return baseCost;
}
int Chai::getSugarAmount() 
{ 
    return this->sugarAmount;
}
string Chai::getChaiType() { return chaiType; }
string Chai::getName() { return name; }
float Chai::getBaseCost() { return baseCost; }

// ------------------------------
// SehriFoodCounter class implementations
// ------------------------------

// Default constructor
SehriFoodCounter::SehriFoodCounter() : parathaCount(0), chaiCount(0) { }

// Copy constructor
SehriFoodCounter::SehriFoodCounter(const SehriFoodCounter &other)
{
    parathaCount = other.parathaCount;
    chaiCount = other.chaiCount;
    for (int i = 0; i < parathaCount; i++)
    {
        parathas[i] = new Paratha(*other.parathas[i]);
    }
    for (int i = 0; i < chaiCount; i++)
    {
        chais[i] = new Chai(*other.chais[i]);
    }
    
}

void SehriFoodCounter::addParatha(int id, string stuffingType, float baseCost, int spiceLevel, float oil) 
{
    
    if (parathaCount >= 0 && parathaCount < 10)
    {
        parathas[parathaCount] = new Paratha(id, stuffingType, baseCost, spiceLevel, oil);
        parathaCount++;
    } 
}
void SehriFoodCounter::addChai(int id, float baseCost, int sugarAmount, string chaiType) 
{
    
    if (chaiCount >= 0 && chaiCount < 10)
    {
        chais[chaiCount] = new Chai(id, baseCost, sugarAmount, chaiType);
        chaiCount++;
    } 
    
}
void SehriFoodCounter::getParathas(Paratha *actualParathas[], int &count) const 
{
    for (int i =0; i < parathaCount; i++)
    {
        actualParathas[i] = new Paratha(*parathas[i]);
        count++;
    }
}
void SehriFoodCounter::getChais(Chai *actualChais[], int &count) const 
{
    for (int i =0; i < chaiCount; i++)
    {
        actualChais[i] = new Chai(*chais[i]);
        count++;
    }
    // Error 
}
Paratha *SehriFoodCounter::findSpiciestParatha() 
{
   
    int max = 0;
    int max_index = 0;
    for (int i =0; i< parathaCount; i++)
    {
        if (parathas[i]->getSpiceLevel() >= max )
        {
            max = parathas[i]->getSpiceLevel();
            max_index = i;
        }
    }
    return parathas[max_index];    
}

string SehriFoodCounter::getMostOrderedParathaType() 
{
    
    int max_repeated =0;
    int index_repeated = 0;
    for (int i =0; i < parathaCount; i++)
    {
        int repeated = 0;
        for (int j= i + 1; i< parathaCount; j++)
        {
            if (parathas[i]->getStuffingType() == parathas[j]->getStuffingType())
            {
                repeated++;
            }
        }
        if (repeated > max_repeated)
        {
            max_repeated = repeated;
            index_repeated = i;
        }
    }
    return parathas[index_repeated]->getStuffingType();
}
Paratha *SehriFoodCounter::getParathaWithMaxOil() 
{
    cout << "check" << endl;
    int max = 0;
    int max_index = 0;
    for (int i =0; i< parathaCount; i++)
    {
        if (parathas[i]->getOil() >= max )
        {
            max = parathas[i]->getOil();
            max_index = i;
        }
    }
    return parathas[max_index];  
}
string SehriFoodCounter::getMostOrderedChaiType() 
{
    cout << "check" << endl;
    int max_repeated = 0;
    int index_repeated = 0;
    for (int i =0; i < chaiCount; i++)
    {
        int repeated = 0;
        for (int j= i + 1; i< chaiCount; j++)
        {
            if (chais[i]->getChaiType() == chais[j]->getChaiType())
            {
                repeated++;
            }
        }
        if (repeated > max_repeated)
        {
            max_repeated = repeated;
            index_repeated = i;
        }
    }
    return chais[index_repeated]->getChaiType();
}
Chai **SehriFoodCounter::getMostSugaryChai(int &count) 
{
    if (chaiCount == 0)
    {
        count  =0;
        return nullptr;
    }
    int max = 0;
    int max_index =0;
    for (int i = 0; i< chaiCount; i++)
    {
        if (chais[i]->getSugarAmount() > max)
        {
            max = chais[i]->getSugarAmount();
            max_index =i;
        }
    }
    Chai **sweetchai = new Chai *[chaiCount];
    count = 0;
    for (int i =0; i < chaiCount; i++)
    {
        if (chais[i]->getSugarAmount() == max)
        {
            sweetchai[count++] = chais[i];
        }   
    }
    return sweetchai;

    // return nullptr;
}
float SehriFoodCounter::calculateTotalBill() 
{
    int total =0;
    for (int i =0; i < parathaCount; i++)
    {
        if (parathas[i]->calculateDiscount() != 0.0)
        {
            total += parathas[i]->calculateDiscount();
        }
        else
        {
            total += parathas[i]->getBaseCost();
        }
    }
    for (int i =0; i < chaiCount; i++)
    {
        if (chais[i]->calculateDiscount() != 0.0)
        {
            total += chais[i]->calculateDiscount();
        }
        else
        {
            total += chais[i]->getBaseCost();
        }
    }
    return total;
}
void SehriFoodCounter::displayParathas() 
{
    for (int i =0; i < parathaCount; i++)
    {
        parathas[i]->displayDetails();
    }
}
void SehriFoodCounter::displayChais() 
{
    for (int i =0; i < chaiCount; i++)
    {
        chais[i]->displayDetails();
    }
}
SehriFoodCounter::~SehriFoodCounter() 
{
    // for (int i =0; i < parathaCount; i++)
    // {
    //     delete parathas[i];
    // }
    // for (int i =0; i < chaiCount; i++)
    // {
    //     delete chais[i];
    // }
    
}
