// C++ program to create a directory in Linux
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

#ifndef FILEMANAGEMENT
#define FILEMANAGEMENT
  
int easymkdir(const char* filePath);
#endif