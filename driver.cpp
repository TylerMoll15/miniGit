#include <iostream>
#include "miniGit.hpp"
#include <string>
#include "fileManagement.hpp"


using namespace std;

void choiceSelection(int& choice){
    string choiceLine;
    int choiceNumber = 7;
    bool loopRunning = true;

    while(loopRunning){
        cout << "Select one of the four options: " << endl;
        cout << "1. Add a File to the current commit" << endl;
        cout << "2. Remove a File from the current commit" << endl;
        cout << "3. Commit Changes" << endl;
        cout << "4. Checkout a Commit " << endl;
        cout << "5. Initialize a New Repository" << endl;
        cout << "6. Select a Repository" << endl;
        cout << "7. Quit" << endl;
        cout << "#> ";

        getline(cin, choiceLine);
        if(choiceLine.length() > 1 || !isdigit(choiceLine[0]) || stoi(choiceLine) > choiceNumber|| stoi(choiceLine) < 1){
            cout << endl;
            cout << "## Please choose an option 1-7 ##" << endl;
            cout << endl;
        }
        else{
            choice = stoi(choiceLine);
            loopRunning = false;
        }
    }
}


int main(){
    bool isRunning = true;
    const char* repoName;
    string currentRepo = "No Repository Selected";


    while(isRunning){
        int choice = 0;
        string relevantString;
        cout << endl;
        cout << ">> Current Repository: " << currentRepo << " <<"<< endl;
        choiceSelection(choice);

        switch(choice){
            case 1: //add file
                cout << "Adding file..." << endl;
                break;
            case 2: //remove file
                cout << "Removing a file..." << endl;
                break;
            case 3: //commit
                cout << "Commiting changes..." << endl;
                break;
            case 4: //checkout
                cout << "Checking out a commit..." << endl;
                break;
            case 5: //init
                cout << "What do you want to name your repository?" << endl;
                getline(cin, relevantString);
                currentRepo = relevantString;
                repoName = relevantString.c_str();
                easymkdir(repoName);
                break;
            case 6: //selecting a repo
                cout << "Selecting a repository..." << endl;
                break;
            case 7: //quit
                cout << "Bye!" << endl;
                isRunning = false;
                break;
        }
    }

    SLL testLL;
    testLL.addSLLNode("file1.txt", "file1v1.txt");
    testLL.addSLLNode("fiel.txt", "file1v1.txt");
    testLL.prettyPrint();
}