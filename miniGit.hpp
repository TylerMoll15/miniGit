#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#ifndef MINIGIT_H
#define MINIGIT_H

//each SLLnode pertains to a single file w/ in the commit
struct SLLnode{
    string fileName; //name of local file
    string fileVersion; //name of file in .minigit folder
    SLLnode *next;
};

//each DLLnode pertains to a single commit w/ in the repo (all files in commit)
struct DLLnode{
    int commitNumber;
    SLLnode *headLL;
    DLLnode *previous;
    DLLnode *next;
};

//essentially the entire repository
class DLL{
    private:
        DLLnode* head;
        int numberOfNodes;
        //fs::path filePath;
        string filePath;
    
    public:
        ~DLL();
        void prettyPrint();
        string idToName(int commitNumber);
        bool initialSetup();
        bool addDLLNode();
        bool removeNode(int commitNumber);
        string getLocation();
        int getNumberOfNodes();
        void addHead(int commitNumber, SLLnode* sllHead);
};

//the list of files in each commit
class SLL{
    private:
        SLLnode* head = nullptr;
        int numberOfNodes;
    
    public:
        ~SLL();
        void prettyPrint();
        bool addSLLNode(string fileName, string fileVersion);
        bool removeNode(string fileName);
        SLLnode* getHeadPointer(){return head;}
};

bool easymkdir(string filePathString);
string easyQuestion(string prompt);
void copy(string from, string to);
#endif

