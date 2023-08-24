#include <iostream>
#include <string>
#include <algorithm>
#include "ComandDistr.h"

bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}


int main(int argc, char* argv[])
{
	//Проверка корректности ввода
	if (argc != 2) {
		std::cout << "Incorrect argument input" << std::endl;
		exit(1);
	}
	if (!isDig(argv[1])) {
		std::cout << "Not a val" << std::endl;
		exit(1);
	}

	//Фиксируем введенное значение
	int count = atoi(argv[1]);
	ComandDistr CmdDis (count);
	CmdDis.run();

	return 0;
}
