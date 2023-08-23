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
	bool is_open;

public:
	explicit ComandDistr(int& count) :scope_block(0), is_open(false) {
		st_pl_cmd.reserve(count);
	}

	void run() {
		std::string cmd;
		while (std::getline(std::cin, cmd)) {
			if (isScope(cmd)) {
				if (st_pl_cmd.size() != 0 && is_open) {
					printBlock(st_pl_cmd);
					st_pl_cmd.clear();
				}
				else if (scope_block == 0 && !is_open) {
					printBlock(dn_pl_cmd);
					dn_pl_cmd.clear();
				}
				continue;
			}
			if (scope_block == 0 && dn_pl_cmd.size() == 0)
				addStBlock(cmd);
			else
				addDynBlock(cmd);
		}
		if (st_pl_cmd.size()) {
			printBlock(st_pl_cmd);
			st_pl_cmd.clear();
		}
		if (dn_pl_cmd.size()) {
			printBlock(dn_pl_cmd);
			dn_pl_cmd.clear();
		}
	}

	bool isScope(const std::string& str) {
		if (str == "{") {
			is_open = !is_open;
			scope_block++;
			return true;
		}
		else if (str == "}") {
			is_open = !is_open;
			scope_block--;
			return true;
		}
		else
			return false;

	}

	void addStBlock(const std::string& str) {
		if (st_pl_cmd.size() != st_pl_cmd.capacity())
			st_pl_cmd.emplace_back(str);
		if (st_pl_cmd.size() == st_pl_cmd.capacity()){
			printBlock(st_pl_cmd);
			st_pl_cmd.clear();
		}
	}


	void addDynBlock(const std::string& str) {
		dn_pl_cmd.emplace_back(str);
	}

	template <typename T>
	void printBlock(T obj) {
		std::cout << "bulk: ";
		std::for_each(obj.cbegin(), obj.cend() - 1, [](const std::string& str) {std::cout << str << ","; });
		std::cout << *(obj.cend() - 1) << std::endl;
		

	}
};