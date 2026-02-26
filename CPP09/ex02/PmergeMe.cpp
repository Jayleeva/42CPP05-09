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
	this->dataDeq.container.insert(this->dataDeq.container.end(), begin, end);
}

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}



void	binaryInsert(std::deque<unsigned int> &container, unsigned int ui)
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
	std::deque<unsigned int>::iterator it = container.begin() + i;
	while (i + 1 < container.size())
	{
		if (ui > container[i] && ui < container[i + 1])
		{
			container.insert(it + 1, ui);
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
	//std::cout << "not inserted" << std::endl;
};



void	jacobsthalInsert(t_dataDeq *data)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = data->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);
	//std::cout << "[DEQ] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	std::cout << "[DEQ] big.size during jac= " << data->big.size() << std::endl;
	//printContainer(data->big);

	if (size == 0)
	{
		data->container.push_back(data->big[i]);
		return ;
	}
	while (i < size)
	{
		std::cout << "[DEQ] i = " << i << std::endl;
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "[DEQ] standard; big[i] = " << data->big[i] << std::endl;
			binaryInsert(data->small, data->big[i]);
		}
		else
		{
			std::cout << "[DEQ] jacobsthal; big[i] = " << data->big[i] << std::endl;
			binaryInsert(data->small, data->big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	data->container.clear();
	data->container = data->small;
};

template <typename T>
void	swap_elements(T &a, T &b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	swapSort(size_t n, std::deque<unsigned int> &current, t_dataDeq *data)
{
	size_t	size;
	std::deque<unsigned int> tmp;
	size_t	elsize = 1;

	size_t	power = n;
	while (power > 0)
	{
		elsize *= 2; 
		power --;
	}

	if (n == 1)
	{
		size = current.size();
		size_t	i = 0;
		while (i + 1 < size)
		{
			std::deque<unsigned int> pair;
			if (n == 1)
			{
				pair.push_back(current[i]);
				pair.push_back(current[i + 1]);
			}
			if (pair[0] > pair[1])
				swap_elements(pair[0], pair[1]);
			tmp.insert(pair.begin(), elsize);
			std::cout << "noot noot" << std::endl;
			i += elsize;
		}
		// ignorer les derniers si sequence "impaire"
	}
	else if (n > 1 && n < data->nlvl)
	{
		size = current.size();
		size_t	i = 0;
		while (i + 1 < size)
		{
			if (current[elsize / 2 + i] > current[elsize + i + 1])
				swap_elements(, );
			std::cout << "ELSE noot noot" << std::endl;
			i += elsize;
		}
		// ignorer les derniers si sequence "impaire"
	}
	current.clear();
	current = tmp;
}


void	mergePairs(size_t n, std::deque<unsigned int> &current, t_dataDeq *data)
{
	if (n > 1)
		mergePairs(--n, current, data);
	//if (size / 2 > 1)
	//	mergePairs(size / 2, current, data);
	swapSort(n, current, data);
}


void		PmergeMe::sortDequeue(t_dataDeq *data)
{
	size_t	size = data->container.size();
	size_t	tmp = size;
	data->nlvl = 1; // si 1, ne rentre jamais dans jacobsthal, marche la plupart du temps mais pas toujours.
	while (tmp / 2 > 1)
	{
		tmp /= 2;
		data->nlvl ++;
	}
	size_t	i = 1;
	while (i < data->nlvl)
	{
		tmp *= 2;
		i ++;
	}
	std::cout << "[DEQ] n = " << data->nlvl << " tmp = " << tmp << std::endl;
	mergePairs(data->nlvl, data->container, data);
	//jacobsthalInsert(data);
}
