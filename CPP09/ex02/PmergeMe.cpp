#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default constructor called" << DEFAULT << std::endl;
}

PmergeMe::PmergeMe(PmergeMe const &original)
{
	std::cout << YELLOW << "[PMERGEME] : Copy constructor called" << DEFAULT << std::endl;
	*this = original;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &original)
{
	if (this != &original)
	{
		this->container = original.container;
	}
	std::cout << YELLOW << "[PMERGEME] : Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default destructor called" << DEFAULT << std::endl;
}


std::vector<unsigned int>	PmergeMe::getContainer() const
{
	return (this->container);
}

void	PmergeMe::setContainer(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	this->container.insert(this->container.end(), begin, end);
}


void	PmergeMe::sortContainer()
{
	if (merge_(this->container))
	{
		this->container = insert_(this->container);
		this->sortContainer();
	}
}

void	PmergeMe::printContainer()
{
	size_t	size = this->container.size();

	for (int i = 0; i < size -2 ; i++)
	{
		std::cout << this->container[i] << ' ';
	}
	std::cout << this->container[size -1] << std::endl;
}