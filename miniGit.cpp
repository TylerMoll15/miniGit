#include <iostream>
#include "miniGit.hpp"
#include <string>


using namespace std;

void SLL::prettyPrint(){
    SLLnode* curr = head;

    if(head == nullptr){
        cout << "nothing to print in this linked list!" << endl;
        return;
    }

    cout << "Linked List contents: " << endl;
    while(curr != NULL){
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
