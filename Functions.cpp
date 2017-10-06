#include <iostream>
#include <string>
#include <windows.h>
#include <locale>
#include <fstream>
#include "Functions.h"
#include "PlayList.h"

using namespace std;

wstring cd(string command, string &path)
{
	if(!path.empty() && command.find("C:") && command.find("D:"))
	{
		path.pop_back();
		cout<<path<<endl;
		if(command.find("..")==0)
		{
			path.pop_back();
			path=path.substr(0, path.rfind("\\"));
		}
		else
		{
			path+=command;
		}
	}
	else
	{
		path=command;
	}
	path+="\\";
	
	cout<<path<<endl;
	path.push_back('*');
	return wstring(path.begin(), path.end());
}

void ls(WIN32_FIND_DATA winFileData, HANDLE  hFile)
{
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hFile,&winFileData)!=0) wcout<<winFileData.cFileName<<endl; 
		FindClose(hFile);
	}
}

void playlist_create(string command, WIN32_FIND_DATA &winFileData, HANDLE  &hFile)
{
	string name_list=command.substr(0, command.find(" "));
	//command=command.substr(command.find(" ")+1);
	PlayList fplaylist(name_list);
	fplaylist.out("#EXTM3U\n");
	if(command.find(" ")<MAX_PATH)
	{
		string path=command.substr(command.find(" ")+1).append("\\*.mp3");
		wstring wide_string=wstring(path.begin(), path.end());
	    hFile= FindFirstFile(wide_string.c_str(),&winFileData);
		if (hFile!=INVALID_HANDLE_VALUE)
	    {
			tags header;
		     //wcout<<winFileData.cFileName<<endl; 
			do {
			fplaylist.out("#EXTINF: ");
			FILE *file1;
            wstring test(&winFileData.cFileName[0]);
            string test2(test.begin(), test.end());
			path=command.substr(command.find(" ")+1).append("\\")+test2;
			cout<<path<<endl;
	        file1 = fopen(path.c_str(), "rb");
	        fseek(file1, -128, SEEK_END); 
			fread(&header,sizeof(header),1,file1);
			fplaylist.out(header.name); fplaylist.out(" - ");
			fplaylist.out(header.artist); fplaylist.out(" - ");
			fplaylist.out(header.year); fplaylist.out("\n");
			fplaylist.out(path.c_str()); fplaylist.out("\n");
			fclose(file1);
			}
			while (FindNextFile(hFile, &winFileData)!=0);
			FindClose(hFile);
		}
	}
	cout<<"Was created!"<<endl;
}

void playlist_add_folder(string command, WIN32_FIND_DATA &winFileData, HANDLE  &hFile)
{
	string name_list=command.substr(0, command.find(" "));
	string path=command.substr(command.find(" ")+1).append("\\*.mp3");
	PlayList fplaylist(name_list, 0);
	wstring wide_string=wstring(path.begin(), path.end());
	hFile= FindFirstFile(wide_string.c_str(),&winFileData);
		if (hFile!=INVALID_HANDLE_VALUE)
	    {
			tags header;
		     //wcout<<winFileData.cFileName<<endl; 
			do {
			fplaylist.out("#EXTINF: ");
			FILE *file1;
            wstring test(&winFileData.cFileName[0]);
            string test2(test.begin(), test.end());
			path=command.substr(command.find(" ")+1).append("\\")+test2;
			cout<<path<<endl;
	        file1 = fopen(path.c_str(), "rb");
	        fseek(file1, -128, SEEK_END); 
			fread(&header,sizeof(header),1,file1);
			fplaylist.out(header.name); fplaylist.out(" - ");
			fplaylist.out(header.artist); fplaylist.out(" - ");
			fplaylist.out(header.year); fplaylist.out("\n");
			fplaylist.out(path.c_str()); fplaylist.out("\n");
			fclose(file1);
			}
			while (FindNextFile(hFile, &winFileData)!=0);
			FindClose(hFile);
		}
	cout<<"Was added!"<<endl;
}

void playlist_add_file(string command, WIN32_FIND_DATA &winFileData, HANDLE  &hFile)
{
	string name_list=command.substr(0, command.find(" "));
	string path=command.substr(command.find(" ")+1).append(".mp3");
	PlayList fplaylist(name_list, 0);
    tags header;
    FILE *file1;
	cout<<path<<endl;
	file1 = fopen(path.c_str(), "rb");
	fplaylist.out("#EXTINF: ");
	fseek(file1, -128, SEEK_END);
    fread(&header,sizeof(header),1,file1);
	fplaylist.out(header.name); fplaylist.out(" - ");
    fplaylist.out(header.artist); fplaylist.out(" - ");
	fplaylist.out(header.year); fplaylist.out("\n");
	fplaylist.out(path.c_str()); fplaylist.out("\n");
	fclose(file1);
	cout<<"Was added!"<<endl;
}

void playlist_add_playlist(string command, WIN32_FIND_DATA &winFileData, HANDLE  &hFile)
{
	string name_list=command.substr(0, command.find(" "));
	string name_list2=command.substr(command.find(" ")+1);
	PlayList fplaylist(name_list, 0);
	PlayList fplaylist1(name_list);
}

void help()
{
	cout<<"Commanded:"<<endl;
	cout<<"cd <name folder> or <name Disk(:)> or <..>"<<endl;
	cout<<"ls - print name folder and file"<<endl;
	cout<<"playlist create <name playlist> <name folder>"<<endl;
	cout<<"playlist add <folder or file or playlist> <name>"<<endl;
}
void exit()
{
	cout<<"END"<<endl;
}
