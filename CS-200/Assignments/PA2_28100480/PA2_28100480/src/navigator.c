#include "../include/keychain.h"
#include "../include/locator.h"
#include "../include/navigator.h"

VaultNavigator* initializeNavigator(int num_allocations)
{ 
    if (num_allocations == 0)
    {
        return NULL;
    }
    VaultNavigator * navigator = (VaultNavigator *) malloc (sizeof (VaultNavigator) );
    if (navigator == NULL)
    {
        return NULL;
    }
    navigator ->key_chain = initializeKeyChain(RED, 7, "origin");

    if (navigator->key_chain == NULL)
    {
        return NULL;
    }
    
    navigator ->map = initializeMap(num_allocations, navigator->key_chain, "origin");
    
    if (navigator ->map == NULL)
    {
        return NULL;
    }
    navigator->key_chain = NULL; 

    return navigator;
}

void navigatorMalloc(VaultNavigator *v_ptr, DataType type, int units, char *identifier)
{
    if (v_ptr == NULL || v_ptr->map == NULL || units == 0 || identifier == NULL)
    {
        return;
    }
    if (getPointer(v_ptr->map, identifier) != NULL)
    {
        return;
    }
    KeyChain *origin = (KeyChain *)getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }
    KeyChain *new_key = keyChainMalloc(type, units, origin);
    if (new_key == NULL)
    {
        return;
    }
    makeEntry(&v_ptr->map, (void *)new_key, identifier);
    v_ptr->key_chain = new_key;
}

void navigatorFree(VaultNavigator* v_ptr, char* identifier)
{
    if (v_ptr == NULL || identifier == NULL)
    {
        return;
    }

    KeyChain *origin = getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }

    KeyChain *free_key = getPointer(v_ptr->map, identifier);
    if (free_key == NULL)
    {
        return;
    }
    keyChainFree(free_key, origin);
    removeEntry(v_ptr->map, identifier);

    if (v_ptr->map == NULL)
    {
        return;
    }
    
}

void storeData(VaultNavigator* v_ptr, char* identifier, void* data)
{
    if (v_ptr == NULL || identifier == NULL || data == NULL)
    {
        return;
    }

    KeyChain *origin = getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }

    KeyChain *store_key = getPointer(v_ptr->map, identifier);
    if (store_key == NULL)
    {
        return;
    }
    if (origin == store_key)
    {
        return;
    }
    keyChainStoreData(store_key, data);
}

void accessData(VaultNavigator* v_ptr, char* identifier, void* dest)
{
   if (v_ptr == NULL || identifier == NULL || dest == NULL)
    {
        return;
    }

    KeyChain *origin = getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }

    KeyChain *access_key = getPointer(v_ptr->map, identifier);
    if (access_key == NULL)
    {
        return;
    }
    if (origin == access_key)
    {
        return;
    }
    keyChainAccessData(access_key, dest);
}

void incrementPointer(VaultNavigator* v_ptr)
{
    if (v_ptr == NULL)
    {
        return;
    }

    KeyChain *inc_pointer = getNext(v_ptr->key_chain);
    if (inc_pointer == NULL)
    {
        return;
    }
    v_ptr->key_chain = inc_pointer; 
}

void decrementPointer(VaultNavigator* v_ptr)
{
    if (v_ptr == NULL)
    {
        return;
    }

    KeyChain *origin = getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }

    KeyChain *dec_pointer = getPrevious(v_ptr->key_chain, origin);

    if (dec_pointer == NULL)
    {
        return;
    }

    if (dec_pointer == origin)
    {
        return;
    }
    
    v_ptr->key_chain = dec_pointer;
}

void changePointer(VaultNavigator* v_ptr, char* identifier)
{
    if (v_ptr == NULL || identifier == NULL)
    {
        return;
    }

    KeyChain *origin = getOrigin(v_ptr->map);
    if (origin == NULL)
    {
        return;
    }

    KeyChain *pointer_key = getPointer(v_ptr->map, identifier);
    if (pointer_key == NULL)
    {
        return;
    }
    if (origin == pointer_key)
    {
        return;
    }
    v_ptr->key_chain = pointer_key;
}
