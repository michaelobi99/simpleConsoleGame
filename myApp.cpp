#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
using namespace std::literals::string_literals;
enum class direction : std::uint8_t { LEFT, UP, RIGHT, DOWN };

std::vector<std::string> field{
		"########################################\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"##############################..........\n"s,
		"........................................\n"s,
		"....................####################\n"s,
		"........................................\n"s,
		"########################################\n"s };

void displayField(std::uint32_t const& position_row, std::uint32_t const& position_col) {
	std::ostringstream output;
	field[position_row][position_col] = 'x';
	std::cout << "size = " << std::size(field)<<"\n";
	std::for_each(std::cbegin(field), std::cend(field), [&output](std::string line) {output << line; });
	std::cout << output.str();
}
auto getDirection() {
	while (true) {
		for (std::uint8_t key = 8; key <= 222; ++key) {
			if (GetAsyncKeyState(key) == -32767) {
				if (key == VK_UP)
					return direction::UP;
				else if (key == VK_LEFT)
					return direction::LEFT;
				else if (key == VK_RIGHT)
					return direction::RIGHT;
				else if (key == VK_DOWN)
					return direction::DOWN;
			}
		}
	}
	
}

auto movePlayer(direction const& dir, std::uint32_t row, std::uint32_t col) -> std::tuple<std::uint32_t, std::uint32_t> {
	auto isEven = [](std::uint32_t num) {return num % 2 == 0; };
	switch (dir) {
	case direction::LEFT: {
		auto testStr = field[row];
		if (testStr[col - 1] != '#' && col > 1)
			--col;
		break;
	}
	case direction::RIGHT: {
		auto testStr = field[row];
		if (testStr[col + 1] != '#' && col < 39)
			++col;
		break;
	}
	case direction::UP: {
		if (row > 1) {
			auto testStrUpper = field[row - 1];
			if (testStrUpper[col] != '#')
				--row;
		}
		break;
	}
		
	case direction::DOWN: {
		if (row < 28) {
			auto testStrLower = field[row + 1];
			if (testStrLower[col] != '#')
				++row;
		}
		break;
	}
	}
	return std::tuple(row, col);
}

int main() {
	std::uint8_t player{ 'x' };
	std::uint32_t playerPosition_row = 1;
	std::uint32_t playerPosition_col = 30;
	while (true) {
		displayField(playerPosition_row, playerPosition_col);
		auto direction = getDirection();
		auto [nextPosition_row, nextPosition_col] = movePlayer(direction, playerPosition_row, playerPosition_col);
		std::swap(nextPosition_row, playerPosition_row);
		std::swap(nextPosition_col, playerPosition_col);
		field[nextPosition_row][nextPosition_col] = '.';
		system("cls");
	}
}