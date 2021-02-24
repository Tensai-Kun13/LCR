#pragma once

#include <vector>

#include "Player.h"
#include "PlayerOptions.h"
#include "Dice.h"

class Game
{
private:
	Dice m_dice;
	int numPlayers{ 3 }, loserCounter{ 0 }, chipsInPot{ 0 };
	bool noWinner { true };

	using PlayerList = std::vector<Player>;
	PlayerList players;

	void welcomePlayer();
	void showRules() const;
	void givePlayerOptions() const;
	bool intInputCheck(int&);
	PlayerOptions evaluateOptionsInput(int& playerInput) const;
	void setupPlayers();
	void gameRound();
	void playerTurn(Player&, Player&, Player&);
	void waitRollInput();
	void checkWinner();
	void printScoreboard();
	void printWinner();
	
public:

	void runGame();
};
