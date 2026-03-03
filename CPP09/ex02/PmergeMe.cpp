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
	size_t				size = data->pending.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);
	//std::cout << "[DEQ] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	if (size == 0)
	{
		data->main.push_back(data->pending[i]);
		return ;
	}
	while (i < size)
	{
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "[DEQ] standard; big[i] = " << data->pending[i] << std::endl;
			binaryInsert(data->main, data->pending[i]);
		}
		else
		{
			std::cout << "[DEQ] jacobsthal; big[i] = " << data->pending[i] << std::endl;
			binaryInsert(data->main, data->pending[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
};

void	swap_elements(size_t size, std::deque<unsigned int>::iterator it, std::deque<unsigned int>::iterator ite)
{
	unsigned int	tmpui;

	for (size_t i = 0; i < size; i ++)
	{	
		tmpui = *it;
		*it = *ite;
		*ite = tmpui;

		it ++;
		ite ++;
	}
}

void	sortPairs(size_t size, t_dataDeq *data)
{
	std::cout << "entered sort pairs with size = " << size << std::endl;
	for (std::deque<unsigned int>::iterator it = data->container.begin(); it + size / 2 < data->container.end(); it += size)
	{
		std::deque<unsigned int>::iterator ite = it + size - 1;
		if (*(it + size / 2 - 1) > *(ite))
		{
			std::cout << "must swap it = " << *(it + size / 2 - 1) << " and ite = " << *(ite) << std::endl;
			swap_elements(size / 2, it, it + size / 2);
		}
	}
	std::cout << "exits sort pairs = ";
	printContainer(data->container);
}

void	swapping(size_t size, t_dataDeq *data)
{
	if (size / 2 > 1)
	{
		swapping(size / 2, data);
	}
	size_t	fixedSize = size;
	if (size % 2 != 0)
		fixedSize --;
	sortPairs(fixedSize, data);
}

void	formMainAndPending(size_t size, size_t fixedSize, t_dataDeq *data)
{
	//main = 'b1' puis tous les 'a' : premier bloc, deuxième bloc, puis un sur deux (4ème, 6ème...)
	//pending = tous les autres 'b' : troisième bloc, puis un sur sur deux (5ème, 7ème...)

	std::deque<unsigned int>::iterator it = data->container.begin();
	std::deque<unsigned int>::iterator ite = data->container.begin() + fixedSize;

	if (fixedSize < size)
		data->remaining.insert(data->remaining.end(), ite, data->container.end());

	if (size == data->container.size() || size == data->container.size() / 2)
	{
		data->main.insert(data->main.end(), it, ite);
		std::cout << "hey" << std::endl;
		return ;
	}

	size_t half = fixedSize / 2;
	data->main.insert(data->main.end(), it, it + half * 2);
	data->pending.insert(data->pending.end(), it + half * 2, it + half * 3);
	
	std::deque<unsigned int>::iterator begin = data->container.begin();
	size_t	n = 3;
	for (it = begin + half * n; it != ite; it += fixedSize)
	{
		n ++;
		if (begin + half * n != ite)
		{
			std::cout << "maiiiiiiiin" << std::endl;
			data->main.insert(data->main.end(), it, it + half); // segfault
			std::cout << "pendiiiiing" << std::endl;
			data->pending.insert(data->pending.end(), it + half, it + half * 2);
		}
		std::cout << "n = " << n << std::endl;
	}
	std::cout << "remaining after formmainpending = ";
	printContainer(data->remaining);
}

void	merging(size_t size, t_dataDeq *data)
{
	if (size / 2 > 1)
	{
		size_t	fixedSize = size;
		size_t	n = 2;
		while (n * 2 < size)
			n *= 2;
		if (n * 2 > size)
			fixedSize = n;
		std::cout << "entered merging with size = " << size << " and fixedSize = " << fixedSize << std::endl;
		formMainAndPending(size, fixedSize, data);
		jacobsthalInsert(data);
		/*size_t	n = data->remaining.size();
		if (n)
		{
			data->pending.insert(data->remaining.end(), data->remaining.begin(), data->remaining.begin() + n);
		}*/
		merging(size / 2, data);
	}
}

void		PmergeMe::sortDequeue(t_dataDeq *data)
{
	size_t	size = data->container.size();

	swapping(size, data);
	std::cout << "container after swapping = ";
	printContainer(data->container);

	merging(size, data);
	std::cout << "container after merging = ";
	printContainer(data->container);

	binaryInsert(data->container, data->remaining[0]);
}
