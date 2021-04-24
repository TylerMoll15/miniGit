#include <iostream>
#include "miniGit.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

void choiceSelection(int& choice){
    string choiceLine;
    int choiceNumber = 6;
    bool loopRunning = true;

    while(loopRunning){
        cout << "Select one of the 5 options: " << endl;
        cout << "1. Add a File to the current commit" << endl;
        cout << "2. Remove a File from the current commit" << endl;
        cout << "3. Commit Changes" << endl;
        cout << "4. Checkout a Commit " << endl;
        cout << "5. Quit" << endl;
        cout << "#> ";

        getline(cin, choiceLine);
        if(choiceLine.length() > 1 || !isdigit(choiceLine[0]) || stoi(choiceLine) > choiceNumber|| stoi(choiceLine) < 1){
            cout << endl;
            cout << "## Please choose an option 1-6 ##" << endl;
            cout << endl;
        }
        else{
            choice = stoi(choiceLine);
            loopRunning = false;
        }
    }
}


int main(){
    vector<string> fileList;
    DLL newRepo;
    SLL newRepoFileList;
    bool isRunning = true;
    SLLnode* curr;
    ofstream fileVersion;
    ofstream currentFile;
    ifstream versionFile;
    string eachLine = "";

    cout << "Do you want to initialize a new repository? (y/n)" << endl;
    
    string initAnswer;
    bool validAnswer = false;
    while(!validAnswer){
        initAnswer = "";
        cout << "#> ";
        getline(cin, initAnswer);

        if(initAnswer == "y"){
            newRepo.initialSetup();
            validAnswer = true;
        }
        else if(initAnswer == "n"){
            validAnswer = true;
        }
        else{
            cout << "Enter a valid answer" << endl;
        }
        
    }




    while(isRunning){
        bool noError = false;
        bool addDuplicate = false;
        bool valid = false;
        int choice = 0;
        string relevantString;
        string newestFile;
        choiceSelection(choice);

        switch(choice){
            case 1: //add file
                while(!noError){
                    addDuplicate = false;
                    relevantString = easyQuestion("What file do you want to add? (enter relative file path)");

                    SLLnode* dupCheck = newRepoFileList.getHeadPointer();
                    while(dupCheck != nullptr && dupCheck->fileName != relevantString){ //iterates through current added file list, stops on duplicate or end of LL
                        dupCheck = dupCheck->next;
                    }

                    if(dupCheck != nullptr){
                        addDuplicate = true;
                    }

                    if(!fs::exists(relevantString)){
                        cout << endl << endl << "File does not exist. Enter a valid File" << endl;
                        noError = false;
                    }
                    else if(addDuplicate){
                        cout << endl << "File has already been added. Enter a valid file" << endl;
                    }
                    else{
                        noError = true;
                        int fileVersion = 0;

                        if(!fileEquivalence(".minigit/" + findNewestFile(relevantString), relevantString) || !fs::exists(".minigit/__" + to_string(0) + "__" + relevantString)){
                            newRepoFileList.addSLLNode(relevantString, "__" + to_string(fileVersion) + "__" + relevantString);
                        }
                        cout << endl;
                    }
                }
                break;
            case 2: //remove file
                while(!valid){
                    valid = false;
                    relevantString = easyQuestion("Which file would you like to remove?");

                    SLLnode* curr = newRepoFileList.getHeadPointer();
                    while(curr != nullptr && curr->fileName != relevantString){
                        curr = curr->next;
                    }

                    if(curr == nullptr){
                        cout << endl << "File does not exist in added files, enter a valid file name" << endl << endl;
                        valid = false;
                    }
                    else if(curr != nullptr && curr->fileName == relevantString){
                        valid = true;
                        newRepoFileList.removeNode(curr->fileName);
                    }
                    else{
                        cout << "Something weird happened..." << endl;
                    }
                }   
                
                break;
            case 3: //commit
                curr = newRepoFileList.getHeadPointer();

                if(curr != nullptr){
                    newRepo.addDLLNode();
                    newRepo.addHead(newRepo.getNumberOfNodes(), newRepoFileList.getHeadPointer());
                    while(curr != nullptr){
                        if(fs::exists(".minigit/" + curr->fileVersion)){ //file exists in repository
                            cout << "File Exists!" << endl;
                            
                            int versionNumber = 0;
                            while(fs::exists(".minigit/" + curr->fileVersion)){ //finds what to change current file version to (eg if most recent __0__, this would make curr version __1__)
                                versionNumber++;
                                curr->fileVersion = "__" + to_string(versionNumber) + "__" + curr->fileName;
                            }

                            newestFile = "__" + to_string(versionNumber - 1) + "__" + curr->fileName;
                            
                            copy(curr->fileName, ".minigit/" + curr->fileVersion);
                        }
                        else{ //file version doesn't exist in repository
                            cout << "File doesn't exist, copying over" << endl;
                            copy(curr->fileName, ".minigit/" + curr->fileVersion);
                        }
                        curr = curr->next;
                    }
                    newRepoFileList.clipHead();
                }
                else{
                    cout << endl << endl << "Nothing to commit!" << endl << endl;
                }
                
                
                break;
            case 4: //checkout
                {
                    relevantString = easyQuestion("Enter a commit number");

                    DLLnode* curr = newRepo.getHeadPointer();

                    while(curr != nullptr && curr->commitNumber != stoi(relevantString)){
                        curr = curr->next;
                    }

                    if(curr == nullptr){
                        cout << "Commit doesn't exist" << endl;
                    }
                    else{
                        SLLnode* sllcurr = curr->headLL;
                        while(sllcurr != nullptr){

                            // fs::remove(sllcurr->fileName);
                            // copy(".minigit/" + sllcurr->fileVersion, sllcurr->fileName);

                            versionFile.close();
                            versionFile.open(".minigit/" + sllcurr->fileVersion);
                            currentFile.open(sllcurr->fileName);
                            eachLine = "";
                            

                            while(getline(versionFile, eachLine)){
                                currentFile << eachLine;
                            }
                            currentFile.close();
                            sllcurr = sllcurr->next;
                        }
                    }
                }
                break;
            case 5: //quit
                cout << "Bye!" << endl;
                isRunning = false;
                break;
        }
    }

    // DLL firstRepo;
    // SLL firstFileList;


    // firstRepo.initialSetup();
    // firstRepo.addDLLNode();
    // firstRepo.addDLLNode();

    // firstFileList.addSLLNode("Fruit.txt", "0000");
    // firstFileList.addSLLNode("Grapes.txt", "0000");
    // firstFileList.addSLLNode("Strawberries.txt", "0000");

    // firstRepo.addHead(2, firstFileList.getHeadPointer());


    // firstFileList.prettyPrint();

    // cout << endl << endl << endl;

    // firstFileList.removeNode("Strawberries.txt");
    // firstFileList.removeNode("Fruit.txt");
    // firstFileList.removeNode("Grapesggggg.txt");

    // firstFileList.prettyPrint();
    //firstRepo.prettyPrint();
}

///WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO