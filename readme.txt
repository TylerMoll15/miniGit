Welcome to the Tyler Moll implementation of minigit! I hope you enjoy your stay


OPENING INITILIZATION:
Once the file is opened, you will be prompted will the following question:
Do you want to initialize a new repository? (y/n)

Entering "y" will delete all files in the .minigit folder in your current directory, and create a fresh .minigit folder
Entering "n" will not change the current .minigit folder, but no persistence has been encoded into this program so the old data structures will not be loaded


MAIN FUNCTIONALITY:
Select one of the 5 options:
1. Add a File to the current commit                --> Will add a given file to the current commit (and SLL) if the file exists in the current directory, and hasn't already been added
2. Remove a File from the current commit           --> Will remove a file from the current commit, if it has already been added (and SLL)
3. Commit Changes                                  --> Will save the current version of the added files in the .minigit folder, and create a new commit (the files of the past commit are not copied into the new commit)
4. Checkout a Commit                               --> Will revert the files in the current directory to that of a previous commit
5. Quit                                            --> Quits program