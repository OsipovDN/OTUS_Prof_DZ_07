#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <chrono>
#include <fstream>

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
		DynamicPullBlock temp;
		while (std::getline(std::cin, cmd)) {
			if (isScope(cmd)) {
				if (st_pl_cmd.size() != 0 && is_open) {
					saveBlock(st_pl_cmd);
					printBlockToStream(std::cout, st_pl_cmd);
					st_pl_cmd.clear();
				}
				else if (scope_block == 0 && !is_open) {
					addDynBlock(temp);
					saveBlock(dn_pl_cmd);
					printBlockToStream(std::cout, dn_pl_cmd);
					dn_pl_cmd.clear();
				}
				continue;
			}
			if (scope_block == 0 && dn_pl_cmd.size() == 0) {
				addStBlock(cmd);
			}
			else {
				temp.emplace_back(cmd);
			}
		}
		if (st_pl_cmd.size() != 0) {
			saveBlock(st_pl_cmd);
			printBlockToStream(std::cout, st_pl_cmd);
			st_pl_cmd.clear();
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
		if (st_pl_cmd.size() != st_pl_cmd.capacity()) {
			st_pl_cmd.emplace_back(str);
		}
		if (st_pl_cmd.size() == st_pl_cmd.capacity()) {
			saveBlock(st_pl_cmd);
			printBlockToStream(std::cout, st_pl_cmd);
			st_pl_cmd.clear();
		}
	}

	void addDynBlock(DynamicPullBlock& obj) {
		for (const auto& it : obj)
			dn_pl_cmd.emplace_back(it);
		obj.clear();
	}

	template <typename T>
	bool saveBlock(T obj) {
		std::string name = getNameFile();
		std::ofstream file(name);
		if (!file.is_open()) {
			std::cout << "file is not open!" << std::endl;
			return false;
		}
		else {
			printBlockToStream <std::ofstream, T>(file, obj);
			return true;
		}

	}

	template <typename T, typename U>
	void printBlockToStream(T& stream, const U& obj) {
		stream << "bulk: ";
		std::for_each(obj.cbegin(), obj.cend() - 1, [&stream](const std::string& str) {
			stream << str << ",";
			});
		stream << *(obj.cend() - 1) << std::endl;
	}



	std::string getNameFile() {
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string name = "bulk" + std::to_string(time) + ".log";
		return name;
	}
};