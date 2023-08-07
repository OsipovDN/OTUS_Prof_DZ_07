#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <chrono>

struct Command {
	std::string cmd;
	std::time_t tm;

	Command(const std::string& str) :cmd(str) {
		tm = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}
};

using StaticPullBlock = std::vector<Command>;
using DynamicPullBlock = std::deque<Command>;
template <typename T>
using Iter = typename T::const_iterator;


class ComandDistr {
private:
	StaticPullBlock st_pl_cmd;
	DynamicPullBlock dn_pl_cmd;
	bool flag_scope;

	bool isScope(const std::string& str) {
		if (str == "{" || str == "}") {
			if (str == "{")
			flag_scope = true;
			if (str == "}")
			flag_scope = false;
			return true;
		}
		else
			return false;
	}

	//Fix it
	bool addStBlock(const std::string& str) {
		if (st_pl_cmd.size() != st_pl_cmd.capacity()) {
			st_pl_cmd.emplace_back(Command(str));
			return true;
		}
		else
			return false;
	}

	//TODO
	bool addDynBlock(const std::string&) {
		return true;
	
	}
	template <typename T>
	void printBlock(Iter<T> st, Iter<T> end) {
		std::cout << "bulk: ";
		std::for_each(st, end - 1, [](const Command& str) {std::cout << str.cmd << ","; });
		std::cout << (end - 1)->cmd << std::endl;
	}

public:
	explicit ComandDistr(int& count) {
		st_pl_cmd.reserve(count);
		flag_scope = false;
	}

	void run() {
		std::string cmd;
		do {
			std::cin >> cmd;
			if (isScope(cmd)) {
				if (flag_scope) {
				printBlock<StaticPullBlock>(st_pl_cmd.cbegin(), st_pl_cmd.cend());
				st_pl_cmd.clear();
					addDynBlock(cmd);
				}
				else 
					printBlock<DynamicPullBlock>(dn_pl_cmd.cbegin(), dn_pl_cmd.cend());
			}
			else
				addStBlock(cmd);
		} while (cmd != "EOF");
	}

};