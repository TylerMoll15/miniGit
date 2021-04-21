#include <iostream>
#include "miniGit.hpp"
#include <string>
#include <fstream>
#include <filesystem>


using namespace std;
namespace fs = std::filesystem;

void SLL::prettyPrint(){
    SLLnode* curr = head;

    if(head == nullptr){
        cout << "nothing to print in this linked list!" << endl;
        return;
    }

    cout << "Linked List contents: " << endl;
    while(curr != nullptr){
        cout << "Filename: " << curr->fileName << endl;
        cout << "File Version: " << curr->fileVersion << endl << endl;
        curr = curr->next;
    }
}

bool SLL::addSLLNode(string filename_, string fileVersion_){
    SLLnode* newNode = new SLLnode;
    newNode->fileName = filename_;
    newNode->fileVersion = fileVersion_;
    bool addSuccess = false;

    if(head == nullptr){ //head is empty
        head = newNode;
        numberOfNodes++;
        addSuccess = true;
        return addSuccess;
    }

    //head is not empty
    SLLnode* curr = head;
    SLLnode* prev = nullptr;
    while(curr != nullptr){
        prev = curr;
        curr = curr->next;
    }
    prev->next = newNode;
    addSuccess = true;
    return addSuccess;
}

bool SLL::removeNode(string fileName){
    SLLnode* curr = head;
    SLLnode* prev = nullptr;

    while(curr != nullptr && curr->fileName != fileName){ //iterates through SLL
        prev = curr;
        curr = curr->next;
    }

    if(curr == nullptr){ //file node not found
        cout << fileName << " is not in the linked list" << endl;
        return false;
    }

    if(curr == head){ //checks if head is node to be deleted
        head = curr->next;
        delete curr;
        return true;
    }

    if(curr->next == nullptr){ //node is at the end of the list
        prev->next = nullptr;
        delete curr;
        return true;
    }
    else if(curr->next != nullptr){ //node is in the middle of the list
        prev->next = curr->next;
        delete curr;
        return true;
    }
} 

SLL::~SLL(){
    SLLnode* curr = head;
    SLLnode* prev = nullptr;

    while(curr != nullptr){
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}


//=========================================
// DLL (repo) functions
bool DLL::initialSetup(){
    DLLnode* firstNode = new DLLnode;
    firstNode->commitNumber = 0;
    firstNode->headLL = nullptr;
    firstNode->previous = nullptr;
    firstNode->next = nullptr;
    head = firstNode;
    numberOfNodes = 0;
    numberOfNodes++;

    fs::remove_all(".minigit");
    easymkdir(".minigit");

    return true;
}

string DLL::getLocation(){
    return filePath;
}

//WEIRD ERROR W/ DESTRUCTOR
DLL::~DLL(){
    // DLLnode* curr = head;
    // DLLnode* prev = nullptr;

    // if(numberOfNodes > 1){ //multiple commits in the DLL
    //     while(curr != nullptr){
    //         prev = curr;
    //         curr = curr->next;
    //         delete prev;
    //     }
    // }
    // else if(numberOfNodes == 1){ //one or fewer nodes in the DLL
    //     delete head;
    // }
}

int DLL::getNumberOfNodes(){
    return numberOfNodes;
}

bool DLL::addDLLNode(){
    DLLnode* newNode = new DLLnode;
    newNode->commitNumber = numberOfNodes;
    newNode->headLL = nullptr;
    numberOfNodes++;

    
    if(head == nullptr){ //head is empty
        head = newNode;
        return true;
    }

    //head is not empty
    DLLnode* curr = head;
    DLLnode* prev = nullptr;
    while(curr->next != nullptr){
        prev = curr;
        curr = curr->next;
    }
    curr->next = newNode;
    curr->previous = prev;
    newNode->previous = curr;

    return true;
}

void DLL::addHead(int commitNumber, SLLnode* sllHead){
    DLLnode* curr = head;
    DLLnode* prev = nullptr;

    while(curr != nullptr && curr->commitNumber != commitNumber){ //iterates while relevant node hasn't been found, or curr is not at the end of list
        prev = curr;
        curr = curr->next;
    }

    if(curr == nullptr){ //relevant commit doesn't exist
        cout << "Relevant commit " << commitNumber << " does not exist" << endl;
        return;
    }
    else{ //if commit exists
        curr->headLL = sllHead;
        cout << "File head " << sllHead->fileName << " was added to commit " << curr->commitNumber << endl << endl;
        return;
    }
}

void DLL::prettyPrint(){
    DLLnode* curr = head;
    
    while(curr != nullptr){
        if(curr == head){
            cout << "Head " << endl << "commit number -> " << curr->commitNumber << endl << "File List head Pointer -> " << curr->headLL << endl 
            << "Next Commit in chain -> " << curr->next << endl << "Previous commit in chain -> " << curr->previous << endl << endl;
        }
        else{
            cout << "Commit " << curr->commitNumber << endl << "commit number -> " << curr->commitNumber << endl << "File List head Pointer -> " << curr->headLL << endl 
            << "Next Commit in chain -> " << curr->next << endl << "Previous commit in chain -> " << curr->previous << endl << endl;
        }
        curr = curr->next;
    }
}
  
//==========================================
// General useful functions
bool easymkdir(string relativePathString){
    return fs::create_directory(relativePathString);
}

string easyQuestion(string prompt){
    string answer;
    cout << prompt << endl;
    cout << "#> ";
    getline(cin, answer);
    return answer;
}