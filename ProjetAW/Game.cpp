#include "Game.h"
#include <iostream>
#include <string>
using std::string;

Game::Game() {

}

Game::Game(string args[]) {
	args = args;
}

string * Game::getArgs() {
	return args; //this functions args
}