#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

int main(int argc, char* argv[])
{
	int block_count;
	if (argc != 2) {
		std::cout << "Incorrect argument input" << std::endl;
		exit(1);
	}
	if (!isDig(argv[1])) {
		std::cout << "Not a val" << std::endl;
		exit(1);
	}
	block_count = atoi(argv[1]);

	std::vector<std::string> pul_block;
	std::string block;
	size_t i = 0;
	while (i != block_count) {
		std::cin >> block;
		pul_block.push_back(block);
		i++;
	}

	auto predPrint = [](const std::string& bl) {
		std::cout << bl << std::endl; };
	std::for_each(pul_block.cbegin(), pul_block.cend(), predPrint);

	return 0;
}
