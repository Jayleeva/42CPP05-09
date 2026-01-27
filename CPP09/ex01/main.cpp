#include "RPN.hpp"


int	is_in_set(char c, std::string set)
{
	for (int i = 0; set[i]; i ++)
	{
		if (set[i] == c)
			return (1);
 	}
	return (0);
}

int main(int argc, char **argv)
{
	RPN	stack;

	if (argc != 2)
		return (1);
	
	stack.setQueue(std::string(argv[1]));
	stack.printRes();
	return (0);
}