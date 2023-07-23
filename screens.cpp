#include <iostream>
#include <fstream>
#include <iomanip>
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

void Screens::generateHTML()
{
	ofstream file;
	ScrItem *screen;

	file.open("index.html");
	if(file.is_open()) {
	file <<
"<!DOCTYPE html>\
<html lang='ru'>\
<head>\
  <meta charset='utf-8'>\
  <meta http-equiv='X-UA-Compatible' content='IE=edge'>\
  <meta name='viewport' content='width=device-width, initial-scale=1'>\
  <link rel='stylesheet' type='text/css' href='style.css' />\
  <title>Статистика по экранам</title>\
</head>\
<body>\
  <div class='container'>\
    <h1 style='font-size: 20px; text-align: center;'>Текущие плейлисты</h1>\
    <div class='tabs'>";

		screen = firstItem;
		while(screen) {
			file << "      <div id=\"" << screen->playlist->getName().c_str() << "\"><pre>";
			screen->playlist->print(file);
			file << "</pre>\n      </div>\n";
			screen = screen->nextItem;
		}
		file << "      <div class=\"tabs__links\">\n";
		screen = firstItem;
		while(screen) {
			int duration = screen->playlist->getDuration();
			int block_duration;
			if(!screen->playlist->getName().find("Barceloneta") or screen->playlist->getName() == "SeaZone") block_duration = duration;
			else if(screen->playlist->getName() == "Moremoll-in") block_duration = duration / 3;
			else block_duration = duration / 2;
			file << "        <a ";
			if(block_duration >= 295) file << "style = 'background-color: #ffa0a0;' ";
			file << "href=\"#" << screen->playlist->getName().c_str() << "\">";
			file << "<div style='float: right;'>(" << setfill('0') << setw(2) << block_duration / 60 << ":" << setfill('0') << setw(2) << block_duration % 60 << ")</div>";
			file << screen->playlist->getName().c_str() << "</a>\n";
			screen = screen->nextItem;
		}
		file <<
"      </div>\
    </div>\
  </div>\
</body>\
</html>";
	}
	file.close();
}
