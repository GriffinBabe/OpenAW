#include <iostream>
#include <string>
#include "include/awgame.h"

using namespace std;

AWGame::AWGame() {
	cout << "Game initialisé" << endl;
}

AWGame::AWGame(std::string config[]) {
	cout << "Game Initialisé!" << endl;
	for (int i = 0; i > config->length(); i++) {
		cout << config[i] << endl;
	}
}

AWGame::~AWGame() {
	cout << "Game détruit!" << endl;
}