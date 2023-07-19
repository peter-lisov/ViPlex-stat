#include <iostream>
#include <fstream>
#include <string>
#include "playlist.h"

using namespace std;

Playlist::Playlist(string pName)
{
	name = pName;
	duration = 0;
	count = 0;
	firstItem = NULL;
}

void Playlist::add(int iOrder, string iName, int iDuration)
{
	PlaylistItem *newItem = new PlaylistItem();
	newItem->order = iOrder;
	newItem->name = iName;
	newItem->duration = iDuration;
	newItem->nextItem = firstItem;
	firstItem = newItem;
	count++;
	duration += iDuration;
}

void Playlist::print()
{
	PlaylistItem *item = firstItem;
        while(item) {
		cout << item->order << '\t' << item->duration << '\t' << item->name << endl;
		item = item->nextItem;
	}
}

void Playlist::print(ofstream &file)
{
	PlaylistItem *item = firstItem;
        while(item) {
		file << item->order << '\t' << item->duration << '\t' << item->name << endl;
		item = item->nextItem;
	}
}

Playlist::~Playlist()
{
	PlaylistItem *item;
	while(firstItem) {
		item = firstItem->nextItem;
		delete firstItem;
		firstItem = item;
	}
}
