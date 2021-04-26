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
            cout << "## Please choose an option 1-5 ##" << endl;
            cout << endl;
        }
        else{
            choice = stoi(choiceLine);
            loopRunning = false;
        }
    }
}




int main(){
    DLL newRepo;
    SLL newRepoFileList;
    bool isRunning = true;
    bool inCheckout = false;
    bool freshCommit = false;
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
                if(!inCheckout){
                    while(!noError && relevantString != "q"){
                        addDuplicate = false;
                        relevantString = easyQuestion("What file do you want to add? (enter relative file path or 'q' to go to the menu)");

                        SLLnode* dupCheck = newRepoFileList.getHeadPointer();
                        while(dupCheck != nullptr && dupCheck->fileName != relevantString){ //iterates through current added file list, stops on duplicate or end of LL
                            dupCheck = dupCheck->next;
                        }

                        if(dupCheck != nullptr){
                            addDuplicate = true;
                        }

                        if(!fs::exists(relevantString) && relevantString != "q"){
                            cout << endl << endl << "File does not exist. Enter a valid File" << endl;
                            noError = false;
                        }
                        else if(addDuplicate){
                            cout << endl << "File has already been added. Enter a valid file" << endl;
                        }
                        else{
                            noError = true;
                            int fileVersion = 0;
                            
                            if(relevantString == "q"){

                            }
                            else if(!fs::exists(".minigit/__" + to_string(0) + "__" + relevantString) || !fileEquivalence(".minigit/" + findNewestFile(relevantString), relevantString)){
                                newRepoFileList.addSLLNode(relevantString, "__" + to_string(fileVersion) + "__" + relevantString);
                            }
                            else{
                                cout << endl << endl << "File not added, no changes since most recent version" << endl << endl;
                            }
                            cout << endl;
                        }
                    }
                }
                else{
                    cout << endl << endl << "You're in an earlier commit, you can't change the past!" << endl << endl; 
                }
                break;
            case 2: //remove file
                if(!inCheckout){
                    while(!valid && relevantString != "q"){
                        valid = false;
                        relevantString = easyQuestion("Which file would you like to remove?");

                        SLLnode* curr = newRepoFileList.getHeadPointer();
                        while(curr != nullptr && curr->fileName != relevantString){
                            curr = curr->next;
                        }

                        if(curr == nullptr){
                            cout << endl << "File does not exist in added files, enter a valid file name (or 'q' to go back to the menu)" << endl << endl;
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
                }
                else{
                    cout << endl << endl << "You're in an earlier commit, you can't change the past!" << endl << endl; 
                }   
                break;
            case 3: //commit
                if(!inCheckout){
                    curr = newRepoFileList.getHeadPointer();
                    if(curr != nullptr){
                        newRepo.addDLLNode();
                        newRepo.addHead(newRepo.getNumberOfNodes(), newRepoFileList.getHeadPointer());
                        while(curr != nullptr){
                            if(fs::exists(".minigit/" + curr->fileVersion)){ //file exists in repository                            
                                int versionNumber = 0;
                                while(fs::exists(".minigit/" + curr->fileVersion)){ //finds what to change current file version to (eg if most recent __0__, this would make curr version __1__)
                                    versionNumber++;
                                    curr->fileVersion = "__" + to_string(versionNumber) + "__" + curr->fileName;
                                }

                                newestFile = "__" + to_string(versionNumber - 1) + "__" + curr->fileName;
                                
                                copy(curr->fileName, ".minigit/" + curr->fileVersion);
                            }
                            else{ //file version doesn't exist in repository
                                copy(curr->fileName, ".minigit/" + curr->fileVersion);
                            }
                            curr = curr->next;
                        }
                        newRepoFileList.clipHead();
                        freshCommit = true;
                    }
                    else{
                        cout << endl << endl << "Nothing to commit!" << endl << endl;
                    }
                }
                else{
                    cout << endl << endl << "You're in an earlier commit, you can't change the past!" << endl << endl; 
                }
                break;
            case 4: //checkout
                {
                    relevantString = easyQuestion("Enter a commit number");

                    DLLnode* curr = newRepo.getHeadPointer();

                    while(curr != nullptr && curr->commitNumber != stoi(relevantString) + 1){ //grabs / decides whether user inputted commit exists
                        curr = curr->next;
                    }

                    if(relevantString == "0"){
                        cout << endl << endl << "Commit doesn't exist" << endl << endl;
                    }

                    string warnAnswer = "y";
                    if(!inCheckout && curr != nullptr && relevantString != "0"){
                        warnAnswer = easyQuestion("Any uncommitted changes will be destroyed, are you sure you want to continue? (any answer besides 'y' will cancel the checkout)");
                    }

                    if(curr == nullptr){
                        cout << endl << endl << "Commit doesn't exist" << endl << endl;
                    }
                    else if(warnAnswer == "y"){
                        SLLnode* sllcurr = curr->headLL;
                        while(sllcurr != nullptr){
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
                        if(relevantString == to_string(newRepo.getNumberOfNodes() - 1)){
                            inCheckout = false;
                        }
                        else if(relevantString != to_string(newRepo.getNumberOfNodes())){
                            inCheckout = true;
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
}