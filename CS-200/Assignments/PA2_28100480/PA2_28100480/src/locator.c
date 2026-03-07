#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Locator {
    char* identifier;
    uintptr_t address;

} Locator;

Locator* initializeMap(int num_allocations, void* addr, char* identifier)
{
    Locator * first_locator = calloc(num_allocations +2, sizeof(Locator));
    
    if (first_locator == NULL)
    {
        return NULL;
    }

    first_locator[0].address = (uintptr_t) addr;
    first_locator[0].identifier = identifier;

    first_locator[num_allocations + 1].address = -1;  // making last node's address -1, to find the size of array by traversing array till -1
    first_locator[num_allocations + 1].identifier = NULL;

    

    return first_locator;
}

void releaseMap(Locator* map)
{
    if (map == NULL)
    {
        return;
    }
    free(map);
    map = NULL;
}

void clearMap(Locator* map)
{
    if (map == NULL)
    {
        return;
    }
    int i =0;
    while (map[i].address != -1)
    {
        map[i].identifier = NULL;
        map[i].address = 0;
        i++;
    }
}

Locator* resizeMap(Locator* map, int new_num_allocs)
{
    int i = 0;
    while (map[i].address != -1) 
    {
        i++;
    }

    Locator* temp = realloc(map, (new_num_allocs + 2) * sizeof(Locator));
    if (temp == NULL) 
    {
        return NULL; 
    }
    map = temp;

    for (int j = i; j < new_num_allocs + 1; j++) 
    {
        map[j].address = 0;
        map[j].identifier = NULL;
    }

    map[new_num_allocs + 1].address = -1;
    return map;
}

void makeEntry(Locator** map, void* addr, char* identifier)
{

    int i = 0;
    while ((*map)[i].address != -1 && (*map)[i].address != 0) 
    {
        i++;
    }

    if ((*map)[i].address == 0) 
    {
        (*map)[i].address = (uintptr_t) addr;
        (*map)[i].identifier = identifier;
    }

    
    if ((*map)[i].address == -1) 
    {
        
        Locator* temp = realloc(*map, (i * 2) * sizeof(Locator));
        if (temp == NULL) 
        {
            return; 
        }
        *map = temp;

        for (int j = i; j < (i * 2); j++) 
        {
            (*map)[j].address = 0;
            (*map)[j].identifier = NULL;
        }
        (*map)[i*2].address = -1; 
    }

    (*map)[i].address = (uintptr_t)addr;
    (*map)[i].identifier = identifier;
    
}

void removeEntry(Locator* map, char* identifier)
{
    if (map == NULL || identifier == NULL)
    {
        return;
    }

    if (map[0].identifier == identifier)
    {
        if (map[1].identifier == NULL)
        {
            map[0].identifier = NULL;
            map[0].address = 0;
        }
        else
        {
            return;
        }
    }

    int i =0;
    while (map[i].address != -1)
    {
        i++;
    }

    int j =0;
    
    while (map[j].identifier != identifier)
    {
        j++;
    }    

    map[j].address =0;
    map[j].identifier = NULL;

    for (int swap = j; swap < i; swap++)
    {
        map[swap].address = map[swap + 1].address;
        map[swap].identifier = map[swap + 1].identifier;
    }

    map[i - 1].identifier = NULL;
    map[i - 1].address = 0;
}

void* getOrigin(Locator* map)
{
    if (map == NULL)
    {
        return NULL;
    }
    return (void *) map[0].address;
}

void* getPointer(Locator* map, char* identifier)
{
    if (map == NULL || identifier == NULL)
    {
        return NULL;
    }
    
    int i = 0;
    while (map[i].address != NULL) 
    {
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        if (strcmp(map[j].identifier, identifier) == 0)
        {
            return (void *) map[j].address;
        }
    }
    return NULL;
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

uintptr_t getAddress(Locator* map, int index){
    return map[index].address;
}

char* getIdentifier(Locator* map, int index){
    return map[index].identifier;
}