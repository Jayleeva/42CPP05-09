#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN	container;

	if (argc != 2)
		return (1);
	
	container.setQueue(std::string(argv[1]));
	try 
	{
		container.printRes();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}