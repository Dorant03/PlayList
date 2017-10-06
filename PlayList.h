#include <fstream>
using namespace std;

struct tags
{
char tag[3];
char name[30];
char artist[30];
char album[30];
char year[4];
char comment[30];
char byte;
char track;
char style;
};

class PlayList
{
private:
	ofstream playlist;
public:
	PlayList(string _name);
	void out(string info);
};