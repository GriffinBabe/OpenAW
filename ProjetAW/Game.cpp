#include "Game.h"
#include <iostream>
#include <string>
#include <QtDebug>
#include "window.h"

using std::string;
using namespace std;

Game::Game() {

}

Game::Game(string arg[]) {
	args = arg;
}

void Game::printArgs() {
	for (int i = 0; i < this->args->length(); i++) {
		string str = this->args[i];
	}
}