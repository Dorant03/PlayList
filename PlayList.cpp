#include <iostream>
#include <fstream>
#include "PlayList.h"
using namespace std;

PlayList::PlayList(string _name)
{
	playlist.open(_name.append(".m3u"));
}
void PlayList::out(string info)
{
	playlist<<info.c_str();
}
