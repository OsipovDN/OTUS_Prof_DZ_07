#include <iostream>
#include <string>
#include <algorithm>
#include "ComandDistr.h"

using StaticPullBlock = std::vector<std::string>;
using DynamicPullBlock = std::deque<std::string>;


class Receiver {
private:
	StaticPullBlock st_pl_cmd;
	DynamicPullBlock dn_pl_cmd;
	size_t scope_block;
	bool last_scope;


	void addStBlock(const std::string& str) { st_pl_cmd.emplace_back(str); }
	void addDynBlock(const std::string& str) { dn_pl_cmd.emplace_back(str); }
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

public:
	explicit Receiver(int& count) :scope_block(0) {
		last_scope = false;
		st_pl_cmd.reserve(count);
	}

	void openBlock() {
		scope_block++;
		last_scope = true;
	}
	void closeBlock() {
		scope_block--;
		last_scope = true;
	}
	size_t isStFull() { return st_pl_cmd.size() == st_pl_cmd.capacity(); }
	size_t getDnSize() { return dn_pl_cmd.size(); }
	bool readeToSave() { return last_scope; }
	void addBlock(const std::string& cmd) {
		last_scope = false;
		if (scope_block == 0 && dn_pl_cmd.size() == 0) {
			addStBlock(cmd);
		}
		else
			addDynBlock(cmd);
	}
	void clearBlock() {
		if (!st_pl_cmd.empty())
			st_pl_cmd.clear();
		if (!dn_pl_cmd.empty())
			dn_pl_cmd.clear();
	}
	template <typename T>
	void save(T& out) {
		if (st_pl_cmd.size() != 0) 
			printBlockToStream<T, StaticPullBlock>(out, st_pl_cmd);
		else if (scope_block == 0) 
			printBlockToStream<T, DynamicPullBlock>(out, dn_pl_cmd);

	}



	template <typename T, typename U>
	void printBlockToStream(T& stream, const U& obj) {
		stream << "bulk: ";
		std::for_each(obj.cbegin(), obj.cend() - 1, [&stream](const std::string& str) {
			stream << str << ",";
			});
		stream << *(obj.cend() - 1) << std::endl;
	}
};

class Command {
protected:
	Receiver* res;
	Command(Receiver* r) :res(r) {};
public:
	virtual void execute(const std::string& cmd) = 0;
	virtual ~Command() {};

};

class ReadFromConsol :public Command {
private:
	bool isScope(const std::string& s) {
		bool flag = false;
		if (s == "{") {
			res->openBlock();
			flag = true;
		}
		if (s == "}") {
			res->closeBlock();
			flag = true;
		}
		return flag;
	}
public:
	explicit ReadFromConsol(Receiver* r) :Command(r) {}
	void execute(const std::string& str) override {
		if (!isScope(str))
			res->addBlock(str);
	}

};

class WriteToFile :public Command {
private:
	std::string getNameFile() {
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string name = "bulk" + std::to_string(time) + ".log";
		return name;
	}
public:
	explicit WriteToFile(Receiver* r) :Command(r) {};
	void execute(const std::string& cmd) override {
		if (res->readeToSave() || res->isStFull()) {
			std::string name = getNameFile();
			std::ofstream file(name);
			if (!file.is_open()) {
				std::cout << "file is not open!" << std::endl;
			}
			else {
				res->save<std::ofstream>(file);
			}
		}
	}
};

class WriteToConsol :public Command {
public:
	explicit WriteToConsol(Receiver* r) :Command(r) {};
	void execute(const std::string& cmd) override {
		if (res->readeToSave() || res->isStFull()) {
			res->save<std::ostream>(std::cout);
			res->clearBlock();
		}
	}
};






class Invoker {
private:
	std::vector<Command*> commands;
public:
	void setCommands(Command* com) {
		commands.emplace_back(com);
	};

	void runCommands(std::string& com) {
		for (const auto cmd : commands) {
			cmd->execute(com);
		}
	}
};


bool isDig(char* arg) {
	std::string num = arg;
	auto isdig = [](char ch) {return std::isdigit(ch); };
	return std::all_of(num.cbegin(), num.cend(), isdig);
}

int main(int argc, char* argv[])
{

	if (argc != 2) {
		std::cout << "Incorrect argument input" << std::endl;
		exit(1);
	}
	if (!isDig(argv[1])) {
		std::cout << "Not a val" << std::endl;
		exit(1);
	}

	int count = atoi(argv[1]);
	/*ComandDistr CmdDis(count);
	CmdDis.run();*/

	Receiver* res = new Receiver(count);
	Invoker* inv = new Invoker();
	inv->setCommands(new ReadFromConsol(res));
	inv->setCommands(new WriteToFile(res));
	inv->setCommands(new WriteToConsol(res));
	std::string cmd;

	while (std::getline(std::cin, cmd)) {
		inv->runCommands(cmd);
	}

	delete inv;
	delete res;
	


	return 0;
}
