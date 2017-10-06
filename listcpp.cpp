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
	wcout.imbue(locale("rus_rus.866"));//äëÿ âûâîäà
    wcin.imbue(locale("rus_rus.866"));//äëÿ ââîäà
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
		if(command.find("playlist create")==0)
		{
			command=command.substr(command.find(" ")+1);
			command=command.substr(command.find(" ")+1);
			playlist_create(command, winFileData, hFile);
			/*fplaylist<<"#EXTINF: ";
			FILE *file1;
	        file1 = fopen("D:\\myzuka\\Nickelback_-__Photograph_.mp3", "rb");
            tags header;
	        fseek(file1, -128, SEEK_END); 
			fread(&header,sizeof(header),1,file1);
			fplaylist<<header.name<<" - ";
			fplaylist<<header.artist<<" - ";
			fplaylist<<header.year<<endl;
			fplaylist<<"D:\\myzuka\\Nickelback_-__Photograph_.mp3"<<endl;
			fclose(file1);
		}*/
		}
	}
	
    return 0;
	
}
