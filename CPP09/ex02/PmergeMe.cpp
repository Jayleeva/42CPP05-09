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
	while (i + 1 < size)
	{
		if (i == 0 && ui < this->small[i])
		{
			this->small.insert(this->small.begin(), ui);
			return ;
		}
		if (ui > this->small[i] && ui < this->small[i + 1])
		{
			this->small.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (i == size && ui > this->small[i])
	{
		this->small.push_back(ui);
		return ;
	}
}

void	PmergeMe::splitBigSmall(std::vector<unsigned int>&current)
{
	size_t	size = current.size();

	this->big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			binaryInsertSmall(current[i]);
			this->big.push_back(current[i + 1]);
		}
		else
		{
			binaryInsertSmall(current[i + 1]);
			this->big.push_back(current[i]);
		}
		i += 2;
	}
	if (i < size)
		binaryInsertSmall(current[size]);
	current.clear();
	current = this->big;
}

void	PmergeMe::mergePairs(size_t size, std::vector<unsigned int>&current)
{
	if (size / 2 > 1)
		this->mergePairs(size / 2, current);
	this->splitBigSmall(current);
}

void	PmergeMe::jacobsthalBinaryInsert(size_t i, size_t size, int jacbosthal)
{
	unsigned int	ui = this->big[jacbosthal];

	std::vector<unsigned int>::iterator it = this->container.begin() + i;
	while (i + 1 < size)
	{
		if (i == 0 && ui < this->big[i])
		{
			this->container.insert(this->container.begin(), ui);
			return ;
		}
		if (ui > this->container[i] && ui < this->container[i + 1])
		{
			this->container.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (i == size && ui > this->big[i])
	{
		this->container.push_back(ui);
		return ;
	}
}

void	PmergeMe::standardBinaryInsert(size_t i, size_t size, unsigned int ui)
{
	std::vector<unsigned int>::iterator it = this->container.begin() + i;
	while (i + 1 < size)
	{
		if (i == 0 && ui < this->big[i])
		{
			this->container.insert(this->container.begin(), ui);
			return ;
		}
		if (ui > this->container[i] && ui < this->container[i + 1])
		{
			this->container.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (i == size && ui > this->big[i])
	{
		this->container.push_back(ui);
		return ;
	}
}

void	PmergeMe::binaryInsertBig()
{
	std::deque<size_t>	jacobsthal(1, 3);
	size_t			size = this->big.size();
	size_t			i = 0;

	this->container.clear();
	this->container = this->small;

	if (size == 0)
	{
		this->container.push_back(this->big[i]);
		return ;
	}

	while (i + 1 < size)
	{
		if (jacobsthal[1] - jacobsthal[0] > size - i)
		{
			this->standardBinaryInsert(i, size, this->big[i]);
			return ;
		}
		this->jacobsthalBinaryInsert(i, size, jacobsthal[1]);
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
}

void	PmergeMe::sortContainer()
{
	this->mergePairs(this->container.size(), this->container);
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