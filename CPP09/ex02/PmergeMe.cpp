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
		//this->dataDeq.container = original.dataDeq.container;
	}
	std::cout << YELLOW << "[PMERGEME] : Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default destructor called" << DEFAULT << std::endl;
}


std::deque<unsigned int>	PmergeMe::getDeq() const
{
	return (this->container);
}

void	PmergeMe::setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->container.insert(this->container.end(), begin, end);
}

/*t_dataVec	PmergeMe::getDataVec() const
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
}*/


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
	std::cout << "[DEQ] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	/*if (size == 0)
	{
		data->main.push_back(data->pending[i]);
		return ;
	}*/
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
			std::cout << "[DEQ] jacobsthal; big[i] = " <<  data->pending[jacobsthal[1]] << std::endl;
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

void	sortPairs(size_t size, std::deque<unsigned int>	&container, std::deque<unsigned int>::iterator max_)
{
	for (std::deque<unsigned int>::iterator it = container.begin(); it + size / 2 < max_; it += size)
	{
		std::deque<unsigned int>::iterator ite = it + size - 1;
		if (*(it + size / 2 - 1) > *(ite))
		{
			//std::cout << "must swap it = " << *(it + size / 2 - 1) << " and ite = " << *(ite) << std::endl;
			swap_elements(size / 2, it, it + size / 2);
		}
	}
}

void	swapping(size_t size, std::deque<unsigned int> &container)
{
	size_t	fixedSize = size;

	if (size / 2 > 1)
		swapping(size / 2, container);

	size_t	n = 2;
	while (n * 2 < fixedSize)
		n *= 2;
	if (n * 2 > fixedSize)
		fixedSize = n;

	if (size % 2 != 0)
		sortPairs(fixedSize, container, container.end() - size / 2);
	else
		sortPairs(fixedSize, container, container.end() - size / 2 + 1);
	//std::cout << "after sortpairs of size = " << size << ": \n   ";
	//printContainer(container);
}

std::deque<unsigned int>	copy_deque(std::deque<unsigned int> deq)
{
	std::deque<unsigned int>	res;
	res.insert(res.end(), deq.begin(), deq.end() -1);
	return (res);
}

std::deque<unsigned int>	mergeMainAndPending(t_dataDeq *data, bool must_insert)
{
	std::deque<unsigned int>	merged;

	if (must_insert)
	{
		std::cout << "FUCKING MERGE OMFG" << std::endl;
		jacobsthalInsert(data);
	}
		
	if (data->remaining.size())
	{
		std::cout << "insert remaining" << std::endl; // on rentre pas
		data->main.insert(data->main.end(), data->remaining.begin(), data->remaining.end());
	}

	merged.insert(merged.end(), data->main.begin(), data->main.end());
	return (merged);
}

std::deque<unsigned int>	formMainAndPending(size_t size, size_t fixedSize, std::deque<unsigned int> &current) // t_dataDeq *data) //, )
{
	//main = 'b1' puis tous les 'a' : premier bloc, deuxième bloc, puis un sur deux (4ème, 6ème...)
	//pending = tous les autres 'b' : troisième bloc, puis un sur sur deux (5ème, 7ème...)
	t_dataDeq	data_;
	std::deque<unsigned int>	res;
	std::deque<unsigned int>::iterator it = current.begin();
	std::deque<unsigned int>::iterator ite = current.begin() + fixedSize;

	if (fixedSize < size) // marche pas quand sequence est paire de base?
	{
		//std::cout << "remainiiiiiing" << std::endl;
		data_.remaining.insert(data_.remaining.end(), ite, current.end());
		std::cout << "remaining after formmainpending = ";
		printContainer(data_.remaining);
	}

	static size_t	n = 1;
	if (n < 3) // size == current.size() || size == current.size() / 2 )
	{
		data_.main.insert(data_.main.end(), it, ite);
		//std::cout << "FIRST / SECOND : size = " << size << " container.size() = " << current.size() << " half container = " << current.size() /2 << std::endl;
		//std::cout << "main after base = ";
		//printContainer(data_.main);
		n ++;
		res = mergeMainAndPending(&data_, 0);
		return (res);
	}

	size_t half = fixedSize / 2;
	data_.main.insert(data_.main.end(), it, it + half * 2);
	data_.pending.insert(data_.pending.end(), it + half * 2, it + half * 3);
	
	std::cout << "[MAIN] after base insert = ";
	printContainer(data_.main);
	std::cout << "[PENDING] after base insert = ";
	printContainer(data_.pending);

	std::deque<unsigned int>::iterator begin = current.begin();
	for (it = begin + half * n; it < ite; it += fixedSize)
	{
		n ++;
		if (begin + half * n != ite)
		{
			std::cout << "maiiiiiiiin" << std::endl;
			data_.main.insert(data_.main.end(), it, begin + half * n); // segfault
			std::cout << "pendiiiiing" << std::endl;
			data_.pending.insert(data_.pending.end(), begin + half * n, begin + half * (n + 1));
		}
		//std::cout << "n = " << n << std::endl;
	}
	res = mergeMainAndPending(&data_, 1);
	return (res);
}

void	merging(size_t size, std::deque<unsigned int> &container) //, std::deque<unsigned int> &current)
{
	t_dataDeq	data_;

	if (size / 2 > 1)
	{
		size_t	fixedSize = size;
		size_t	n = 2;
		while (n * 2 < size)
			n *= 2;
		if (n * 2 > size)
			fixedSize = n;
		std::cout << "entered merging with size = " << size << " and fixedSize = " << fixedSize << std::endl;
		container = formMainAndPending(size, fixedSize, container);
		std::cout << "merged container = ";
		printContainer(container);
		//data_ = formMainAndPending(size, fixedSize, container);
		//container = mergeMainAndPending(&data_);
		//container = copy_deque(data_.main);
		merging(size / 2, container); //, data->main);
	}
}

void		PmergeMe::sortDequeue()
{
	size_t	size = this->container.size();

	swapping(size, this->container);
	std::cout << "container after swapping = ";
	printContainer(this->container);

	merging(size, this->container); //, data->container);
	std::cout << "container after merging = ";
	printContainer(this->container);

	//binaryInsert(container, data->remaining[0]);
}
