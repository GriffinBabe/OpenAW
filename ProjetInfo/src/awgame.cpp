#include <iostream>
#include <string>
#include "include/awgame.h"

using namespace std;

AWGame::AWGame() {
	cout << "Game initialis�" << endl;
}

AWGame::AWGame(std::string config[]) {
	cout << "Game Initialis�!" << endl;
	for (int i = 0; i > config->length(); i++) {
		cout << config[i] << endl;
	}
}

AWGame::~AWGame() {
	cout << "Game d�truit!" << endl;
}