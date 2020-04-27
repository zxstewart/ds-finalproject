#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
    LinkedList(){
    	head = nullptr;
    }
    void insert(LLNode *prev, int newKey);
    LLNode* searchList(int key);
    void printList();
};

//------------------------------------------------------------------------------------------------------------

void LinkedList::insert(LLNode* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
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

  else{

      LLNode* newNode = new LLNode;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }

// Print the keys in your list
void LinkedList::printList(){
  LLNode* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
LLNode* LinkedList::searchList(int key) {

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
}