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
	//static	size_t						rank = 2;
	//std::vector<unsigned int>::iterator it;
	//std::vector<unsigned int>::iterator first;
	//std::vector<unsigned int>::iterator middle;
	//std::vector<unsigned int>::iterator last;
	size_t								size = this->container.size();


	//size_t n = sqrt(size);
	//std::cout << "size = " << size << " n = " << n << std::endl;

	size_t	i = 0;
	while (size / 2 > 1)
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
		size /= 2;
	}

	/*for (it = this->container.begin(); ; it++)
	{
		std::vector<unsigned int> pair;

	}

	std::vector<unsigned int>			tmp_small;

	size_t n = sqrt(size);
	while (n > 0)
	{
		std::cout << n << std::endl;
		n --;
	}

	if (size > 1)
	{
		first = this->container.begin();
		middle = this->container.begin() + size / 2;
		//this->container.erase(first, middle);
		size /= rank;
		rank += 2;
		this->sortContainer();
	}

	{
		first = this->container.begin();
		middle = this->container.begin() + this->container.size() / 2;
		if (size % rank == 0)
			last = this->container.end();
		else
			last = this->container.end() - size % rank;

		this->small.insert(this->small.end(), first, middle);
		this->big.insert(this->big.end(), middle + 1, last);

		this->container.erase(first, last);

		if (this->container.size() > 0)
			this->leftover.insert(this->leftover.end(), this->container.begin(), this->container.end());

		rank += 2;

		//merge_small(this, 0, size / 2);
		//merge_big(this, size / 2, size);
		insert_big_in_small();
		insert_leftover();
		this->sortContainer();
	}*/
	return;
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