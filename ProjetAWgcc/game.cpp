#include "game.h"
#include <string>

Game::Game(std::string username)
{
	std::cout << username << std::endl;
	std::vector<Player* (std::string)> players; // vector initialisation
}

void Game::yell() {
	std::cout << "yaaaaaaah" << std::endl;
}

void Game::newPlayer(Player& p)
{
	players.push_back(p); // Adds the player to the vector
}

void Game::setLocalPlayer(Player& p) {
	this->localPlayer = &p;
}

Player* Game::getLocalPlayer()
{
	return localPlayer;
}
