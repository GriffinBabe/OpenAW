#include "game.h"

Game::Game()
{
	std::vector<Player> players; // vector initialisation
}

void Game::newPlayer(Player p)
{
	players.push_back(p); // Adds the player to the vector
}

void Game::setLocalPlayer(Player p) {
	localPlayer = p;
}

Player& Game::getLocalPlayer()
{
	return localPlayer;
}
