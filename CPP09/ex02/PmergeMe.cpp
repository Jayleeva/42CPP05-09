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

t_dataVec	PmergeMe::getDataVec() const
{
	return (this->dataVec);
}

t_dataDeq	PmergeMe::getDataDeq() const
{
	return (this->dataDeq);
}

void	PmergeMe::setDataVec(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

void	PmergeMe::setDataDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

/*void	PmergeMe::setVector(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end)
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
}*/


template<typename T>
void	standardBinaryInsert(T *container, unsigned int ui)
{
	size_t			i = 0;

	if (container.size() == 0)
	{
		container.push_back(ui);
		return ;
	}

	if (ui < container[0])
	{
		container.insert(container.begin(), ui);
		return ;
	}
	T::iterator it = container.begin() + i;
	while (i + 1 < container.size())
	{
		if (ui > container[i] && ui < container[i + 1])
		{
			small.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > container[container.size() -1] && ui < container[container.size()])
	{
		container.insert(it + 1, ui);
		return ;
	}
	if (ui > container[container.size()])
	{
		container.push_back(ui);
		return ;
	}
	std::cout << "not inserted" << std::endl;
}


template<typename T, typename Tdata>
void	splitBigSmall(T *current, Tdata *data, char type)
{
	size_t	size = current.size();

	data->big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			standardBinaryInsert(data->small, current[i]);
			data->big.push_back(current[i + 1]);
		}
		else
		{
			standardBinaryInsert(data->small, current[i + 1]);
			data->big.push_back(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		standardBinaryInsert(data->small, current[i]);
		i++;
	}
	current.clear();
	current = data->big;
}

template<typename T, typename Tdata>
void	mergePairs(size_t size, T *current, Tdata *data, char type)
{
	if (size / 2 > 1)
		mergePairs(size / 2, current, data, type);
	splitBigSmall(current, data, type);
}


template<typename Tdata>
void	jacobsthalBinaryInsert(Tdata *data)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = data->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_back(1);
	jacobsthal.push_back(3);

	if (size == 0)
	{
		data->container.push_back(data->big[i]);
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
			standardBinaryInsert(data->small, data->big[i]);
		}
		else
		{
			std::cout << "jacobsthal" << std::endl;
			standardBinaryInsert(data->small, data->big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	data->container.clear();
	data->container = data->small;
}


template<typename Tdata>
void	PmergeMe::sortContainer(Tdata *data, char type)
{
	mergePairs(data->container.size(), data->container, data, type);
	jacobsthalBinaryInsert(data);
}


template<typename Tdata>
void	PmergeMe::printContainer(Tdata *data)
{
	size_t	size = data->container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		std::cout << data->container[i] << ' ';
	}
	std::cout << data->container[size -1] << std::endl;
}