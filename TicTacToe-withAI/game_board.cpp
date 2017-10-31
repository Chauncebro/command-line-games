#include "stdafx.h"
#include "lab2.h"
#include "new_piece.h"
#include "game_board.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;

int board_dim(ifstream & scanny, unsigned & w, unsigned & h)
{
	unsigned result = 0;
	string line;

	if (scanny.is_open())
	{
		if (getline(scanny, line))
		{
			istringstream ss(line);
			if (ss >> w)
			{
				result = 1;
			}
			if (ss >> h)
			{
				result = 2 + result;
			}
		}
		else
		{
			return no_line_in_stream;
		}
	}
	else
	{
		return file_open_fail;
	}
	if (result == 1)
	{
		return no_extract;
	}
	else if (result == 2)
	{
		return no_extract;
	}
	else if (result == 3)
	{
		return success;
	}

	return success;
}

bool is_formatted(string s)
{
	istringstream ss(s);
	string a, b, c;
	unsigned d, e;
	unsigned suc = 0;
	if (ss >> a) {
		++suc;
	}
	if (ss >> b) {
		++suc;
	}
	if (ss >> c) {
		++suc;
	}
	if (ss >> d) {
		++suc;
	}
	if (ss >> e) {
		++suc;
	}
	return (suc == 5);
}

int read_piece(ifstream & scanny, vector<Piece> & pieces, unsigned w, unsigned h)
{
	unsigned p_count = 0;
	string line;

	if (scanny.is_open())//if this file exists
	{
		while (getline(scanny, line))
		{
			if (!line.empty())//ignore empty lines
			{
				if (is_formatted(line))
				{
					string a, b, c;
					unsigned d, e, ind;
					istringstream ss(line);
					ss >> a;
					ss >> b;
					ss >> c;
					ss >> d;
					ss >> e;
					piece_colour aa = get_pc(a);
					if (d < w && e < h && (aa != invalid_colour))
					{
						ind = e*w + d;
						Piece gp = Piece(aa, b, c);
						pieces[ind] = gp;
						++p_count;
					}
				}
			}
		}
		scanny.close();
	}
	else
	{
		return file_open_fail;
	}
	if (p_count == 0)
	{
		return no_pieces;
	}
	else
	{
		return success;
	}
}


int print_pieces(vector<Piece> pieces, unsigned w, unsigned h)
{
	if (pieces.size() > (w*h))
	{
		return pieces_dont_fit;
	}
	else
	{
		for (int high = h - 1; high >= 0; --high)
		{
			cout << high;
			for (int side = 0; side < w; ++side)
			{
				int ind = high*w + side;
				cout << pieces[ind].the_r;
			}
			cout << " " << endl;
		}
	}
	cout << " ";
	for (int z = 0; z < h; z++)
	{
		cout << z;
	}
	cout << "" << endl;
	return success;
}



int print_pieces_ind(vector<Piece> pieces, unsigned w, unsigned h)
{

	if (pieces.size() > (w*h))
	{
		return pieces_dont_fit;
	}
	else
	{
		Piece a_blank = Piece(no_colour, "", " ");
		for (int high = h - 1; high >= 0; --high)
		{
			for (int side = 0; side < w; ++side)
			{
				int ind = high*w + side;
				if (!is_blank(pieces[ind]))
				{
					cout << side << "," << high << " ";
					cout << pc_to_string(pieces[ind].the_c) << " ";
					cout << pieces[ind].the_r;

					int ind2 = high*w + side + w;
					int ind3 = high*w + side - w;
					int ind4 = high*w + side + 1;
					int ind5 = high*w + side - 1;
					int ind6 = high*w + side + w + 1;
					int ind7 = high*w + side + w - 1;
					int ind8 = high*w + side - w + 1;
					int ind9 = high*w + side - w - 1;
					int count = 0;

					if (ind2 >= 0 && ind2 < pieces.size()) {
						if (!is_blank(pieces[ind2])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side) << "," << (side + 1) << " ";
							cout << pc_to_string(pieces[ind2].the_c) << " ";
							cout << pieces[ind2].the_r;
						}
					}
					if (ind3 >= 0 && ind3 < pieces.size()) {
						if (!is_blank(pieces[ind3])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << side << "," << (high - 1) << " ";
							cout << pc_to_string(pieces[ind3].the_c) << " ";
							cout << pieces[ind3].the_r;
						}
					}
					if (ind4 >= 0 && ind4 < pieces.size() && side + 1<w) {
						if (!is_blank(pieces[ind4])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side + 1) << "," << (high) << " ";
							cout << pc_to_string(pieces[ind4].the_c) << " ";
							cout << pieces[ind4].the_r;
						}
					}
					if (ind5 >= 0 && ind5 < pieces.size() && side != 0) {
						if (!is_blank(pieces[ind5])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side - 1) << "," << (high) << " ";
							cout << pc_to_string(pieces[ind5].the_c) << " ";
							cout << pieces[ind5].the_r;
						}
					}
					if (ind6 >= 0 && ind6 < pieces.size() && side + 1<w) {
						if (!is_blank(pieces[ind6])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side + 1) << "," << (high + 1) << " ";
							cout << pc_to_string(pieces[ind6].the_c) << " ";
							cout << pieces[ind6].the_r;
						}
					}
					if (ind7 >= 0 && ind7 < pieces.size() && side>0) {
						if (!is_blank(pieces[ind7])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side - 1) << "," << (high + 1) << " ";
							cout << pc_to_string(pieces[ind7].the_c) << " ";
							cout << pieces[ind7].the_r;
						}
					}
					if (ind8 >= 0 && ind8 < pieces.size() && side + 1<w) {
						if (!is_blank(pieces[ind8])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side + 1) << "," << (high - 1) << " ";
							cout << pc_to_string(pieces[ind8].the_c) << " ";
							cout << pieces[ind8].the_r;
						}
					}
					if (ind9 >= 0 && ind9 < pieces.size() && side>0) {
						if (!is_blank(pieces[ind9])) {
							if (count == 0) {
								cout << ": ";
							}
							else {
								cout << "; ";
							}
							++count;
							cout << (side - 1) << "," << (high - 1) << " ";
							cout << pc_to_string(pieces[ind9].the_c) << " ";
							cout << pieces[ind9].the_r;
						}
					}
					cout << endl;
				}

			}
		}
	}

	return success;
}
