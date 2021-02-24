#include "Player.h"
#include <iostream>

using namespace std;

void Player::setDice()
{
	// set number of dice to number of chips, max 3 dice
	if (numChips >= 3)
	{
		numDice = 3;
	}
	else
	{
		numDice = numChips;
	}
}

void Player::subtractChip()
{
	// subtract chips if any
	if (numChips == 0)
	{
		cout << playerName << " has no more chips\n";
	}
	else
	{
		--numChips;
	}
}

void Player::passChip(Player& player)
{
	subtractChip();

	// give appropriate player chip and display message
	player.addChip();
	cout << getName() << " passed " << player.getName() << " a chip\n\n";
}