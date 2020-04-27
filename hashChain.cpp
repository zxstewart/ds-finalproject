#include <string>
#include <list> //idk if we need this but included just in case
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct node     //sorry for confusion... i renamed it back to node because separate files and less typing...i'm a little lazy
{
    int key;
    struct node* next;
};

class HashTable
{
    const int tableSize = 40009;  // No. of buckets (linked lists) should be 400 right? but we establish that later in the main i think

    // Pointer to an array containing buckets
    node* *table;   //this is the linked list array of size 400 that stores integers
    //int colNum =0;  //renamed to make it shorter and less of a pain to type out
    node* createNode(int key, node* next);
public:
    HashTable();  // Constructor
    bool isEmpty(); //check if the table is empty
    bool insertItem(int key);// inserts a key into hash table
    //do we need a remove function? i don't think so but idk
    unsigned int hashFunction(int key);// hash function to map values to key
    int numIndexItems(int index);//num items in the bucket (LL) at specified table index
    void printTable();
    node* searchItem(int key);//searches for ptr with given key
    //int getNumOfCollision(); don't need this here because chain hashing avoids collisions
};

//-------------------------------BEGIN CLASS FUNCTIONS-------------------------------------------------------------------

HashTable::HashTable()//seems right to me so far... idk if anything needs to be added
{
    table = new node *[tableSize]; //... this creates an array of ptrs to nodes
    for(int i = 0 ; i < tableSize; i++)//setting everything to null
    {
        table[i] = new node;
        table[i]->key = NULL;
        table[i]->next = NULL;
    }
}

bool HashTable::isEmpty()
{
    int sum = 0;
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i]->key != NULL)
        {
            sum += table[i]->key;
        }
        else
        {
            continue;   //apparently this is a real thing i can do that i'm quite happy to have learned about lol
        }
    }
    if(sum == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int HashTable::hashFunction(int key)
{
    int index = key % tableSize;//remainder of key/tableSize
    return index;
}

 bool HashTable::insertItem(int key)    //returns true if able to add
 {
     bool return_Val = false;
     int index = hashFunction(key);
     if(isEmpty)//if its empty
     {
        table[index]->key = key;//overwrite with key given
        return_Val = true;
     }
     else//meaning there is already a value in its spot
     {
         node* ptr = table[index];// first item in bucket
         node* n = new node;//new item
         n->key = key; //initializing key
         n->next = NULL; // initializing next to nothing
         //next need to add to end of linked list in the bucket
         while(ptr->next!= NULL)//while next element != NULL
         {
             ptr = ptr->next;//go through to next
         }
         //ptr is now pointing to last item in list
         ptr->next = n; // linking the last item in list to newly created item
        return_Val = true;
     }
 }

int HashTable::numIndexItems(int index)
{
    int count = 0;
    if(table[index]->key != NULL)
    {
        count++;//count first item
        node* ptr = table[index];//points to being of list thats in tht bucket
        while(ptr->next != NULL) //as long as next ptr is not nothing
        {
            count++; //increment counter
            ptr=ptr->next; // move ptr to next item
        }
    }
    return count;//by now we have all items accounted for in that list
}


void HashTable:: printTable()
{
    int num; //num of elements in each bucket
    for(int i = 0; i < tableSize; i++)//remember tableSize is the no. of buckets (linked lists)
    {
        num = numIndexItems(i);//assign number to num
        cout << "------------------\n";
        cout << "index = " << i << endl;
        for(int j = 0; j < num; j++)
        {
            cout << table[i]->key << endl;
        }
        cout << "# of items = " << num << endl;
        cout << "------------------\n";
    }
    return;
}

node* HashTable:: searchItem(int key)
{
    int bucket = hashFunction(key);//find the bucket its stored in
    bool foundKey = false;
    node* ptr = table[bucket]; //pointer that points to first item in the bucket
    while(ptr->key != NULL) //scan entire list (as long as ptr points to something)
    {
        if(ptr->key == key)//seeing if the keys match
        {
            foundKey = true;//mark that we found a match
        }
        ptr = ptr->next;
    }
    if(foundKey == true)//if we kow we found the value then return the ptr val
    {
        return ptr;//ptr should be pointng to the right one
    }
    else
    {
        return NULL;
        //will need to check for NULL when we use this function... if (returnVal != NULL)... blah blah blah
    }
}

//------------------------------------------MAIN-------------------------------------------
int main()
{
    //run insert and search time tests and write info to a file
}