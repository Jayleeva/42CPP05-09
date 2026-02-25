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
		this->dataVec.container = original.dataVec.container;
		this->dataDeq.container = original.dataDeq.container;
	}
	std::cout << YELLOW << "[PMERGEME] : Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default destructor called" << DEFAULT << std::endl;
}

std::vector<unsigned int>	PmergeMe::getVector() const
{
	return (this->dataVec.container);
}

void	PmergeMe::setVector(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

std::deque<unsigned int>	PmergeMe::getDeque() const
{
	return (this->dataDeq.container);
}

void	PmergeMe::setDeque(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

template<typename T>
void	PmergeMe::binaryInsertSmall(unsigned int ui)
{
	size_t	i = 0;

	if (this->small.size() == 0)
	{
		this->small.push_back(ui);
		return ;
	}

	if (ui < this->small[0])
	{
		this->small.insert(this->small.begin(), ui);
		return ;
	}
	std::vector<unsigned int>::iterator it = this->small.begin();
	while (i + 1 < this->small.size())
	{
		if (ui > this->small[i] && ui < this->small[i + 1])
		{
			this->small.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > this->small[this->small.size() -1])
	{
		//std::cout << "dernier " << ui << std::endl;
		this->small.push_back(ui);
		return ;
	}
}

template<typename T>
void	print_small(T small)
{
	size_t	size2 = small.size();
	std::cout << "small (size: " << size2 << ") = ";
	for (size_t i = 0; i < size2 -1 ; i++)
	{
		std::cout << small[i] << ' ';
	}
	std::cout << small[size2 -1] << std::endl;
}

template<typename T>
void	PmergeMe::splitBigSmall(T &current)
{
	size_t	size = current.size();

	this->big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			binaryInsertSmall(current[i]);
			//print_small(this->small);
			this->big.push_back(current[i + 1]);
		}
		else
		{
			binaryInsertSmall(current[i + 1]);
			//print_small(this->small);
			this->big.push_back(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		binaryInsertSmall(current[i]);
		i++;
	}
	current.clear();
	current = this->big;
	/*size_t	size2 = this->big.size();

	for (size_t i = 0; i < size2 -1 ; i++)
	{
		std::cout << this->big[i] << ' ';
	}
	std::cout << this->big[size2 -1] << std::endl;*/
}

template<typename T>
void	PmergeMe::mergePairs(size_t size, T &current)
{
	if (size / 2 > 1)
		this->mergePairs(size / 2, current);
	this->splitBigSmall(current);
}

template<typename T>
void	PmergeMe::standardBinaryInsert(unsigned int ui)
{
	size_t			i = 0;

	if (ui < this->small[0])
	{
		this->small.insert(this->small.begin(), ui);
		return ;
	}
	std::vector<unsigned int>::iterator it = this->small.begin() + i;
	while (i + 1 < this->small.size())
	{
		if (ui > this->small[i] && ui < this->small[i + 1])
		{
			this->small.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > this->small[this->small.size() -1] && ui < this->small[this->small.size()])
	{
		this->small.insert(it + 1, ui);
		return ;
	}
	if (ui > this->small[this->small.size()])
	{
		this->small.push_back(ui);
		return ;
	}
	std::cout << "not inserted" << std::endl;
}

template<typename T>
void	PmergeMe::binaryInsertBig()
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = this->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);


	if (size == 0)
	{
		this->container.push_back(this->big[i]);
		return ;
	}
	while (i < size)
	{
		std::cout << "i = " << i << std::endl;
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "standard" << std::endl;
			this->standardBinaryInsert(this->big[i]);
		}
		else
		{
			std::cout << "jacobsthal" << std::endl;
			this->standardBinaryInsert(this->big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	this->container.clear();
	this->container = this->small;
}

template<typename T>
void	PmergeMe::sortContainer(T &container)
{
	this->mergePairs(container.size(), container);
	this->binaryInsertBig();
}

template<typename T>
void	printContainer(T &container)
{
	size_t	size = container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		std::cout << container[i] << ' ';
	}
	std::cout << container[size -1] << std::endl;
}