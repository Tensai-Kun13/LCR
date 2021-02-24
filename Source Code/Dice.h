#pragma once
#include <cstdlib>

class Dice
{
private:
	int number;

	void convertNumbertoSymbol(int&);

public:
	void rollDice();

	int getNumber() { return number; }
	

};