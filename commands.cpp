#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using PulBlock = std::vector<std::string>;
using Iter = std::vector< std::string >::const_iterator;

bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

void printBlock(Iter st, Iter end) {
	std::cout << "bulk: ";
	std::for_each(st, end - 1, [](const std::string& str) {std::cout << str << ","; });
	std::cout << *(end - 1) << std::endl;
}

bool addStatBlock(PulBlock& bl, const std::string& str) {
	if(str=="EOF")
		return false;
	bl.push_back(str);
	if (bl.size() == bl.capacity())
		return false;
	else 
		return true;
}


bool addDynBlock(PulBlock& , std::string& ) {
	return 0;
}


int main(int argc, char* argv[])
{
	int cmd_count;
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
	cmd_count = atoi(argv[1]);

	//Заполнение статического блока
	std::string cmd;
	PulBlock static_pul_block;
	PulBlock dynamic_pul_block;
	static_pul_block.reserve(cmd_count);

	Iter it_start;
	Iter it_end;
	bool flag_ins = false;

	//Заполнение статического блока
	do {
		std::cin >> cmd;
		flag_ins = addStatBlock(static_pul_block, cmd);
		if (!flag_ins) {
			printBlock(static_pul_block.cbegin(), static_pul_block.cend());
			static_pul_block.clear();
			addDynBlock(dynamic_pul_block, cmd);
		}
	} while (cmd != "EOF");

	return 0;
}
