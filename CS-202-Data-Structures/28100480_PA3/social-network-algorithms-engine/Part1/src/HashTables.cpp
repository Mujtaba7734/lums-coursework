#include "HashTables.h"


// =======================
// Constructor
// =======================
template <typename T>
HashTable<T>::HashTable(CollisionHandle strategy)
{
    collision_strategy = strategy;
    table_size = 10;
    num_elements = 0;
    loadFactor = 0.0;

    if (collision_strategy == SEPARATE_CHAINING)
    {
        chaining_table.resize(table_size);
        probing_table = nullptr;
    }
    else
    {
        probing_table = new KeyValuePair[table_size];
        for (int i = 0; i < table_size; i++)
        {
            probing_table[i].isEmpty = true;
            probing_table[i].isDeleted = false;
        }
    }
}

// =======================
// Destructor
// =======================
template <typename T>
HashTable<T>::~HashTable()
{
    if (probing_table)
    {
        delete [] probing_table;
        probing_table = nullptr;
    }
}

// =======================
// Load Factor Calculation
// =======================
template <typename T>
void HashTable<T>::calculateLoadFactor()
{
    if (table_size == 0) return;

    loadFactor = (float) num_elements / table_size;
    if (loadFactor > loadFactorThreshold) resizeAndRehash();
}

// (Not on the cpp file) Resize and Rehash

template <typename T>
void HashTable<T>::resizeAndRehash()
{
    int old_size = table_size;
    int new_size = old_size * 2;

    if (collision_strategy == SEPARATE_CHAINING)
    {
        vector<vector<KeyValuePair>> old_chain = chaining_table;
        
        chaining_table.clear();
        chaining_table.resize(new_size);
        table_size = new_size;
        num_elements = 0;

        for (auto &chain: old_chain)
        {
            for (auto &pair: chain)
            {
                insertSeparateChaining(pair.key, pair.value);
            }
        }
    }
    else
    {
        KeyValuePair* old_table = probing_table;
        probing_table = new KeyValuePair[new_size];
        table_size = new_size;
        num_elements = 0;

        for(int i = 0; i < new_size; i++)
        {
            probing_table[i].isEmpty = true;
            probing_table[i].isDeleted = false;
        }

        for (int i = 0; i < old_size; i++)
        {
            if (!old_table[i].isEmpty && !old_table[i].isDeleted)
            {
                if (collision_strategy == LINEAR_PROBING)
                {
                    insertLinearProbing(old_table[i].key, old_table[i].value);
                }
                else
                {
                    insertQuadraticProbing(old_table[i].key, old_table[i].value);
                }
            }
        }
        delete [] old_table;
    }
} 

// =======================
// Linear Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertLinearProbing(int key, T value)
{
    if (key < 0) return;

    int index = hashFunction1(key);
    int first_deleted = -1;
    int i = 0;

    while (i < table_size)
    {
        int current = (index + i) % table_size;

        if (probing_table[current].isEmpty)
        {
            if (first_deleted != -1) current = first_deleted;
            
            probing_table[current].key = key;
            probing_table[current].value = value;
            probing_table[current].isEmpty = false;
            probing_table[current].isDeleted = false;

            num_elements++;
            return;
        }
        
        if (!probing_table[current].isDeleted && probing_table[current].key == key)
        {
            probing_table[current].value = value;
            return;
        }

        if (probing_table[current].isDeleted)
        {
            if (first_deleted == -1) first_deleted = current;
        }
        i++;
    }
}

template <typename T>
T HashTable<T>::searchLinearProbing(int key)
{
    if (key < 0) return T();

    int index = hashFunction1(key);
    int i = 0;

    while (i < table_size)
    {
        int current = (index + i) % table_size;
        if (probing_table[current].isEmpty) return T();
        if (!probing_table[current].isDeleted && probing_table[current].key == key) return probing_table[current].value;
        i++;
    }
    return T();
}

template <typename T>
void HashTable<T>::removeLinearProbing(int key)
{
    if (key < 0) return;

    int index = hashFunction1(key);
    int i = 0;

    while(i < table_size)
    {
        int current  = (index + i) % table_size;
        if (probing_table[current].isEmpty) return;

        if (!probing_table[current].isDeleted && probing_table[current].key == key)
        {
            probing_table[current].isDeleted = true;
            num_elements--;
            return;
        }
        i++;
    }
}

// =======================
// Quadratic Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertQuadraticProbing(int key, T value)
{
    if (key < 0) return;

    int index = hashFunction1(key);
    int first_deleted = -1;
    int i = 0;
    
    while (i < table_size)
    {
        int current = (index + i * i) % table_size;
        
        if (probing_table[current].isEmpty)
        {
            if (first_deleted != -1) current = first_deleted;
            
            probing_table[current].key = key;
            probing_table[current].value = value;
            probing_table[current].isEmpty = false;
            probing_table[current].isDeleted = false;

            num_elements++;
            return;
        }

        if (!probing_table[current].isDeleted && probing_table[current].key == key)
        {
            probing_table[current].value = value;
            return;
        }

        if (probing_table[current].isDeleted)
        {
            if (first_deleted == -1) first_deleted = current;
        }
        i++;
    }
}

template <typename T>
T HashTable<T>::searchQuadraticProbing(int key)
{
    if (key < 0) return T();
    
    int index = hashFunction1(key);
    int i = 0;
    
    while (i < table_size)
    {
        int current = (index + i * i) % table_size;

        if (probing_table[current].isEmpty) return T();
        if (!probing_table[current].isDeleted && probing_table[current].key == key) return probing_table[current].value;
        i++;
    }
    return T();
}

template <typename T>
void HashTable<T>::removeQuadraticProbing(int key)
{
    if (key < 0) return;

    int index = hashFunction1(key);
    int i = 0;

    while (i < table_size)
    {
        int current = (index + i * i) % table_size;

        if (probing_table[current].isEmpty) return;

        if (!probing_table[current].isDeleted && probing_table[current].key == key)
        {
            probing_table[current].isDeleted = true;
            num_elements--;
            return;
        }
        i++;
    }
}

// =======================
// Separate Chaining Methods
// =======================
template <typename T>
void HashTable<T>::insertSeparateChaining(int key, T value)
{
    if (key < 0) return;

    int index = hashFunction1(key);

    for (auto &chain : chaining_table[index])
    {
        if (chain.key == key)
        {
            chain.value = value;
            return;
        }
    }

    chaining_table[index].push_back(KeyValuePair(key, value, false));
    num_elements++;
}

template <typename T>
T HashTable<T>::searchSeparateChaining(int key)
{
    if (key < 0) return T();

    int index = hashFunction1(key);

    for (auto chain: chaining_table[index])
    {
        if (chain.key == key) return chain.value;
    }
    return T();
}

template <typename T>
void HashTable<T>::removeSeparateChaining(int key)
{
    if (key < 0) return;

    int index  = hashFunction1(key);

    auto &chain = chaining_table[index];

    for (auto i = chain.begin(); i != chain.end(); i++)
    {
        if(i->key == key)
        {
            chain.erase(i);
            num_elements--;
            return;
        }
    }
}

// =======================
// Insert
// =======================
template <typename T>
void HashTable<T>::insert(int key, T value)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            insertLinearProbing(key, value);
            break;
        case QUADRATIC_PROBING:
            insertQuadraticProbing(key, value);
            break;
        case SEPARATE_CHAINING:
            insertSeparateChaining(key, value);
            break;
    }
    calculateLoadFactor();
}

// =======================
// Search
// =======================
template <typename T>
T HashTable<T>::search(int key)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            return searchLinearProbing(key);
        case QUADRATIC_PROBING:
            return searchQuadraticProbing(key);
        case SEPARATE_CHAINING:
            return searchSeparateChaining(key);
    }
    return T(); // Default return
}

// =======================
// Remove
// =======================
template <typename T>
void HashTable<T>::remove(int key)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            removeLinearProbing(key);
            break;
        case QUADRATIC_PROBING:
            removeQuadraticProbing(key);
            break;
        case SEPARATE_CHAINING:
            removeSeparateChaining(key);
            break;
    }
    calculateLoadFactor();
}

// Please use this for debugging help
template <typename T>
void HashTable<T>::displayProbingTable()
{
    cout << "Current Table (size: " << table_size << "):\n";
    for (int i = 0; i < table_size; i++)
    {
        if (!probing_table[i].isEmpty)
            cout << "[" << i << "] -> Key: " << probing_table[i].key << ", Value: " << probing_table[i].value << endl;
        else
            cout << "[" << i << "] -> EMPTY\n";
    }
}

template class HashTable<int>;
template class HashTable<string>;