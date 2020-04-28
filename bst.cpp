#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <sstream>
#include <sstream>
using namespace std;

struct Node
{
    int key;
    Node* left ;
    Node* right;
};

class BST
{
    private:
        Node* root;
        Node* createNode(int data);
        Node* addNodeHelper(Node*, int);
        void printTreeHelper(Node*);
        //void print2DUtilHelper(Node *, int);  already have printTree function so i dont think we need this?
        Node* searchKeyHelper(Node*, int);
        void destroyNode(Node *root);

    public:
        Node* getRoot();                // Returns the root of the tree
        void addNode(int);              // function to insert a node in the tree.
        bool searchKey(int);            // function to search a data in the tree
        void printTree();               //function to print the tree
        BST();                          // default constructor
        BST(int data);                  // parameterized constructor
        ~BST();                         // destructor
        //void print2DUtil(int);
};

//---------------------------------------------------------------------------------------------------------------------------------

Node* BST:: createNode(int data)
{
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BST::BST()
{
}

BST::BST(int data)
{
    root = createNode(data);
    cout<< "New tree created with "<<data<<endl;
}

BST::~BST()//destructor
{
     destroyNode(root);
}


Node* BST::getRoot()
{
    return root;
}

void BST:: destroyNode(Node *currNode)
{
     if(currNode!=NULL)
     {
         destroyNode(currNode->left);
         destroyNode(currNode->right);

         delete currNode;
         currNode = NULL;
     }
 }

// void BST::print2DUtilHelper(Node *currNode, int space)
// {
//     if (currNode == NULL)
//     {
//         return;
//     }

//     space += COUNT; //idk what this is doing or why there's an error...

//     // Process right child first
//     print2DUtilHelper(currNode->right, space);
//     // Print current node after space
//     // count
//     printf("\n");
//     for (int i = COUNT; i < space; i++)
//     {
//         printf(" ");
//         printf("%d\n", currNode->key);
//     }
//     // Process left child
//     print2DUtilHelper(currNode->left, space);
// }

// void BST::print2DUtil( int space)
// {
//   print2DUtilHelper(root, space);
// }

Node* BST:: addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL)
    {
        return createNode(data);
    }
    else if(currNode->key < data)
    {
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data)
    {
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;
}

void BST:: addNode(int data)
{
    root = addNodeHelper(root, data);
    cout<<data<<" has been added"<<endl;
}

void BST:: printTreeHelper(Node* currNode)
{
     if(currNode)
     {
        printTreeHelper( currNode->left);
        cout << " "<< currNode->key;
        printTreeHelper( currNode->right);
     }
 }

void BST:: printTree()
{
     printTreeHelper(root);
     cout<<endl;
}

Node* BST::searchKeyHelper(Node* currNode, int data)
{
    if(currNode == NULL)
        return NULL;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

// This function will return whether a key is in the tree
bool BST::searchKey(int key)
{
    Node* tree = searchKeyHelper(root, key);
    if(tree != NULL)
    {
        return true;
    }
    cout<<"Key not present in the tree"<<endl;
    return false;
}

//------------------------------------------MAIN-------------------------------------------
int main()
{
    //run insert and search time tests and write info to a file
    BST tree;
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
    bool found;
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
            tree.addNode(testDataA[ctr]);
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
        chrono::steady_clock::time_point _start(chrono::steady_clock::now());
        for(int i = 0; i < 100; i++)
        {
            found = tree.searchKey(searcher[i]);
        }
        chrono::steady_clock::time_point _end(chrono::steady_clock::now());
        time = chrono::duration_cast<chrono::duration<float>>(_end - _start).count();
        search[spot] = (time/100);//avg
        time =0;//reset time here
        spot++;//incrementing the places in insert and search arrays
    }
    //write to a file
    cout << "collecting insert data..." << endl;
    ofstream fileOut;
    fileOut.open("treeInsertSetA.txt"); //just change this title when we run it w the different data set
    for(int i = 0; i < 400; i++)
    {
        fileOut << insert[i] << endl;
    }
    fileOut.close();
    cout << "collecting search data..." << endl;
    ofstream file2Out;
    file2Out.open("treeSearchSetA.txt");
    for(int j = 0; j < 400; j++)
    {
        file2Out << search[j] << endl;
    }
    file2Out.close();
}
