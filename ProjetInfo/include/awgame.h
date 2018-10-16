#include <iostream>
#include <string>

class AWGame 
	/*
		The Game will hold all gamestate informations (exemple. Players, Map, Units...) it's the core of the model in the MVC Pattern
	*/
{

	public:
		AWGame();
		AWGame(std::string config[]);
};