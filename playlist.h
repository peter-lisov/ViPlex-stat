#include <string>

#ifndef PLAYLIST_H
#define PLAYLIST_H

using namespace std;

struct PlaylistItem {
	int order;
	string name;
	int duration;
	PlaylistItem *nextItem;
};

class Playlist {
	string name;
	int duration;
	int count;
	PlaylistItem *firstItem;
public:
	Playlist(string pName);
	~Playlist();
	string getName() {return name;}
	int getDuration() {return duration;}
	void add(int iOrder, string iName, int iDuration);
	void print();
};

#endif
