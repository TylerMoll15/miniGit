#include <iostream>
#include "miniGit.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>


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
    newNode->next = nullptr;
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
    head = nullptr;
}

void SLL::clipHead(){
    head = nullptr;
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

    fs::remove_all(".minigit");
    easymkdir(".minigit");
    addDLLNode();

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
    numberOfNodes++;
    newNode->commitNumber = numberOfNodes;
    newNode->headLL = nullptr;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    SLL copyLast;    

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

SLLnode* DLL::idToHeadLL(int commitNumber){
    DLLnode* curr = head;

    while(curr != nullptr && curr->commitNumber != commitNumber){
        curr = curr->next;
    }
    if(curr == nullptr){
        cout << "No commit " << commitNumber << " exists" << endl;
        return nullptr;
    }
    else{
        return curr->headLL;
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

void copy(string from, string to){
    ifstream file(from);
    ofstream newFile(to);
    string eachLine;

    if(file.fail()){
        cout << "File " << from << " not opened" << endl;
    }
    else{
        while(getline(file, eachLine)){
            newFile << eachLine;
        }
        file.close();
        newFile.close();
    }
}

bool fileEquivalence(string file1, string file2){
    vector<string> firstFileStringList;
    vector<string> secondFileStringList;
    bool equal;

    fstream file1_;
    file1_.open(file1);
    string eachLine1;

    fstream file2_;
    file2_.open(file2);
    string eachLine2;

    while(file1_ >> eachLine1){
        firstFileStringList.push_back(eachLine1);
    }

    while(file2_ >> eachLine2){
        secondFileStringList.push_back(eachLine2);
    }

    if(firstFileStringList.size() != secondFileStringList.size()){
        file1_.close();
        file2_.close();
        return false;
    }
    for(int i = 0; i < firstFileStringList.size(); i++){
        cout << (firstFileStringList[i] == secondFileStringList[i]) << endl;
        if(firstFileStringList[i] != secondFileStringList[i]){
            file1_.close();
            file2_.close();
            return false;
        }
    }
    file1_.close();
    file2_.close();
    return true;
}

//finds newest existing version of a given file
string findNewestFile(string file1){
    int versionNumber = 0;
    string newestFile = "__" + to_string(versionNumber) + "__" + file1;

    while(fs::exists(".minigit/" + newestFile)){ //finds what to change current file version to (eg if most recent __0__, this would make curr version __1__)
        versionNumber++;
        newestFile = "__" + to_string(versionNumber) + "__" + file1;
    }
    newestFile = "__" + to_string(versionNumber - 1) + "__" + file1;

    return newestFile;
}