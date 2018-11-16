#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "gamecontroller.h"
#include <fstream>
#include <ios>
using namespace std;

void surprise(){
	vector<string> files{"surprise.txt", "surprise2.txt", "surprise3.txt"};
	srand(time(NULL));
	int random = 0 + rand()% (4 - 0); 

	ifstream f{files[random]};
	string s;
	while(getline(f, s)) {
		cout << s;
	}
	//if (f.is_open()) 
	//	cout << f.rdbuf();
}


int main(int argc, char* argv[]) {
	string boardFile = (argc<=1) ? "" : argv[1]; //randomly generate if nothing given

	bool newGame = true;
	while (newGame) {
		unique_ptr<GameController> controller = make_unique<GameController>(boardFile);

		cout << "WELCOME TO CC3K" << endl
			<< "Choose your race:" << endl
			<< "[s]hade: (125 HP, 25 Atk, 25 Def)" << endl
			<< "[d]row: (150 HP, 25 Atk, 15 Def)" << endl
			<< "[v]ampire: (50 HP, 25 Atk, 25 Def)" << endl
			<< "[t]roll: (120 HP, 25 Atk, 15 Def)" << endl
			<< "[g]oblin: (110 HP, 15 Atk, 20 Def)" << endl;

		//Make Player
		string race;
		if (cin >> race) {
			if (race == "q") { break; }
			while (!(controller->makePlayer(race))) {
				cout << race << " is not a race." << endl << " Please enter one of: s, d, v, t, g." << endl;
				cin >> race; 
			}
		} else {
			break; //bad input
		}

		controller->startGame();
		
		bool turn = true;
		while (turn) {
			cout << "HERE???" << endl;
			controller->print();
			cout << "Printed" << endl; 

			cout << "Enter one of:" << endl
				<< "no, so, ea, we, nw, se, sw - to move in that direction" << endl
				<< "u <direction> - use potion in direction" << endl
				<< "a <direction> - attack enemy in direction" << endl
				<< "f - freeze enemies" << endl
				<< "r - restart the game" << endl
				<< "q - quit game" << endl;
			
			string cmd;
			if (!(cin >> cmd)) { break;}

			if (cmd == "u") {
				string dir;
				if (!(cin >> dir)) { break; }
				if (!(controller->usePotion(dir))) {
					cout << dir << " is not a valid direction." << endl;
				} 
			} else if (cmd == "a") {
				string dir;
				if (!(cin >> dir)) { break; }
				cout << "dir is: " << dir << endl; 
				if (!(controller->attackEnemy(dir))) {
					cout << dir << " is not a valid direction." << endl;
				} 				
			} else if (cmd == "f") {
				controller->freezeEnemies();
			} else if (cmd == "r") {
				break;
			} else if (cmd == "q") {
				newGame = false;
				break;
			} else {
				if (!controller->movePlayer(cmd)) {
					cout << "Invalid command." << endl;
				}
			}

			if (controller->getGameOver()) {
				controller->print();
				cout << "Looks like the game has ended!" << endl;
				controller->printScore();
				cout << "Would you like to play again? (y/n)" << endl;
				char playAgain;
				while (true) {
					while (!(cin >> playAgain)) {
						cout << "Please enter [y] or [n]!" << endl;
						cin.clear();
						cin.ignore();
					}

					if (playAgain == 'y') {
						turn = false;
						break;
					} else if (playAgain == 'n') {
						turn = false;
						newGame =  false;
						break;
					} 
				}
			} 
		}
	}
	surprise();
}
