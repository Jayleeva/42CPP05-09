#include "RPN.hpp"


// TEST: ./RPN "3 2 4 8 + - + 1 5 - 4 3 1 2 - + + + -"
// 3 1 2 4 - - 3
int main(int argc, char **argv)
{
	RPN	container;

	if (argc != 2)
	{
		std::cerr << "Error : please enter a reverse polish expression in one string." << std::endl;
		return (1);
	}

	try
	{
		container.setQueue(std::string(argv[1]));
		container.printRes();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}