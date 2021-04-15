#include <iostream>
#include <vector>
#ifndef MINIGIT_H
#define MINIGIT_H

using namespace std;

//each SLLnode pertains to a single file w/ in the commit
struct SLLnode{
    string fileName; //name of local file
    string fileVersion; //name of file in .minigit folder
    SLLnode *next;
};

//each DLLnode pertains to a single commit w/ in the repo (all files in commit)
struct DLLnode{
    int commitNumber;
    SLLnode *head;
    DLLnode *previous;
    DLLnode *next;
};

//essentially the entire repository
class DLL{
    private:
        DLL* head;
        int numberOfNodes;
    
    public:
        void prettyPrint();
        string idToName(int commitNumber);
        bool addDLLNode(SLLnode* head);
        bool removeNode(int commitNumber);
};

//the list of files in each commit
class SLL{
    private:
        SLLnode* head = nullptr;
        int numberOfNodes;
    
    public:
        void prettyPrint();
        bool addSLLNode(string fileName, string fileVersion);
        bool removeNode(string fileName);
        
};

#endif
