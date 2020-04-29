#include <string>
#include <list> //idk if we need this but included just in case
#include <iostream>
#include <chrono>
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
    node* temp = new node;
    temp->key = key;

    int idx = hashFunction(key);
    int i = 0;
    
    if(table[idx] == NULL)
    {
        tableSize++;
        table[idx] = temp;
        added = true;
    }
    while(table[idx] != NULL && table[idx]->key != key && added == false)
    {
        colNum++;   
        i++;
        idx = idx + (i*i);  //this is the quadratic probing thing...
        idx %= capacity;
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
    int idx = hashFunction(key);
    bool foundKey = false;

    while(table[idx] != NULL)
    {
        if(table[idx]->key == key)
        {
            return table[idx];
            foundKey = true;
            idx++;
            idx %= capacity;
        }
        if(idx++ >= capacity)
        {
            //circle back to beginning of table array
            idx = 0;
        }
        if(!foundKey)
        {
            return NULL;
        }
    }
}

int HashTable::getNumOfCollision()
{
    return colNum;
}

//------------------------------------------MAIN-------------------------------------------
int main()
{
    //run insert and search time tests and write info to a file
    HashTable HTable;
    int testDataA[40000];
    int testDataB[40000];
    float insert[400];
    float search[400];

    ifstream myFile("dataSetB.csv");
        if(!myFile.is_open())
        {
            cout << "file failed to open" << endl;
            return 0;
        }
    string line; 
    string myString;
    float temp;
    int count = 0;
    double time;
    bool add;
    node* idk;
    while(getline(myFile, line))
    {
        stringstream ss(line);
        while(getline(ss, myString, ','))
        {
            temp = stoi(myString);
            testDataA[count] = temp;
            count++;
        }
    }
    myFile.close();
    int ctr=0; //keeps track of the num
    int spot = 0;//keep track of where in insert and search we are
    //add data should be in the testData array now 
    while(spot < 400)//this should only do testDataA
   { 
        chrono::steady_clock::time_point _start(chrono::steady_clock::now());
        for(int i = 0; i < 100; i++)
        {
            add = HTable.insertItem(testDataA[ctr]);
            ctr++;
        }
        chrono::steady_clock::time_point _end(chrono::steady_clock::now());
        time = chrono::duration_cast<chrono::duration<float>>(_end - _start).count();
        insert[spot] = (time/100);//recording average insert time 
        //reset time here
        time =0;

        int searcher[100];//array to hold random values
        for(int i =0; i < 100; i++)//putting in random values
        {
            searcher[i] = (rand()%ctr);// range 0 to 99... then increase by 100 w each search
        }
        chrono::steady_clock::time_point _start2(chrono::steady_clock::now());
        for(int i = 0; i < 100; i++)
        {
            idk = HTable.searchItem(searcher[i]);
        }
        chrono::steady_clock::time_point _end2(chrono::steady_clock::now());
        time = chrono::duration_cast<chrono::duration<float>>(_end2 - _start2).count();
        search[spot] = (time/100);//avg
        time =0;//reset time here
        spot++;//incrementing the places in insert and search arrays
    }
    //write to a file
    cout << "collecting insert data..." << endl;
    ofstream fileOut;
    fileOut.open("hashQuadInsertSetB.txt"); //just change this title when we run it w the different data set
    for(int i = 0; i < 400; i++)
    {
        fileOut << insert[i] << endl;
    }
    fileOut.close();
    cout << "collecting search data..." << endl;
    ofstream file2Out;
    file2Out.open("hashQuadSearchSetB.txt");
    for(int j = 0; j < 400; j++)
    {
        file2Out << search[j] << endl;
    }
    file2Out.close();
}
