#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using PulBlock = std::vector<std::string>;

bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

void addBlock(PulBlock& p, const size_t& c) {
	size_t i = 0;
	std::string block;
	while (i != c) {
		std::cin >> block;
		if (block == "EOF") {
			p.push_back(block);
			break;
		}
		else
			p.push_back(block);
		i++;
	}
}

int main(int argc, char* argv[])
{
	int block_count;
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
	block_count = atoi(argv[1]);

	//Заполнение статического блока
	PulBlock pul_block;
	bool flag = false;
	auto print = [](const std::string& bl) {
		if (bl != "EOF")
			std::cout << bl << " ";
	};

	do {
		addBlock(pul_block, block_count);
		std::vector< std::string >::const_iterator iter = pul_block.begin();
		flag = std::any_of(iter, pul_block.cend(), [](const std::string& com) {return com == "EOF"; });
		std::cout << "bulk: ";
		std::for_each(pul_block.cbegin(), pul_block.cend(), print);
		std::cout << std::endl;
		iter += block_count;


	} while (!flag);




	return 0;
}
