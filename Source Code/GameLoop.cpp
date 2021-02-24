#include "GameLoop.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Game::welcomePlayer()
{
	cout << "Welcome to LCR!\n\n";
	showRules();
}

void Game::showRules() const
{
	string line;
	ifstream myFile("LCR_Rules.txt");

	// checks if the file is open
	if (myFile.is_open())
	{
		// checks if there is a line in the file and writes to the console line by line
		while (getline(myFile, line))
		{
			cout << line << '\n';
		}
		myFile.close();
	}
	else cout << "Unable to open file\n";
}

// prints out player options
void Game::givePlayerOptions() const
{
	cout << "What would you like to do? (Enter a corresponding number)\n\n";
	cout << "1: Start Game\n";
	cout << "2: Show Rules\n";
	cout << "3: Quit\n";
}

bool Game::intInputCheck(int& input)
{
	// loop to make sure input is valid, replays message and takes input until valid
	bool isValid = true; // condition to exit loop
	do
	{
		cin >> input;

		// checks if input fails
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');    //clear buffer before taking new line
			cout << "You have entered an incorrect input\n";
			isValid = false;
		}
	} while (!isValid);

	return isValid;
}

PlayerOptions Game::evaluateOptionsInput(int& playerInput) const
{
	PlayerOptions chosenOption;

	// takes in player input and sets chosenOption based on input
	switch (playerInput)
	{
	case 1:
		cout << "Let's Play LCR!\n\n";
		chosenOption = PlayerOptions::Start;
		break;
	case 2:
		chosenOption = PlayerOptions::ShowRules;
		break;
	case 3:
		cout << "You have chosen to Quit!\n\n";
		chosenOption = PlayerOptions::Quit;
		break;
	default:
		cout << "I do not recognize that option, try again!\n\n";
		chosenOption = PlayerOptions::None;
	}

	return chosenOption;
}

void Game::setupPlayers()
{
	// asks how many players
	cout << "How many players are playing?\n";
	intInputCheck(numPlayers);

	// check to make sure there are at least 3 players
	while (numPlayers < 3)
	{
		cout << "You need at least 3 players\n";
		intInputCheck(numPlayers);
	}

	// adds as many player instances to players vector as number of players
	for (size_t i = 0; i < numPlayers; ++i)
	{
		Player newPlayer;
		newPlayer.setName(i + 1);	// set player name to "Player (player number)"
		players.push_back(newPlayer);
	}
}

void Game::gameRound()
{
	// iterate through players vector
	for (size_t i = 0; i < players.size(); ++i)
	{
		noWinner = true;	// make sure there is no winner to start round

		// if player has 0 chips, skip turn
		if (players[i].getIsLoser())
		{
			break;
		}
		
		cout << players[i].getName() << "'s turn:\n";	// displays which player's turn it is
		
		if (&players[i] == &players[0])	// checks if player is first element of players vector
		{
			// run player's turn, player to left is last element of players vector, player to right is next element of players vector
			playerTurn(players[i], players[numPlayers - 1], players[i + 1]);
		}
		else if (&players[i] == &players[numPlayers - 1])	// checks if player is last element of players vector
		{
			// run player's turn, player to left is previous element of players vector, player to right is first element of players vector
			playerTurn(players[i], players[i - 1], players[0]);
		}
		else    // if player is not first or last element of players vector
		{
			// run player's turn, player to left is previous element of players vector, player to right is next element of players vector
			playerTurn(players[i], players[i - 1], players[i + 1]);
		}

		cout << endl;
		
		checkWinner();

		// set noWinner to false and break from round loop if there is 1 non-loser (winner)
		if (loserCounter == (numPlayers - 1))
		{
			noWinner = false;
			break;
		}
	}
}

void Game::playerTurn(Player& currentPlayer, Player& playerLeft, Player& playerRight)
{
	waitRollInput();
	currentPlayer.setDice();	// sets player's dice to number of chips, up to 3 max

	// rolls as many dice as player has
	for (size_t i = 0; i < currentPlayer.getDice(); ++i)
	{
		int dieFace;

		m_dice.rollDice();
		dieFace = m_dice.getNumber();

		// checks dice roll and passes chips as necessary
		switch (dieFace)
		{
		case 1:
			currentPlayer.passChip(playerLeft);
			break;
		case 2:
			currentPlayer.passChip(playerRight);
			break;
		case 3:
			currentPlayer.subtractChip();
			++chipsInPot;
			cout << currentPlayer.getName() << " has put a chip in the pot\n\n";
			break;
		default:
			cout << currentPlayer.getName() << " does not have to pass a chip\n\n";
		}
	}
}

// waits for player to type an r and hit enter to roll dice
void Game::waitRollInput()
{
	char r = 'a';
	while (r != 'r')
	{
		cout << "Type 'r' and hit enter to roll\n";
		cin >> r;
		cout << endl;
	}
}

void Game::checkWinner()
{
	loserCounter = 0;

	// checks each players' chip count, sets if they are a loser and adds to the loserCounter
	for (auto& player : players)
	{
		if (player.getChips() == 0)
		{
			player.setIsLoser(true);
			++loserCounter;
		}
		else
		{
			player.setIsLoser(false);
		}
	}
}

void Game::printScoreboard()
{
	cout << "Scoreboard:\n";

	// print each players' chip count
	for (auto& player : players)
	{
		cout << player.getName() << " has: " << player.getChips() << " chips left.\n";
	}

	cout << "There are: " << chipsInPot << " chips in the pot.\n\n";
}

void Game::printWinner()
{
	// goes through the players vector and prints first player that is not a loser and breaks from loop
	for (auto& player : players)
	{
		if (!player.getIsLoser())
		{
			cout << player.getName() << " is the winner!\n\n";
			break;
		}
	}
}

void Game::runGame()
{
	srand((int)time(0));    // Makes the random number generated a different number every time the program is
	
	welcomePlayer();

	bool shouldEnd = false;
	while (shouldEnd == false)
	{
		int playerInput;

		// repeatedly show player options until they input a valid choice
		do
		{
			givePlayerOptions();
		} while (!intInputCheck(playerInput));

		// sets option to option choice
		PlayerOptions option = evaluateOptionsInput(playerInput);

		if (option == PlayerOptions::ShowRules) showRules();

		// run game logic
		if (option == PlayerOptions::Start)
		{
			setupPlayers();
			int roundNumber = 0;

			// run game until !noWinner (is a winner)
			do
			{
				cout << "\nRound " << to_string(++roundNumber) << ":\n";	// print round number
				gameRound();
				printScoreboard();
			} while (noWinner);

			printWinner();	// print winner's name
		}

		// end program if player chooses to quit
		shouldEnd = option == PlayerOptions::Quit;
	}
}
