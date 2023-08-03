#pragma once
#include <string>
#include <algorithm>
#include <vector>

using PulBlock = std::vector<std::string>;
using Iter = std::vector< std::string >::const_iterator;

class Block {
private:
	PulBlock pul_cmd;
	size_t size;
public:
	explicit Block(int& count) :size(0) {
		pul_cmd.reserve(count);
	}
	void addCmd(std::string& cmd) {
		if (cmd != "EOF")
			pul_cmd.push_back(cmd);
	}
	size_t size() { return pul_cmd.size(); }
};