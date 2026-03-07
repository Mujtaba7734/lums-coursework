#include "../include/key.h"

typedef struct KeyChain{
    Key* key;
    DataType type;
    int units;
    int index;
    struct KeyChain* next;

} KeyChain;

KeyChain* initializeKeyChain(DataType type, int units, void* data)
{
    if (units == 0)
    {
        return NULL;
    }
    KeyChain *first_keychain = (KeyChain*) malloc (sizeof (KeyChain));

    if (first_keychain == NULL)
    {
        return NULL;
    }
    first_keychain -> key = initializeKey(type, units,data);
    first_keychain -> units = units;
    first_keychain -> type = type; 
    first_keychain-> index = 0;
    first_keychain-> next = NULL;

    return first_keychain;
}

KeyChain* keyChainMalloc(DataType type, int units, KeyChain* origin)
{
    if (units == 0 || origin == NULL)
    {
        return NULL;
    }

    KeyChain *new_keychain = (KeyChain*) malloc (sizeof (KeyChain));
    if (new_keychain == NULL)
    {
        return NULL;
    } 
    
    new_keychain ->type = type;
    new_keychain ->units = units;
    new_keychain ->key = keyMalloc(type, units);
    
    new_keychain ->next = NULL;

    KeyChain* temp = origin;
    while (temp-> next != NULL)
    {
        temp = temp -> next;
    } 

    temp-> next = new_keychain;
    new_keychain ->index = temp->index + 1; 

    return new_keychain;
}

void keyChainFree(KeyChain* key_chain, KeyChain* origin)
{
    if (key_chain == NULL || origin == NULL)
    {
        return;
    }

    if (key_chain->key != NULL)
    {
        keyFree(key_chain->key);
    }
    
    if (key_chain == origin)
    {
        origin = origin->next;
        free(key_chain);
        KeyChain* temp = origin;
        while (temp != NULL) 
        {
            temp->index--;
            temp = temp->next;
        }
        return;
    }

    KeyChain* temp = origin;
    while (temp -> next != NULL && temp -> next != key_chain)
    {
        temp = temp -> next;
    }

    if (temp->next == NULL)
    {
        return;
    }

    temp-> next = key_chain->next;
    free(key_chain);
    KeyChain* temp1 = temp->next;
    while (temp1)
    {
        temp1->index--;
        temp1 = temp1->next;
    }
    return;
}

void keyChainStoreData(KeyChain* key_chain, void* data)
{
    if (key_chain == NULL || data == NULL)
    {
        return;
    }
    keyStoreData(key_chain -> key, data);    
}

void keyChainAccessData(KeyChain* key_chain, void* dest)
{
    if (key_chain == NULL || dest == NULL)
    {
        return;
    }
    keyAccessData(key_chain -> key, dest, key_chain ->type, key_chain ->units);
}

KeyChain* findKeyChain(KeyChain* origin, int index) 
{ 
    if (origin == NULL || index < 0) 
    {
        return NULL;
    }

    KeyChain *temp = origin;

    while (temp != NULL) 
    {
        if (temp->index == index) 
        {
            return temp; 
        }
        temp = temp->next;
    }

    return NULL; 
}

void keyChainMoveData(KeyChain* src, KeyChain* dest) 
{
    if (src == NULL || dest == NULL)
     {
        return;
    }

    int i = (src->units) * (getSize(src->type));
    void* temporary = malloc(i);
    if (temporary == NULL) 
    {
        return;
    }

    keyAccessData(src->key, temporary, src->type, src->units);
    keyStoreData(dest->key, temporary);
    dest->type = src->type;
    dest->units = src->units;
    free(temporary);
    
}

KeyChain* getNext(KeyChain* key_chain)
{
   if (key_chain == NULL || key_chain -> next == NULL)
   {
    return NULL;
   }
   return key_chain->next;
}

KeyChain* getPrevious(KeyChain* key_chain, KeyChain* origin)
{
    if (origin == NULL || key_chain == NULL) 
    {
        return NULL;
    }

    KeyChain *temp = origin;
    
    if (temp == key_chain || temp -> next == NULL)
    {
        return NULL;
    }

    while (temp -> next != key_chain && temp-> next != NULL)
    {
        temp = temp -> next;
    }

    if (temp -> next == NULL)
    {
        return NULL;
    }

    return temp;

}

void keyChainClearData(KeyChain* origin) 
{
    if (origin == NULL)
    {
        return;
    }
    
    KeyChain *temp = origin;
    while (temp != NULL)
    {
        temp->units = 0;
        temp->index = 0;   
        keyFree(temp->key);
        temp ->key = NULL;
        temp = temp->next;
    }
}

void keyChainCompleteRelease(KeyChain* origin) 
{
    if (origin == NULL)
    {
        return;
    }
    
    KeyChain *temp = origin;
    while (temp != NULL)
    {
        temp->units = 0;
        temp->index = 0;
        KeyChain* next = temp-> next;
        if (temp->key != NULL)
        {
            keyFree(temp->key);
            temp->key = NULL; 
        }
        free(temp);
        temp = next;
    }
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

Key* getKey(KeyChain* key_chain){
    return key_chain->key;
}

DataType getType(KeyChain* key_chain){
    return key_chain->type;
}

int getUnits(KeyChain* key_chain){
    return key_chain->units;
}

int getIndex(KeyChain* key_chain){
    return key_chain->index;
}