#include "stdafx.h"
#include "new_piece.h"
#include "lab2.h"

using namespace std;

bool is_blank(Piece p)//check if a piece is blank
{
	piece_colour a = p.the_c;
	string b = p.the_n;
	string c = p.the_r;

	return ((a == no_colour && b == "" && c == " "));
}

string pc_to_string(piece_colour pc)//convert a piece colour enum to a string
{
	switch (pc)
	{
	case(white):
		return "white";
	case(black):
		return "black";
	case(red):
		return "red";
	case(no_colour):
		return "no colour";
	default:
		return "invalid colour";
	}
}

piece_colour get_pc(string s) {//get the enum value for a given string
	string ans = to_lowcase(s);

	if (ans == "white")
	{
		return white;
	}
	else if (ans == "black")
	{
		return black;
	}
	else if (ans == "red")
	{
		return red;
	}
	else if (ans == "" || ans == " " || ans == "no colour" || ans == "no color")
	{
		return no_colour;
	}
	else
	{
		return invalid_colour;
	}
}

Piece::Piece()//constructor for a default piece
	: the_c(no_colour), the_n("default name"), the_r("default rep.") {}

Piece::Piece(piece_colour pc, string name, string rep)//standard constructor for a piece
	: the_c(pc), the_n(name), the_r(rep) {}
