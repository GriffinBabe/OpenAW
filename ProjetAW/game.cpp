#include "game.h"
#include <iostream>

Game::Game()
{
	this->players = new std::vector<Player*>; // Initialises new player vector
	std::cout << "[Game Model] Game Initialised" << std::endl;
}

void Game::addPlayer(Player* p)
{
	this->players->push_back(p);
	std::cout << "[Game Model] Player with username " << p->username << " added to game." << std::endl;
}
