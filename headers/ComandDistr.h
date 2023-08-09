#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <chrono>


using StaticPullBlock = std::vector<std::string>;
using DynamicPullBlock = std::deque<std::string>;


class ComandDistr {
private:
	StaticPullBlock st_pl_cmd;
	DynamicPullBlock dn_pl_cmd;
	size_t scope_block;

public:
	explicit ComandDistr(int& count) :scope_block(0) {
		st_pl_cmd.reserve(count);
	}

	void run() {
		std::string cmd;
		while (std::getline(std::cin, cmd)) {
			addStBlock(cmd);
			addDynBlock(cmd);
		}


	}

	bool isScope(const std::string& str) {
		if (str == "{" || str == "}") {
			if (str == "{")
				scope_block++;
			if (str == "}")
				scope_block--;
			return true;
		}
		std::cin.ignore();
		return false;
	}

	bool addStBlock(const std::string& str) {
		if (!isScope(str))
			st_pl_cmd.emplace_back(str);
		if (st_pl_cmd.size() == st_pl_cmd.capacity())
			return true;
		else
			return false;
	}

	//TODO
	bool addDynBlock(const std::string&) {
		return true;

	}
	template <typename T>
	void printBlock(T obj) {
		std::cout << "bulk: ";
		std::for_each(obj.cbegin(), obj.cend() - 1, [](const std::string& str) {std::cout << str << ","; });
		std::cout << *(obj.cend() - 1) << std::endl;
	}
};