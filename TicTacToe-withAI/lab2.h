#pragma once
#include <string>



enum er_mes {
	success = 0,
	wrong_num_args = -1,
	file_open_fail = -2,
	no_line_in_stream = -3,
	no_extract = -4,
	pieces_dont_fit = -5,
	no_pieces = -6,
	user_quit = -7,
	game_drawn = -8
};

std::string er_to_string(er_mes);
std::string to_lowcase(std::string);
enum index { program_name, file_name, num_args };

