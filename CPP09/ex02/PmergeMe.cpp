#include "PmergeMe.hpp"

size_t		g_counter;

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
		//this->vec = original.vec;
		this->deq = original.deq;
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
	return (this->deq);
}

void	PmergeMe::setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->deq.insert(this->deq.end(), begin, end);
}

void	update_jacobsthal(std::deque<size_t> &jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
}

void	swap_elements(size_t blockSize, std::deque<unsigned int>::iterator it, std::deque<unsigned int>::iterator ite)
{
	unsigned int	tmpui;

	for (size_t i = 0; i < blockSize; i ++)
	{	
		tmpui = *it;
		*it = *ite;
		*ite = tmpui;

		it ++;
		ite ++;
	}
}

void	sortPairs(size_t pairSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator max_)
{
	//std::cout << "pairSize = " << pairSize << " max = " << *(max_ -1) << std::endl;
	size_t	i = 0;
	for (std::deque<unsigned int>::iterator it = current.begin(); it + pairSize / 2 < max_; it += pairSize)
	{
		g_counter ++;
		std::deque<unsigned int>::iterator a = it + pairSize / 2 -1;
		std::deque<unsigned int>::iterator b = a + pairSize / 2;
		//std::cout << "a = " << *a << " b = " << *b << std::endl;
		if (*(a) > *(b))
		{
			swap_elements(pairSize / 2, it, it + pairSize / 2);				
		}
		i += pairSize;
	}
}

std::deque<unsigned int>::iterator getIte(std::deque<unsigned int> &current, size_t pairSize)
{
	std::deque<unsigned int>::iterator	ite;

	size_t	npairs = current.size() / pairSize;
	size_t	remaining = current.size() - npairs * pairSize;

	ite = current.end() - remaining;
	//std::cout << "ite = " << *(ite -1) << std::endl;
	return (ite);
}

size_t	swapping(size_t pairSize, size_t size, std::deque<unsigned int> &current)
{
	while (size / pairSize >= 1)
	{
		sortPairs(pairSize, current, getIte(current, pairSize));
		//std::cout << "sorted = ";
		//printContainer(current, pairSize / 2);
		pairSize *= 2;
	}
	return (pairSize);
}


std::deque<size_t>	formMainAndPending(t_dataDeq *data, size_t blockSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite)
{
	std::deque<size_t>	indexes;
	std::deque<unsigned int>::iterator	it = current.begin();
	size_t				i = blockSize;

	while (it != ite)
	{
		data->pending.insert(data->pending.end(), it, it + blockSize);
		it += blockSize;
		data->main.insert(data->main.end(), it, it + blockSize);
		it += blockSize;
		indexes.push_back(i);
		i += blockSize;
	}

	if (ite != current.end())
		data->remaining.insert(data->remaining.end(), ite, current.end());


	std::cout << "[MAIN] ";
	printContainer(data->main, blockSize);
	std::cout << "[PENDING] ";
	printContainer(data->pending, blockSize);
	if (!data->remaining.empty())
	{
		std::cout << "[REMAINING] ";
		printContainer(data->remaining, 1);
	}
	return (indexes);
}

void	updateIndexes(std::deque<size_t> &indexes, size_t i, size_t blockSize)
{
	for (std::deque<size_t>::iterator it = find(indexes.begin(), indexes.end(), i) + 0; it < indexes.end(); it ++)
	{
		*it += blockSize;
	}
}

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator head, size_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, std::deque<size_t> &indexes)
{
	size_t								dist = (distance(min_, max_) + 1) / blockSize;
	std::deque<unsigned int>::iterator	it;

	
	//std::cout << "blockSize = " << blockSize << " dist = " << dist << " min = " << *(min_) << " max = " << *(max_) << std::endl;
	std::cout << "********** HEAD = " << *(head) << std::endl;

	if (dist == 0)
	{
		container.insert(container.begin(), head - blockSize + 1, head + 1);
		updateIndexes(indexes, 2, blockSize);
		return ;
	}
	
	if (dist <= 2 )
	{
		if (*(head) < *(min_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") smaller than min (" << *(min_) << ")" << std::endl;
			it = min_ - blockSize + 1;
		}
		else if (*(head) > *(min_) && *(head) < *(max_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") between min " << *(min_) << " and max (" << *(max_) << ")" << std::endl;
			it = min_ + 1;
		}
		else if (*(head) > *(max_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") bigger than max (" << *(max_) << ")" << std::endl;
			it = max_ + 1;
		}
			
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize);
		g_counter ++;
		return ;
	}

	if (dist > 2)
	{
		size_t	middle = dist / 2;
		it = min_ + middle + blockSize / 2;
		//std::cout << "middle = " << *(it) << std::endl;
		g_counter ++;
		if (*(head) > *(it))
		{
			//std::cout << "head (" << *(head) << ") bigger than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, it, max_, indexes);
		}
		else if (*(head) < *(it))
		{
			//std::cout << "head (" << *(head) << ") smaller than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, min_, it, indexes);
		}
			
	}
}

std::deque<unsigned int>	jacobsthalMerge(t_dataDeq *data, size_t blockSize, std::deque<size_t> *jacobsthal, std::deque<size_t> &indexes)
{
	std::deque<unsigned int>			merged;
	size_t								npendingBlocks = data->pending.size() / blockSize;
	
	(void)jacobsthal;

	//data->main.insert(data->main.begin(), data->pending.begin(), data->pending.begin() + blockSize);

	while (npendingBlocks > 0)
	{
		std::cout << "npendingBlocks = " << npendingBlocks << " ";
		//std::cout << "index = " << indexes[npendingBlocks -1] << " ";
		std::deque<unsigned int>::iterator	head = data->pending.begin() + npendingBlocks * blockSize -1;
		std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[npendingBlocks - 1] -1;
	
		binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, indexes);
		//std::cout << "main after insertion = ";
		//printContainer(data->main, blockSize);
		//std::cout << "indexes after insertion = ";
		//printContainer(indexes, 1);
		npendingBlocks --;
	}
	merged.insert(merged.end(), data->main.begin(), data->main.end());
	merged.insert(merged.end(), data->remaining.begin(), data->remaining.end());
	return (merged);
}

void	merging(size_t pairSize, std::deque<unsigned int> &current, std::deque<size_t>	*jacobsthal)
{
	while (pairSize / 2 >= 1)
	{
		t_dataDeq	data;
		std::deque<size_t>	indexes;

		std::cout << "-----------------------------" << std::endl;
		indexes = formMainAndPending(&data, pairSize / 2, current, getIte(current, pairSize));
		//std::cout << "-----------------------------\nindexes BEFORE insertion = ";
		//printContainer(indexes, 1);

		current = jacobsthalMerge(&data, pairSize / 2, jacobsthal, indexes);

		std::cout << "*** merged = ";
		printContainer(current, pairSize / 2);
		pairSize /= 2;
	}
}

void	PmergeMe::sortDequeue()
{
	std::deque<size_t>	jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	size_t	pairSize = swapping(2, this->deq.size(), this->deq);
	std::cout << "*** sorted = ";
	printContainer(this->deq, pairSize / 2);
	merging(pairSize / 2, this->deq, &jacobsthal);
	std::cout << YELLOW << "Comparaisons : " << g_counter << DEFAULT << std::endl;
}