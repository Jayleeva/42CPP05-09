#include "MutantStack.hpp"

MutantStack::MutantStack()
{
    std::cout << YELLOW << "[MUTANT]: Default constructor called" << DEFAULT << std::endl;
}

MutantStack::MutantStack(MutantStack const &original)
{
	*this = original;
    std::cout << YELLOW << "[MUTANT]: Copy constructor called" << DEFAULT << std::endl;
}

MutantStack &MutantStack::operator=(MutantStack const &original)
{
	if (this != &original)
	{

	}
    std::cout << YELLOW << "[MUTANT]: Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

MutantStack::~MutantStack()
{
    std::cout << YELLOW << "[MUTANT]: Default destructor called" << DEFAULT << std::endl;
}