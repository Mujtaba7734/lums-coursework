//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Shop.cpp
#include "../include/Shop.hpp"
#include <iostream>

// Private expansions
void Shop::expandPotions()
{
    return;
}

void Shop::expandArmors()
{
    return;
}

// Constructor
Shop::Shop()
{
    potionCount = 0;
    potionCapacity = 0;

    potions = new Potion[potionCapacity];
    
    armorCount = 0;
    armorCapacity = 0;

    armors = new Armor[armorCapacity];
    
}

// Destructor
Shop::~Shop()
{
    if (potions != NULL)
    {
        delete [] potions;
        potions = NULL;
    }

    if (armors != NULL)
    {
        delete [] armors;
        armors = NULL;
    }
}

// Inventory management
void Shop::addPotion(const Potion &p)
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
            return;
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
    return;
}

void Shop::addArmor(const Armor &a)
{
    if (armorCount >= armorCapacity)
    {
        int new_capacity;

        if(armorCapacity == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = 2*armorCapacity;
        }

        Armor *new_armor = new Armor [new_capacity];
        if (new_armor == NULL)
        {
            return;
        }
        for (int i = 0; i < armorCapacity; i++)
        {
            new_armor[i] = armors[i];
        }
        delete [] armors;
        armors = new_armor;
        armorCapacity = new_capacity; 
    }
    this->armors[armorCount] = a;
    armorCount++;
    return;
}

bool Shop::removePotion(int index)
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

bool Shop::removeArmor(int index)
{
    if (index < 0 || index > armorCount)
    {
        return false;
    }
    for (int j = index; j < armorCount - 1; j++)
    {
        armors[j] = armors[j+ 1];
    } 
    armorCount--;
    return true;
}

// Getters
int Shop::getPotionCount() const 
{ 
    return potionCount;
}
int Shop::getArmorCount() const 
{ 
    return armorCount;
}

Potion *Shop::getPotionAtIndex(int index) const
{
    if (index < 0 || index > potionCount)
    {
        return nullptr;
    }
    return &potions[index];
}

Armor *Shop::getArmorAtIndex(int index) const
{
    if (index < 0 || index > armorCount)
    {
        return nullptr;
    }
    return &armors[index];
}

// Shopping functionality
bool Shop::sellPotionTo(int potionIndex, Trainer &buyer)
{
    if (potionIndex < 0 || potionIndex > potionCount)
    {
        return false;
    }
    if (buyer.getMoney() < potions[potionIndex].getCost())
    {
        return false;
    }
    buyer.spendMoney(potions[potionIndex].getCost());
    buyer.addPotion(potions[potionIndex]);
    removePotion(potionIndex);
    return true;
}

bool Shop::sellArmorTo(int armorIndex, Trainer &buyer, int pokemonIndex)
{
    if (armorIndex < 0 || armorIndex > potionCount)
    {
        return false;
    }
    if (buyer.getMoney() < (armors[armorIndex].getDefenseBonus() * 10))
    {
        return false;
    }
    buyer.spendMoney((armors[armorIndex].getDefenseBonus() * 10));
    buyer.getPokemonAtIndex(pokemonIndex)->equipArmor(armors[armorIndex]);

    removeArmor(armorIndex);
}

void Shop::displayInventory() const
{
    cout << "----------------" << endl;
    cout << "     Potions    " << endl;
    cout << "----------------" << endl;
    cout << "  Potion Name   |  Heal Amout | Cost " << endl;
    for (int i = 0; i < potionCount; i++)
    {
        cout << potions[i].getName() << " | " << potions[i].getHealAmount() << " | " << potions[i].getCost() << endl;
    } 
    cout << endl << endl;
    cout << "----------------" << endl;
    cout << "     Armor    " << endl;
    cout << "----------------" << endl;
    cout << "  Armor Name   |  Defense Bonus | Weight " << endl;
    for (int i = 0; i < armorCount; i++)
    {
        cout << armors[i].getName() << " | " << armors[i].getDefenseBonus() << " | " << armors[i].getWeight() << endl;
    } 
    return;
}