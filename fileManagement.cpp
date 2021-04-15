// C++ program to create a directory in Linux
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
  
int easymkdir(const char* relativePath)
{
    // Creating a directory
    if (mkdir(relativePath, 0777) == -1)
        cerr << "Error :  " << strerror(errno) << endl;
  
    else
        cout << "Directory created at " << relativePath << endl;
}