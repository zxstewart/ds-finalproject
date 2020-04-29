#include <string>
#include <list> //idk if we need this but included just in case
#include <iostream>
#include <chrono>
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
    bool isEmpty(int index); //check if the table is empty
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
        //table[i]->key = NULL;
        table[i]->next = NULL;
    }
}

bool HashTable::isEmpty(int index)
{
    int sum = 0;
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i]->key)//!= NULL
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
     if(isEmpty(index))//if its empty agh here 
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
     return return_Val;
 }

int HashTable::numIndexItems(int index)
{
    int count = 0;
    if(table[index]->key)// != NULL
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
    while((ptr->key) && (ptr!= NULL)) // != NULL scan entire list (as long as ptr points to something)
    {
        if(ptr->key == key)//seeing if the keys match
        {
            foundKey = true;//mark that we found a match
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
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

    ifstream myFile("dataSetA.csv");
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
    node* find;
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
            find = HTable.searchItem(searcher[i]);
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
    fileOut.open("hashChainInsertSetA.txt"); //just change this title when we run it w the different data set
    for(int i = 0; i < 400; i++)
    {
        fileOut << insert[i] << endl;
    }
    fileOut.close();
    cout << "collecting search data..." << endl;
    ofstream file2Out;
    file2Out.open("hashChainSearchSetA.txt");
    for(int j = 0; j < 400; j++)
    {
        file2Out << search[j] << endl;
    }
    file2Out.close();
}
