#include "game.h"
#include <iostream>

Game::Game()
{
	std::vector<Player> players; // Initialises new player vector
	std::cout << "[Game Model] Game Initialised" << std::endl;
	cursorX = 0;
	cursorY = 0;
}

void Game::addPlayer(Player p)
{
	players.push_back(p);
	std::cout << "[Game Model] Player with username " << p.getUsername() << " added to game." << std::endl;
}

void Game::addUnit(Unit u)
{
	units.push_back(u);
}

Player* Game::getPlayerByUsername(std::string username) {
	for (auto it = players.begin(); it != players.end(); ++it) {
		if (it->getUsername().compare(username)==0) {
			return &players.at(std::distance(players.begin(),it));
		}
	}
	return NULL;
}

void Game::setCursor(int x, int y)
{
	//temporary but should get on map
	int cellSize = 64; // in pixels
	cursorX = x/cellSize;
	cursorY = y/cellSize;
}

int Game::getCursorX()
{
	return cursorX;
}

int Game::getCursorY()
{
	return cursorY;
}
