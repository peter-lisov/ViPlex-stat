#include <iostream>
#include <string>
#include "screens.h"
#include "playlist.h"

using namespace std;

Playlist *Screens::find(string plName)
{
	Playlist *pl = NULL;
	ScrItem *tmp = firstItem;
	while(tmp) {
		if(plName == tmp->playlist->getName()) pl = tmp->playlist;
		tmp = tmp->nextItem;
	}
    return pl;
}

void Screens::add(string plName, int order, string itName, int duration)
{
	Playlist *pl = find(plName);
	if(!pl) {
		pl = new Playlist(plName);
		ScrItem *tmp = new ScrItem;
		tmp->playlist = pl;
		tmp->nextItem = firstItem;
		firstItem = tmp;
	}
	pl->add(order, itName, duration);
}

void Screens::print(string plName)
{
	Playlist *pl = find(plName);
	if(!pl)
		cout << "Playlist '" << plName << "' not found" << endl;
	else {
		cout << "Playlist: " << plName << "\tDuration: " << pl->getDuration() << endl;
		pl->print();
	}
}

void Screens::print()
{
	ScrItem *tmp = firstItem;
	while(tmp) {
		cout << tmp->playlist->getDuration() << '\t' << tmp->playlist->getName() << endl;
		tmp = tmp->nextItem;
	}
}

Screens::~Screens()
{
	ScrItem *tmp;
	while(firstItem) {
		tmp = firstItem->nextItem;
		delete firstItem->playlist;
		delete firstItem;
		firstItem = tmp;
	}
}
