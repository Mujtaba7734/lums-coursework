#include "../include/navigator.h"
#include "../include/keychain.h"
#include "../include/locator.h"
#include "../include/key.h"

typedef struct KeyChain
{
    Key *key;
    DataType type;
    int units;
    int index;
    struct KeyChain *next;

} KeyChain;

typedef struct Locator
{
    char *identifier;
    uintptr_t address;

} Locator;

void completeDeallocation(VaultNavigator **v_ptr)
{
    if (*v_ptr == NULL) 
    {
        printf("completeDeallocation: v_ptr is NULL\n");
        return;
    }

    KeyChain *origin = (KeyChain *)getOrigin((*v_ptr)->map); 
    if (origin == NULL)
    {
        printf("completeDeallocation: origin is NULL\n");
        return;
    }

    printf("completeDeallocation: Calling keyChainClearData\n");
    keyChainClearData(origin);

    printf("completeDeallocation: Calling keyChainCompleteRelease\n");
    keyChainCompleteRelease(origin);

    printf("completeDeallocation: Clearing map\n");
    clearMap((*v_ptr)->map);

    printf("completeDeallocation: Releasing map\n");
    releaseMap((*v_ptr)->map);

    printf("completeDeallocation: Freeing v_ptr\n");
    free(*v_ptr);
    *v_ptr = NULL;
    printf("\nMemory deallocated Successfully.\n");
    
}

int isFragmented(KeyChain *origin)
{
    if (origin == NULL)
    {
        return 1;
    }

    KeyChain *temporary = origin;

    while (temporary != NULL)
    {
        if (temporary->key == NULL)
        {
            return 1;
        }
        temporary = getNext(temporary);
    }

    return 0; 
}

void printLocator(Locator *map)
{
    if (map == NULL) 
    {
        return;
    }

    FILE *locator_file = fopen("../bin/locator.txt", "w"); 

    if (locator_file == NULL) 
    {
        return;
    }

    int i = 0;

    while (map[i].address != (uintptr_t)NULL)
    {
        i++;
    }

    fprintf(locator_file, "-----------------------------------\n");

    for (int j = 1; j < i; j++) 
    {
        fprintf(locator_file, "Index %d : %s : %p \n", j, map[j].identifier, (void *)map[j].address);
    }

    fprintf(locator_file, "-----------------------------------\n");

    fclose(locator_file); 

    return;
}

// ---------------- Instructions for Test cases --------------//

/*
You can create an int main() function below to test your escape.c.
To test escape.c, navigate to the src directory in the terminal. You can do this by "cd src".

Then run the following command:

gcc escape.c key.c keychain.c navigator.c locator.c -o test

And then:

./test

Delete your int main() afterwards, or comment it out because it will not let you test other files.
*/

// int main()
// {
//     int total = 0;
//     DataType types[10] = {RED, RED, GREEN, BLUE, BLACK, BLACK, RED, BLUE, GREEN, RED};

//     printf("\033[35mTesting initialization:\033[0m");
//     char *data = "CS200";
//     int units = 6;
//     KeyChain *origin = initializeKeyChain(types[0], units, data);
//     KeyChain *keyChain_1 = keyChainMalloc(types[1], 7, origin);
//     KeyChain *keyChain_2 = keyChainMalloc(types[2], 8, origin);
//     KeyChain *keyChain_3 = keyChainMalloc(types[3], 3, origin);

//     VaultNavigator* v_ptr = initializeNavigator(10);

//     completeDeallocation(&v_ptr);

//     Locator map[] = {
//         {"origin", (uintptr_t)0x1000},                                   
//         {"element_0", (uintptr_t)0x1000000a},  
//         {"element_1", (uintptr_t)0x1000000a},    
//         {"element_2", (uintptr_t)0x1000000a}, 
//         {"element_3", (uintptr_t)0x1000000a}, 
//         {"element_4", (uintptr_t)0x1000000a}, 
//         {"element_5", (uintptr_t)0x1000000a}, 
//         {"element_6", (uintptr_t)0x1000000a}, 
//         {"element_7", (uintptr_t)0x10000014},     
//         {"element_8", (uintptr_t)0x1000001e},
//         {NULL, 0}                      
//     };

//     if(isFragmented(origin))
//     {
//         printf("Fragmentation occurs.\n");

//     }
//     else
//     printf("No fragmentation occurs.\n");

//     printLocator(map);

    
//     printf("\nTest cases executed. Check bin/locator.txt for output.\n");

//     return 0;
// }