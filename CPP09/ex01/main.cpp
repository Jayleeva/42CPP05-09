#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN	container;

	if (argc != 2)
	{
		std::cout << "Error : please enter a reverse polish expression in one string." << std::endl;
		return (1);
	}

	try
	{
		container.setQueue(std::string(argv[1]));
		container.printRes();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}