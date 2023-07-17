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
