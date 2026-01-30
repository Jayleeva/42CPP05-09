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

void	PmergeMe::formPairs()
{
	size_t	size = this->container.size();

	size_t	i = 0;
	while (i + 1 < size)
	{
		if (this->container[i] < this->container[i + 1])
		{
			this->small.push_back(this->container[i]);
			this->big.push_back(this->container[i + 1]);
		}
		else
		{
			this->small.push_back(this->container[i + 1]);
			this->big.push_back(this->container[i]);
		}
		i += 2;
	}
	if ()
		this->leftover.push_back();
}
void	PmergeMe::mergePairs()
{

}
void	PmergeMe::insertBigInSmall()
{

}
void	PmergeMe::insertLeftover()
{

}


void	PmergeMe::sortContainer()
{

	//this->formPairs();
	
	if ()
	{
		this->mergePairs();
		this->sortContainer();
	}
	this->insertBigInSmall();
	//this->insertLeftover();
}

void	PmergeMe::printContainer()
{
	size_t	size = this->container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		std::cout << this->container[i] << ' ';
	}
	std::cout << this->container[size -1] << std::endl;
}