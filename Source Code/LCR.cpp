// Robert Lew
// IT-312-X3436 Software Devel w/C++.Net 21EW3
// 2/20/2021
// Module 7-1 Final Project Submission: Dice Game

/*
Here is my full LCR game, this is the "main" file. All of the game logic is in GameLoop, with Player
logic and Dice logic in corresponding class files.
I had a minor issue iterating through my vector of Players. I could not get it to copy to a variable
by reference and affect the vector's element and save the results (in this case, the number of chips each player had).
Eventually, I did away with the variables and just used the element directly. Not best practice, but I got it to work at least.
From there, I mainly had an issue making sure that if the current player was the first element in the vector, the player to
their left was the last element in the vector. And when they were the last element, the player to the right was the first element.
I kept trying to use the front() and back() functions of vector, but I must have been using them incorrectly.
A couple of times this week to get the program finished, I just had to step away from the code and give myself a breather and look at it
later with fresh eyes, or give that time away from my screen to have an epiphany moment.
*/

#include "GameLoop.h"
using namespace std;

int main()
{
    Game game;
	game.runGame();

	return 0;
}
