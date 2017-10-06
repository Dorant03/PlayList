#include <iostream>
#include <string>
#include <windows.h>
#include <locale>
#include <fstream>

using namespace std;

wstring cd(string command, string &path);
void ls(WIN32_FIND_DATA winFileData, HANDLE  hFile);
void playlist_create(string command, WIN32_FIND_DATA &winFileData, HANDLE  &hFile);
void exit();
