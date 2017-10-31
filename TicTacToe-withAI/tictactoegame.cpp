#include "stdafx.h"
#include "tictactoegame.h"
#include "game_board.h"
#include "lab2.h"
#include<iostream>
#include<algorithm>

ostream& operator<< (ostream & oss, const tictactoegame & the_game)//allows us to easily print the board
{
	print_pieces(the_game.pieces, the_game.width, the_game.height);//uses the print pieces method from previous lab
	return oss;
}

void tictactoegame::end_game()//helper method to test if the game is over
{
	keep_going = false;
}

bool tictactoegame::isFilled(unsigned row, unsigned column)//checks a square to see if it is already occupied
{
	Piece in_spot = pieces[row * 5 + column];
	return !(in_spot.the_c == no_colour);
}

bool tictactoegame::draw()//determines if the game is drawn by checking if all spots are occupied
{
	for (unsigned i = 1; i <= 3; ++i)
	{
		for (unsigned j = 1; j <= 3; ++j)
		{
			if (!isFilled(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

bool tictactoegame::done()//checks if either player has three in a row
{
	Piece p1; Piece p2; Piece p3;
	for (unsigned i = 0; i < 3; i++) {
		p1 = pieces[(i + 1) * 5 + 1];
		p2 = pieces[(i + 1) * 5 + 2];
		p3 = pieces[(i + 1) * 5 + 3];
		if (p1.the_c == p2.the_c && p2.the_c == p3.the_c && isFilled(i + 1, 1))
		{
			return true;
		}
		p1 = pieces[(1) * 5 + i + 1];
		p2 = pieces[(2) * 5 + i + 1];
		p3 = pieces[(3) * 5 + i + 1];
		if (p1.the_c == p2.the_c && p2.the_c == p3.the_c && isFilled(1, i+1))
		{
			return true;
		}
	}
	p1 = pieces[6];
	p2 = pieces[12];
	p3 = pieces[18];
	if (p1.the_c == p2.the_c && p2.the_c == p3.the_c && isFilled(2, 2))
	{
		return true;
	}

	p1 = pieces[8];
	p2 = pieces[12];
	p3 = pieces[16];
	if (p1.the_c == p2.the_c && p2.the_c == p3.the_c && isFilled(2, 2))
	{
		return true;
	}
	return false;
}

void tictactoegame::prompt(unsigned &column, unsigned &row) //repeatedly prompts the user for input until it gets
															// some input of good form in a square that is not occupied
{
	cout << "enter move '<column>,<row> or 'quit' to quit" << endl;
	string input_line = "";
	getline(cin, input_line);
	bool worked = false;
	if (input_line.compare("quit")==0)//quit when the user says quit
	{
		throw user_quit;
	}
	else
	{
		unsigned row_in;
		unsigned column_in;
		replace(input_line.begin(), input_line.end(), ',', ' ');
		stringstream ss(input_line);
		if (ss >> column_in)
		{
			if (ss >> row_in)
			{
				if ((row_in > 0 && row_in < 4) && (column_in > 0 && column_in < 4))//check input to see if its in the correct range
				{
					if (!isFilled(row_in, column_in))//make sure spot isn't already taken
					{
						row = row_in;
						column = column_in;
						return;
					}
					else
					{
						cout << "please pick a spot that is not taken" << endl;
						prompt(column, row);
						return;
					}
				}
			}
		}
	}
	cout << "not the right input.  Make sure you type row then a space then column or 'exit;" << endl;
	cout << "the minimum for row and column is 1 and the maximum is 3" << endl;
	prompt(column, row);//call this method again if no input of good form

}

void tictactoegame::comp_turn(unsigned &x, unsigned &y)//the computer is always Xs
{
	if (lastX == 4 && lastY == 4)//computer always goes in the middle first
	{
		x = 2;
		y = 2;
		return;
	}
	for (unsigned i = 1; i <= 3; ++i)//this checks every square to see if it is a winning move, if it is that is the computers move
	{
		for (unsigned j = 1; j <= 3; ++j)
		{
			tictactoegame temp = tictactoegame(pieces);
			if (temp.pieces[5 * i + j].the_c == no_colour)
			{
				Piece pot_move = Piece(red, "Xs", "x");
				temp.pieces[5 * i + j] = pot_move;
				if (temp.done())
				{
					x = j;
					y = i;
					return;
				}
			}
		}
	}
	
	for (unsigned i = 1; i <= 3; ++i)//check to see if there is a square the opponent wins with, take it if there is
	{
		for (unsigned j = 1; j <= 3; ++j)
		{
			tictactoegame temp = tictactoegame(pieces);
			if (temp.pieces[5 * i + j].the_c == no_colour)
			{
				Piece pot_move = Piece(black, "Os", "o");
				temp.pieces[5 * i + j] = pot_move;
				if (temp.done())
				{
					x = j;
					y = i;
					return;
				}
			}
		}
	}

	unsigned potX = 2;//this calculates the optimal move given that we got the middle square (which we always do)
	unsigned potY = 2;//this is just the opposite of where the player goes
	if (lastX == 3) {
		potX = 1;
	}
	if (lastX == 1) {
		potX = 3;
	}
	if (lastY == 3) {
		potY = 1;
	}
	if (lastY == 1) {
		potY = 3;
	}

	if(!isFilled(potY, potX))//make sure the space is not filled
	{
		bool canDo = true;
		tictactoegame temp2 = tictactoegame(pieces);
		Piece my_move = Piece(black, "Xs", "x");
		temp2.pieces[potX * 5 + potY] = my_move;
		for (unsigned i = 1; i <= 3; ++i)//check the optimal move to see if it lets opponent win
		{
			for (unsigned j = 1; j <= 3; ++j)
			{
				tictactoegame temp = tictactoegame(temp2.pieces);
				if (temp.pieces[5 * i + j].the_c == no_colour)
				{
					Piece pot_move = Piece(red, "Os", "o");
					temp.pieces[5 * i + j] = pot_move;
					if (temp.done() && !isFilled(i, j))
					{
						canDo = false;
					}
				}
			}
		}
		if (canDo) {//plays the optimal move if it is safe
			x = potX;
			y = potY;
			return;
		}
	}

	for (unsigned i = 1; i <= 3; ++i) //returns the first available move when all other tactics fail to find a good one
	{
		for (unsigned j = 1; j <= 3; ++j)
		{
			if (!isFilled(i, j)) {
				x = j;
				y = i;
				return;
			}
		}
	}
}

bool tictactoegame::isGameOver()
{
	return !keep_going;
}


void tictactoegame::auto_play() {//the autoplay method plays 1 turn for the computer
	unsigned col; unsigned row;
	comp_turn(col, row);
	pieces[5 * row + col] = Piece(red, "Xs", "x");
	cout << row << " " << col;
}

void tictactoegame::turn()//this method accounts for a single turn for either player but not both
{
	if (!ai) {//this first half is for when we have humans for both players
		if (play1t)
		{
			cout << "Xs turn" << endl;
		}
		else
		{
			cout << "Os turn" << endl;
		}
		unsigned col; unsigned row;

		try {
			prompt(col, row);//get the input
		}
		catch (er_mes user_quit) {
			throw user_quit;
		}
		string s = to_string(col) + "," + to_string(row);
		unsigned index = row * 5 + col;
		if (!keep_going)
		{
			return;
		}

		if (play1t)
		{
			Piece to_insert = Piece(red, "Xs", "x");
			pieces[index] = to_insert;
			x_move.push_back(s);
		}
		else
		{
			Piece to_insert = Piece(black, "Os", "o");
			pieces[index] = to_insert;
			o_move.push_back(s);
		}
	}
	else {//this is when there is only one player
		if (play1t) {//computer turn
			auto_play();
			cout << "hi" << endl;
		}
		else
		{
			cout << "Os turn" << endl;
			unsigned col; unsigned row;

			try {
				prompt(col, row);
			}
			catch (er_mes user_quit) {
				throw user_quit;
			}
			if (!keep_going)
			{
				return;
			}
			string s = to_string(col) + "," + to_string(row);
			unsigned index = row * 5 + col;
			lastX = col;
			lastY = row;
			Piece to_insert = Piece(black, "Os", "o");
			pieces[index] = to_insert;
			o_move.push_back(s);
		}
	}
	if (done())//check to see if somebody one
	{
		tictactoegame temp = tictactoegame(pieces);
		cout << temp << endl;
		if (!play1t)//determine which player won
		{
			cout << "Os wins" << endl;
			end_game();
		}
		else
		{
			cout << "Xs wins" << endl;
			end_game();
		}
	}
	else if (draw())//check if the game is drawn
	{
		tictactoegame temp = tictactoegame(pieces);
		cout << temp << endl;
		throw game_drawn;
	}
	play1t = !play1t;//switch the players turn

}

int tictactoegame::play() //this method handles one whol instance of a game
{
	while (!isGameOver())//loop until game is over
	{
		tictactoegame temp = tictactoegame(pieces);//print out the current board
		cout << temp << endl;
		if (play1t) {//print out player Os entire set of moves each time they move
			cout << "O: ";
			for (unsigned i = 0; i < o_move.size(); i++) {
				cout << o_move[i] << ";";
			}
			cout << "" << endl;
		}
		else//print out player Xs entire set of moves each time they move
		{
			cout << "X: ";
			for (unsigned i = 0; i < x_move.size(); i++) {
				cout << x_move[i] << ";";
			}
			cout << "" << endl;
		}

		try
		{
			turn();
		}
		catch (er_mes a) {//handle quit or draw

			switch (a) {
			case user_quit:
				cout << "you quit" << endl;
				break;
			case game_drawn:
				cout << "the game is a draw as there are no more legal moves";
				break;
			}
			return a;
		}
		
	}
	return success;
}

tictactoegame::tictactoegame()//standard constructor of a new game
	: height(5), width(5), play1t(false),keep_going(true),ai(false) {
	Piece empty_piece = Piece(no_colour, " ", " ");
	for (unsigned i = 1; i <=25; i++)
	{
		pieces.push_back(empty_piece);
	}
}
tictactoegame::tictactoegame(bool the_ai)//constructor for when they want autoplayer
	: height(5), width(5), play1t(true), keep_going(true), ai(the_ai),lastX(4),lastY(4) {
	Piece empty_piece = Piece(no_colour, " ", " ");
	for (unsigned i = 1; i <= 25; i++)
	{
		pieces.push_back(empty_piece);
	}
}

tictactoegame::tictactoegame(vector<Piece> pieces2)//copy constructor used for creating boards for the autoplayer to test moves without changing current board
	: height(5), width(5), play1t(false), keep_going(true), pieces(pieces2){}