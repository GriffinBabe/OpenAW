#pragma once
#include <iostream>
#include <string>

using std::string;

class Game {
	/*
		Game is the core of the model in the MVC Pattern, this will contein all game elements such as the map,
		the units, the players etc...
	*/
private:
	string args[];

public:
	Game(); // Game with default settings
	Game(std::string args[]);
	string* getArgs();
};