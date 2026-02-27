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

template <typename T>
void	swap_elements(T &a, T &b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	formSortedPairs(std::deque<unsigned int> &container, t_dataDeq *data)
{
	if (container.size() % 2 != 0)
	{
		data->remaining.push_back(container[container.size()]);
		container.erase(container.end());
	}

	size_t	i = 0;
	while (i + 1 < container.size())
	{
		if (container[i] > container[i + 1])
			swap_elements(container[i], container[i + 1]);
		std::pair<unsigned int, unsigned int> tmp(container[i], container[i + 1]);
		data->pairs.push_back(tmp);
		i += 2;
	}
	/*for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = data->pairs.begin(); it != data->pairs.end(); ++it)
	{
		if (it->first > it->second)
			swap_elements(it->first, it->second);
	}*/
}

/*void	inplaceMerge(size_t n, std::deque<unsigned int> &current, t_dataDeq *data)
{

}

void	mergeSort(size_t size, std::deque<unsigned int> &current, t_dataDeq *data)
{
	if (size / 2 > 1)
		mergeSort(size / 2, current, data);
	inplaceMerge(current, data);
}*/

bool must_swap(std::pair<unsigned int, unsigned int> a, std::pair<unsigned int, unsigned int> b)
{
	if (a.second < b.second)
		return (1);
	return (0);
}

void mergeSort2(std::deque<std::pair<unsigned int, unsigned int> >::iterator start, std::deque<std::pair<unsigned int, unsigned int> >::iterator end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return;

	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	std::deque<std::pair<unsigned int, unsigned int> >::iterator center = start + firstHalf;

	mergeSort2(start, center, firstHalf);
	mergeSort2(center, end, secondHalf);
	std::inplace_merge(start, center, end, &must_swap);
}


void	formMainAndPending(t_dataDeq *data)
{
	size_t	i = 0;
	while (i < data->pairs.size())
	{
		data->pending.push_back(data->pairs[i].first);
		data->main.push_back(data->pairs[i].second);
		i ++;
	}
}


/*void	binaryInsert(std::deque<int> &container, std::deque<int>::iterator end, int val)
{
	std::deque<int>::iterator it = std::lower_bound(container.begin(), end, val);
	container.insert(it, val);
}*/

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

void		PmergeMe::sortDequeue(t_dataDeq *data)
{
	size_t	size = data->container.size();
	data->nlvl = 1; // si 1, ne rentre jamais dans jacobsthal, marche la plupart du temps mais pas toujours.
	while (size / 2 > 1)
	{
		size /= 2;
		data->nlvl ++;
	}
	std::cout << "[DEQ] n = " << data->nlvl << std::endl;
	formSortedPairs(data->container, data);
	printContainer(data->container);
	//mergeSort(data->nlvl, data->container, data);
	mergeSort2(data->pairs.begin(), data->pairs.end(), 0);

	formMainAndPending(data);
	/*std::cout << "pending = ";
	printContainer(data->pending);
	std::cout << "main = ";
	printContainer(data->main);*/

	jacobsthalInsert(data);
	data->container.clear();
	data->container = data->main;
}
