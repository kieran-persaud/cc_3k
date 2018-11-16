#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int rows, int cols) : rows{rows}, cols{cols} {
	theDisplay.resize(rows, vector<char>(cols, ' ')); 
 }


TextDisplay::~TextDisplay() {}


void TextDisplay::notify(Subject &whoNotified) {
	Info i = whoNotified.getInfo(); 
	theDisplay[i.x][i.y] = i.sc; //should this be [i.x][i.y] ?? 
}


void TextDisplay::updateStats(std::string race, int gold, int curFloor, 
	int hp, int atk, int def) {
	this->race = race;
	this->gold = gold;
	this->curFloor = curFloor;
	this->hp = hp;
	this->atk = atk;
	this->def = def;
}


void TextDisplay::updateAction(string action){
	this->action += action;
}


ostream &operator<<(ostream &out, TextDisplay &td) {
	for (int i=0; i < td.rows; i++){
		for (int j=0; j < td.cols; j++){
			out << td.theDisplay[i][j];
		}
		cout << endl;
	}

	//This is the text under the map
	//79, 3 white spaces --> 76
	out << "Race: " << left << setw(8) << td.race //8+6 = 14
    	<< "Gold: " << left << setw(5) << td.gold //5+6 = 11
    	<< right << setw(44) << "Floor " << td.curFloor << endl //6 32
    	<< "HP: " << td.hp << endl
		<< "Atk: " << td.atk << endl
		<< "Def: " << td.def << endl
		<< "Action: " << td.action << endl; //what is this?

	td.action = ""; //reset action string
	return out;
}	
