#include <iostream>
#include <fstream>
#include "PlayList.h"
using namespace std;

PlayList::PlayList(string _name)
{
	playlist.open(_name.append(".m3u"));
}


PlayList::PlayList(string _name, int n)
{
	playlist.open(_name.append(".m3u"), std::ofstream::app);
}

void PlayList::out(string info)
{
	playlist<<info.c_str();
}

PlayList::~PlayList()
{
	playlist.close();
}
