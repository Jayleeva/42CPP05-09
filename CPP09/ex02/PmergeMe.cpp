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


void	PmergeMe::binaryInsertSmall(unsigned int ui)
{
	size_t	size = this->small.size();
	size_t	i = 0;

	if (size == 0)
	{
		this->small.push_back(ui);
		return ;
	}

	std::vector<unsigned int>::iterator it = this->small.begin();
	while (i < size)
	{
		if (ui < this->small[i])
		{
			this->small.insert(it, ui);
			return ;
		}
		else
		{
			this->small.push_back(ui);
			return ;
		}
		it++;
		i++;
	}
}

void	PmergeMe::splitBigSmall()
{
	size_t	size = this->current.size();

	size_t	i = 0;
	while (i + 1 < size)
	{
		if (this->current[i] < this->current[i + 1])
		{
			binaryInsertSmall(this->current[i]);
			this->big.push_back(this->current[i + 1]);
		}
		else
		{
			binaryInsertSmall(this->current[i + 1]);
			this->big.push_back(this->current[i]);
		}
		i += 2;
	}
	if (i < size)
		binaryInsertSmall(this->current[size]);
	this->current.clear();
	this->current = this->big;
}

void	PmergeMe::mergePairs(size_t size)
{
	if (size / 2 > 1)
		this->mergePairs(size / 2);
	this->splitBigSmall();
}

void	PmergeMe::binaryInsertBig()
{

}


void	PmergeMe::sortContainer()
{
	this->current = this->container;
	this->mergePairs(this->current.size());
	this->binaryInsertBig();
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