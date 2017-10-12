#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "PlayList.h"
#include "Functions.h"
using namespace std;

PlayList::PlayList(string _name_list, string operations)
{
	name_list=_name_list.append(".m3u");
	if( operations.find("new")==0) {   ofstream fout_list(_name_list); fout_list<<"#EXTM3U";  fout_list.close();   }
}
PlayList& PlayList::operator+(string _name_file)
{
	if(!correct_format(name_list)) return *this;
	if(_name_file.find(".mp3")<MAX_PATH)
	{
		add_song(_name_file);
	    return *this;
	}
	string path=_name_file+"\\*.mp3";
	wstring wide_string=wstring(path.begin(), path.end());
	WIN32_FIND_DATA winFileData; 
	HANDLE  hFile;
	hFile= FindFirstFile(wide_string.c_str(),&winFileData);
		if (hFile!=INVALID_HANDLE_VALUE)
	    {
			do {
            wstring _wname(&winFileData.cFileName[0]);
            string _name(_wname.begin(), _wname.end());
			path=_name_file+"\\"+_name;
			//cout<<path<<endl;
			add_song(path);
			}
			while (FindNextFile(hFile, &winFileData)!=0);
			FindClose(hFile);
		}
	return *this;
}

PlayList& PlayList::operator+=(string _name_list)
{
	_name_list.append(".m3u");
	if(!correct_format(name_list)) return *this;
	if(!correct_format(_name_list)) return *this;
	ifstream fin_list1(name_list);
	ifstream fin_list2(_name_list);
	string array_songs[100]; int N=0, i=0;
	string info;
	string songs;

	getline(fin_list1,songs);
	while(!fin_list1.eof())
	{
		getline(fin_list1,array_songs[N]);
		getline(fin_list1,array_songs[N+1]);
		N+=2;
	}
	i=N;
	getline(fin_list2,songs);
	while(!fin_list2.eof())
	{
		getline(fin_list2,info);
		getline(fin_list2,songs);
		bool oz=false;           //пісня не входить у плейліст
		for(int j=0; j<N; j++)
		{
			if(array_songs[j].substr(array_songs[j].rfind("\\")+1)==songs.substr(songs.rfind("\\")+1))
			{ 
				oz=true;         //входить 
				break;
			}
		}
		if(!oz)                  //якщо не входить то додаєм
		{
			array_songs[i]=info;
			array_songs[i+1]=songs; 
			i+=2;
		}
	}
	fin_list1.close();
	fin_list2.close();
	add_songs(array_songs, i);
	cout<<"Successfully added!"<<endl;
	return *this;
}

PlayList& PlayList::operator-=(string _name_list) 
{
	_name_list.append(".m3u");
	if(!correct_format(name_list)) return *this;
	if(!correct_format(_name_list)) return *this;
	ifstream fin_list1(name_list);
	ifstream fin_list2(_name_list);
	string array_songs[100]; int N=0;
	string info;
	string songs;

	getline(fin_list1,songs);
	while(!fin_list1.eof())
	{
		getline(fin_list1,array_songs[N]);
		getline(fin_list1,array_songs[N+1]);
		N+=2;
	}

	getline(fin_list2,songs);
	while(!fin_list2.eof())
	{
		getline(fin_list2,info);
		getline(fin_list2,songs);
		for(int j=0; j<N; j++)
		{
			if(array_songs[j].substr(array_songs[j].rfind("\\")+1)==songs.substr(songs.rfind("\\")+1))
			{ 
				array_songs[j]="\0"; array_songs[j-1]="\0"; 
			}
		}
	}
	fin_list1.close();
	fin_list2.close();
	add_songs(array_songs, N);
	cout<<"Successfully deleted!"<<endl;
	return *this;
}

void PlayList::add_song(string _name_music)
{
	tags header;
	ofstream fout_list(name_list, std::ofstream::app);
	fout_list<<"\n#EXTINF: ";
	FILE *file;
	file = fopen(_name_music.c_str(), "rb");
	fseek(file, -128, SEEK_END);
    fread(&header,sizeof(header),1,file);
	fout_list<<header.name<<" - ";
	fout_list<<header.artist<<" - ";
	fout_list<<header.year<<"\n";
	fout_list<<_name_music.c_str();
	fclose(file);
	fout_list.close();
}

void PlayList::add_songs(string _array_music[], int n)
{
	ofstream fout_list(name_list, std::ofstream::trunc); fout_list<<"#EXTM3U";
	for(int i=0; i<n; i++)
	{
		if(!_array_music[i].empty()) fout_list<<endl<<_array_music[i];
	}
	fout_list.close();
}

bool PlayList::correct_format(string _name_list)
{
	ifstream fin_list(_name_list);
	string data;
	fin_list>>data;
	fin_list.close();
	if(data!="#EXTM3U"){ cout<<_name_list<<": Invalid file format. Missing row '#EXTM3U'."<<endl; return false; }
	return true;
}

PlayList::~PlayList()
{
	
}
