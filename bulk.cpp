#include <iostream>
#include <string>
#include <algorithm>
#include "ComandDistr.h"

using StaticPullBlock = std::vector<std::string>;
using DynamicPullBlock = std::deque<std::string>;

struct Cmd {
private:
	std::time_t time;
	std::string name_cmd;
public:
	Cmd(std::string& com) :
		name_cmd(com),
		time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}
	std::string getName() { return name_cmd; }
	std::time_t getTime() { return time; }
};


class Receiver {
private:
	StaticPullBlock st_pl_cmd;
	DynamicPullBlock dn_pl_cmd;
	size_t scope_block;
	bool is_open;

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
	std::string getNameFile() {
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string name = "bulk" + std::to_string(time) + ".log";
		return name;
	}

public:
	explicit Receiver(int& count) :scope_block(0), is_open(false) {
		st_pl_cmd.reserve(count);
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
};

class Command {
protected:
	Receiver* res;
	Command(Receiver& r) :res(r) {};
public:
	virtual void execute() const = 0;
	virtual ~Command() {};

};

class WriteToConsol :public Command {
public:
	explicit WriteToConsol(Receiver& r) :Command(r) {};
	void execute() const override {};
};

class WriteToFile :public Command {
public:
	explicit WriteToFile(Receiver& r) :Command(r) {};
	void execute() const override {};
};

//class ReadFromConsol :public Command {
//	explicit ReadFromConsol(std::string& cmd) {}
//	void execute() const override {}
//	void executeUnDo() override {}
//};


class Invoker {
public:
	Invoker(Command* com) {
		com->execute();
	};
};

	class Client {
	private:
		Receiver* res;

	public:
		explicit Client(Receiver* r) :res(r) {}
		void run(std::string& cmd) {
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


		return 0;
	}
