#pragma once

#include <string>

class Player
{
private:
	std::string playerName{ "Player "};
	unsigned int numChips{ 3 }, numDice{ 0 };
	bool isLoser{ false };
	

public:
	void setName(const unsigned int name) { playerName += std::to_string(name); }

	const std::string& getName() const { return playerName; }

	void addChip() { ++numChips; }

	void subtractChip();

	const unsigned int& getChips() const { return numChips; }

	void setDice();

	const unsigned int& getDice() const { return numDice; }

	void passChip(Player&);

	void setIsLoser(const bool loser) { isLoser = loser; }

	const bool getIsLoser() const { return isLoser; }
};
