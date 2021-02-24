#include "Dice.h"
#include <iostream>

using namespace std;

void Dice::convertNumbertoSymbol(int& number)
{
	// display message of which special LCR die side based on number rolled
	{
		switch (number)
		{
		case 1:
		{
			cout << "You rolled an: L\n";
		}
		break;
		case 2:
		{
			cout << "You rolled an: R\n";
		}
		break;
		case 3:
		{
			cout << "You rolled a: C\n";
		}
		break;
		default:
		{
			cout << "You rolled a: *\n";
		}
		break;
		}
	}
}

void Dice::rollDice()
{
	number = (rand() % 6) + 1;
	convertNumbertoSymbol(number);
}
