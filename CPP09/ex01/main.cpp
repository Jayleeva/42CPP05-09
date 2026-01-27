#include "RPN.hpp"


int main(int argc, char **argv)
{
	RPN	stack;

	if (argc != 2)
		return (1);
	
	stack.setQueue(std::string(argv[1]));
	stack.printRes();
	return (0);
}