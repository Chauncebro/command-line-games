#pragma once
#include <string>

using namespace std;

enum piece_colour { red, black, white, no_colour, invalid_colour };

string pc_to_string(piece_colour);
piece_colour get_pc(string);

struct Piece
{
	Piece();
	Piece(piece_colour, string, string);

	piece_colour the_c;
	string the_n;
	string the_r;

};
bool is_blank(Piece);