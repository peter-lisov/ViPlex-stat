#include <string>
#include "playlist.h"

#ifndef SCREENS_H
#define SCREENS_H

using namespace std;

struct ScrItem {
	Playlist *playlist;
	ScrItem *nextItem;
};

class Screens {
	ScrItem *firstItem;

	Playlist *find(string plName);
public:
	Screens() {firstItem = NULL;}
	~Screens();
	void add(string plName, int order, string itName, int duration);
	void print(string plName);
	void print();
	void generateHTML();
};

#endif
