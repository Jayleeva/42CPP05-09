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

std::vector<unsigned int>	PmergeMe::getVector() const
{
	return (this->dataVec.container);
}

std::deque<unsigned int>	PmergeMe::getDeque() const
{
	return (this->dataDeq.container);
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
void	pushToContainer(T *container, char type, unsigned int ui)
{
	if (type == 'v')
		container.push_back(ui);
	else if (type == 'd')
		container.push_front(ui);
}

template<typename T>
void	binaryInsertSmall(unsigned int ui, T *small, char type)
{
	size_t	i = 0;

	if (small.size() == 0)
	{
		pushToContainer(small, type, ui);
		return ;
	}

	if (ui < small[0])
	{
		small.insert(small.begin(), ui);
		return ;
	}
	T::iterator it = small.begin();
	while (i + 1 < small.size())
	{
		if (ui > small[i] && ui < small[i + 1])
		{
			small.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > small[small.size() -1])
	{
		//std::cout << "dernier " << ui << std::endl;
		pushToContainer(small, type, ui);
		return ;
	}
}


template<typename T>
void	splitBigSmall(T *current, T *big, char type)
{
	size_t	size = current.size();

	big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			binaryInsertSmall(current[i]);
			if (type == 'v')
				big.push_back(current[i + 1]);
			else if (type == 'd')
				big.push_front(current[i + 1]);
		}
		else
		{
			binaryInsertSmall(current[i + 1]);
			if (type == 'v')
				big.push_back(current[i]);
			else if (type == 'd')
				big.push_front(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		binaryInsertSmall(current[i]);
		i++;
	}
	current.clear();
	current = big;
}

template<typename T, typename Tdata>
void	mergePairs(size_t size, T *current, T *big, char type)
{
	if (size / 2 > 1)
		mergePairs(size / 2, current, big, type);
	splitBigSmall(current, big, type);
}

template<typename T>
void	standardBinaryInsert(unsigned int ui)
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

template<typename Tdata>
void	binaryInsertBig(Tdata *data)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = data->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);

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
			standardBinaryInsert(data->big[i]);
		}
		else
		{
			std::cout << "jacobsthal" << std::endl;
			standardBinaryInsert(data->big[jacobsthal[1]]);
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
	mergePairs(data->container.size(), data->container, data->big, type) // data->container.size(), data->container);
	binaryInsertBig(data);
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