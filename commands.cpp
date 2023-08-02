#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[])
{
	int com_val;
	if (argc != 2) {
		std::cout << "Incorrect argument input" << std::endl;
		exit(1);
	}
	std::string num = argv[1];
	auto isdig = [](char ch) {return std::isdigit(ch); };
	bool flag = std::all_of(num.cbegin(), num.cend(), isdig);
	if (!flag) {
		std::cout << "Not a val" << std::endl;
		exit(1);
	}
	com_val = stoi(num);

	return 0;
}
