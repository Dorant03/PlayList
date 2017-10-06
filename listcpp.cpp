#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <strsafe.h>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <fstream>
#include <vfw.h>
#include "Functions.h"
#include "PlayList.h"
using namespace std;

int main()
{
	//_setmode(_fileno(stdout), _O_U16TEXT);
	wcout.imbue(locale("rus_rus.866"));//для вывода
    wcin.imbue(locale("rus_rus.866"));//для ввода
	WIN32_FIND_DATA winFileData;
	HANDLE  hFile;
	string command;
    string path;
	while(command!="exit")
	{
		getline(cin, command);
		if(command.find("cd")==0)
		{
			command=command.substr(command.find(" ")+1);
			hFile= FindFirstFile(cd(command, path).c_str(),&winFileData);
		}
		if(command.find("ls")==0)
		{
			ls(winFileData, hFile);
		}
		if(command.find("create")==9)
		{
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			playlist_create(command, winFileData, hFile);
		}
		if(command.find("folder")==13)
		{
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			playlist_add_folder(command, winFileData, hFile);
		}
		if(command.find("file")==13)
		{
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			playlist_add_file(command, winFileData, hFile);
		}
		if(command.find("help")==0)
		{
			help();
		}
	}
    return 0;
}