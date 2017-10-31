// lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "lab2.h"
#include "new_piece.h"
#include "game_board.h"
#include "tictactoegame.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <istream>
#include <iomanip>

using namespace std;

string to_lowcase(string s)//convert a string to all lower case
{
	string ans = s;
	for (auto c = s.begin(); c != s.end(); ++c)
	{
		if (*c > 64 && *c < 91)
		{
			*c = *c + 32;
		}
	}
	return ans;
}

int main(int argc, char* argv[])
{
	if (argc == 2) {//play standard game with two arguments
		string name = "TicTacToe";
		if (argv[1] == name)
		{
			tictactoegame the_game = tictactoegame();
			return the_game.play();

		}
		else 
		{
			cout << "you must enter 'TicTacToe' after the filename to play" << endl;
			cout << "<filename> TicTacToe or <filename> TicTacToe yes" << endl;
		}
	}
	else if (argc == 3)//when they enter a third arguement
	{
		string name = "TicTacToe";
		if (argv[1] == name)
		{
			cout << "1" << argv[2] << "1" << endl;
			string ai_tester = "yes";
			if(argv[2] == ai_tester)
			{ 
				cout << "you are playing against the ai" << endl;
				tictactoegame the_game = tictactoegame(true);
				return the_game.play();
			}
			else {
				cout << "you must enter yes if you want to play the auto player or nothing if you want to play another human" << endl;
				cout << "<filename> TicTacToe yes" << endl;
			}
		}
	
	}
	else
	{
		cout << "you must have exactly one or two arguements besides filename" << endl;
		cout << "<filename> TicTactoe or <filename> TicTacToe yes" << endl;
	}
}

