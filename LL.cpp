#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

struct LLNode 
{
    int key;
    LLNode* next;
};

class LinkedList
{
  private:
    LLNode *head;

  public:
    LinkedList()
    {
    	head = nullptr;
    }
    void insert(LLNode *prev, int newKey);
    LLNode* searchList(int key);
    void printList();
    LLNode* findHead();
};

//------------------------------------------------------------------------------------------------------------

void LinkedList::insert(LLNode* prev, int newKey)
{
  //Check if head is Null i.e list is empty
  if(head == NULL)
  {
    head = new LLNode;
    head->key = newKey;
    head->next = NULL;
  }
  // if list is not empty, look for prev and append our LLnode there
  else if(prev == NULL)
  {
      LLNode* newNode = new LLNode;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }
  else
  {
      LLNode* newNode = new LLNode;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;
    }
  }
LLNode* LinkedList:: findHead()
{
    return head;
}
// Print the keys in your list
void LinkedList::printList()
{
  LLNode* temp = head;
  while(temp->next != NULL)
  {
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }
  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
LLNode* LinkedList::searchList(int key)
{
    LLNode* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}

//------------------------------------------MAIN-------------------------------------------
int main()
{
    //run insert and search time tests and write info to a file
    LinkedList LList;
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
    LLNode* found;
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
       LLNode* prev = LList.findHead();
       int ah = 0;
        chrono::steady_clock::time_point _start(chrono::steady_clock::now());
        for(int i = 0; i < 100; i++)
        {
            LList.insert(prev, testDataA[ctr]);
            if(ah == 0)
            {
                prev = LList.findHead();
                ah++;
            }
            else
            {
                prev = prev->next;
            }
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
            found = LList.searchList(searcher[i]);
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
    fileOut.open("LListInsertSetA.txt"); //just change this title when we run it w the different data set
    for(int i = 0; i < 400; i++)
    {
        fileOut << insert[i] << endl;
    }
    fileOut.close();
    cout << "collecting search data..." << endl;
    ofstream file2Out;
    file2Out.open("LListSearchSetA.txt");
    for(int j = 0; j < 400; j++)
    {
        file2Out << search[j] << endl;
    }
    file2Out.close();
}

