#include <iostream>

int main(int argc, char* argv[])
{
	char* com_val;
	if (argc <= 1) {
		std::cout << "The number of processed commands is not specified" << std::endl;
		exit(1);
	}
	else
		com_val = argv[1];
	std::cout << com_val << std::endl;

	return 0;
}
