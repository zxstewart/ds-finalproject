#include <string>
#include <list> //idk if we need this but included just in case
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//open addressing means values are stored directly in the hash table rather than using buckets

struct node     //sorry for confusion... i renamed it back to node because separate files and less typing...i'm a little lazy
{
    int key;
};

class HashTable
{
    const int capacity = 40009;
    int tableSize;  // No. of items in table
    node* *table;
    int colNum =0;  //renamed to make it shorter and less of a pain to type out-- number of collisions
    node* createNode(int key);
public:
    HashTable();  // Constructor
    bool insertItem(int key);// inserts a key into hash table
    //do we need a remove function? i don't think so but idk
    unsigned int hashFunction(int key);// hash function to map values to key
    void printTable();
    node* searchItem(int key);//searches for ptr with given key
    int getNumOfCollision();
};

//-------------------------------BEGIN CLASS FUNCTIONS-------------------------------------------------------------------

HashTable::HashTable()//seems right to me so far... idk if anything needs to be added
{
    tableSize = 0;
    table = new node*[capacity];
    for(int i = 0; i < capacity; i++)
    {
        table[i] = NULL;
    }
    
}

unsigned int HashTable::hashFunction(int key)
{
    int index = key % capacity;//remainder of key/tableSize
    return index;
}

 bool HashTable::insertItem(int key)    //returns true if able to add
 {
    bool added = false;
    node* temp = createNode(key);

    int idx = hashFunction(key);
    while(table[idx] != NULL && table[idx]->key != key)
    {
        idx++;
        idx %= capacity;
    }
    if(table[idx] == NULL)
    {
        tableSize++;
        table[idx] = temp;
        added = true;
    }
    return added;
 }

void HashTable:: printTable()
{
    cout << "------------------\n";
    cout << "Printing Table..." << endl;
    for(int i = 0; i < capacity; i++)
    {
        if(table[i] != NULL)
        {
            cout << table[i]->key << endl;
        }
        else
        {
            continue;
        }
    }
    cout << "# of items = " << tableSize << endl;
    cout << "------------------\n";
    return;
}

node* HashTable:: searchItem(int key)
{
    int idx = hashFunction(key);//find the bucket its stored in
    bool foundKey = false;
    int count = 0;

    while(table[idx] != NULL)
    {
        if(count++ >= capacity)
        {
            //circle back to beginning of table array somehow
        }
        if(table[idx]->key == key)
        {
            return table[idx];
            foundKey = true;
            idx++;
            idx %= capacity;
        }
        if(!foundKey)
        {
            return NULL;
        }
    }
}

int HashTable::getNumOfCollision()
{
    //yeah i really have no idea how to do this...
    return colNum;
}

//------------------------------------------MAIN-------------------------------------------
int main()
{
    //run insert and search time tests and write info to a file
}