#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <istream>
#include <iomanip>
#include "new_piece.h"

class tictactoegame
{
	friend ostream& operator<< (ostream &, const tictactoegame &);//we make the operator a friend to give access to private variables
private:
	vector<Piece> pieces;
	vector<string> o_move;
	vector<string> x_move;
	unsigned height;
	unsigned width;
	bool play1t;
	bool keep_going;
	bool ai;
	unsigned lastX;
	unsigned lastY;
public:
	tictactoegame();
	tictactoegame(bool);
	tictactoegame(vector<Piece>);
	bool done();
	bool draw();
	void end_game();
	void prompt(unsigned &, unsigned &);
	void auto_play();
	bool isGameOver();
	bool isFilled(unsigned, unsigned);
	void turn();
	int play();
	void comp_turn(unsigned &, unsigned &);
};

ostream& operator<< (ostream &, const tictactoegame &);