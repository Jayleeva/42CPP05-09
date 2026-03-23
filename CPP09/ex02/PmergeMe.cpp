#include "PmergeMe.hpp"

ssize_t		g_counter;

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

void	updateJacobsthal(std::deque<ssize_t> &jacobsthal)
{
	ssize_t tmp1 = jacobsthal[0];
	ssize_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
}

void	swap_elements(ssize_t blockSize, std::deque<unsigned int>::iterator it, std::deque<unsigned int>::iterator ite)
{
	unsigned int	tmpui;

	for (ssize_t i = 0; i < blockSize; i ++)
	{	
		tmpui = *it;
		*it = *ite;
		*ite = tmpui;

		it ++;
		ite ++;
	}
}

void	sortPairs(ssize_t pairSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator max_)
{
	//std::cout << "pairSize = " << pairSize << " max = " << *(max_ -1) << std::endl;
	ssize_t	i = 0;
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

std::deque<unsigned int>::iterator getIte(std::deque<unsigned int> &current, ssize_t pairSize)
{
	std::deque<unsigned int>::iterator	ite;

	ssize_t	npairs = current.size() / pairSize; // 7 / 4 = 1
	ssize_t	remaining = current.size() - npairs * pairSize; // 7 - 1 * 4 = 3

	ite = current.end() - remaining; // 7 - 3 = 4
	//std::cout << "ite = " << *(ite -1) << std::endl;
	return (ite);
}

ssize_t	swapping(ssize_t pairSize, ssize_t size, std::deque<unsigned int> &current)
{
	while (size / pairSize >= 1)
	{
		sortPairs(pairSize, current, getIte(current, pairSize));
		std::cout << "sorted = ";
		printContainer(current, pairSize / 2);
		pairSize *= 2;
	}
	return (pairSize);
}


std::deque<ssize_t>	formMainAndPending(t_dataDeq *data, ssize_t blockSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite)
{
	std::deque<ssize_t>	indexes;
	std::deque<unsigned int>::iterator	it = current.begin();
	ssize_t				i = blockSize;

	//std::cout << "ite -1 = " << *(ite -1) << std::endl;
	while (it != ite)
	{
		data->pending.insert(data->pending.end(), it, it + blockSize);
		it += blockSize;
		data->main.insert(data->main.end(), it, it + blockSize);
		it += blockSize;
		indexes.push_back(i);
		i += blockSize;
	}

	if (ite != current.end()) // ajouter dans pending si encore possible de faire un bloc; ajouter dernier main comme max dans les indexes
	{
		if ((ssize_t)distance(ite, current.end()) >= blockSize)
		{
			data->pending.insert(data->pending.end(), it, it + blockSize);
			it += blockSize;
			indexes.push_back(i);
		} 
		data->remaining.insert(data->remaining.end(), it, current.end());
	}

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

void	updateIndexes(std::deque<ssize_t> &indexes, ssize_t i, ssize_t blockSize)// ssize_t i, ) std::deque<ssize_t>::iterator it
{
	std::cout << "entered updateIndexes with i = " << i << std::endl;

	//for (std::deque<ssize_t>::iterator it = find(indexes.begin(), indexes.end(), i); it < indexes.end(); it ++)
	for (std::deque<ssize_t>::iterator it = indexes.begin() + i; it < indexes.end(); it ++)
	{
		if (*it >= 0)
			*it += blockSize;
	}
}

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator head, ssize_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, std::deque<ssize_t> &indexes)
{
	ssize_t								dist = (distance(min_, max_)) / blockSize;
	std::deque<unsigned int>::iterator	it;

	//std::cout << "blockSize = " << blockSize << " dist = " << dist << " min = " << *(min_) << " max = " << *(max_) << std::endl;
	
	std::cout << " dist = " << dist << " min = " << *(min_) << " max = " << *(max_) << std::endl;
	std::cout << "********** HEAD = " << *(head) << std::endl;

	/*if (dist == 0)
	{
		container.insert(container.begin(), head - blockSize + 1, head + 1);
		updateIndexes(indexes, 2, blockSize); // NOPE
		//updateIndexes(indexes, indexes.begin(), blockSize);
		return ;
	}*/
	
	if (dist <= 1)
	{
		if (*(head) < *(min_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") smaller than min (" << *(min_) << ")" << std::endl;
			it = min_ - blockSize + 1;
			g_counter ++;
		}
		else if (*(head) > *(min_) && *(head) < *(max_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
			it = min_ + 1;
			g_counter ++;
		}
		else if (*(head) > *(max_))
		{
			std::cout << "[INSERTED] head (" << *(head) << ") bigger than max (" << *(max_) << ")" << std::endl;
			it = max_ + 1;
			g_counter ++;
		}
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize); // distance ne donne pas le bon
		//updateIndexes(indexes, it -1, blockSize);
		return ;
	}

	if (dist > 1)
	{
		ssize_t	middle = dist / 2;
		it = min_ + middle * blockSize;
		std::cout << "middle = " << *(it) << std::endl;
		g_counter ++;
		if (*(head) > *(it))
		{
			//std::cout << "head (" << *(head) << ") bigger than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, it, max_, indexes);
		}
		else
		{
			//std::cout << "head (" << *(head) << ") smaller than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, min_, it, indexes);
		}	
	}

}

std::deque<unsigned int>	normalMerge(t_dataDeq *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::deque<ssize_t> &indexes)
{
	std::deque<unsigned int>	merged;
	ssize_t						i = n;

	if (remaining)
	{
		while (n > 0)
		{
			if (indexes[n -1] >= 0)
			{
				std::deque<unsigned int>::iterator	head = data->pending.begin() + n * blockSize -1;
				std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[n - 1] -1;
				if (i == n)
					max_ = data->main.end() -1;
				binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, indexes);
			}
			else
				std::cout << "!!!!! already inserted !!!!" << std::endl;
			n --;
		}
	}
	merged.insert(merged.end(), data->main.begin(), data->main.end());
	merged.insert(merged.end(), data->remaining.begin(), data->remaining.end());
	return (merged);
}

std::deque<unsigned int>	jacobsthalMerge(t_dataDeq *data, ssize_t blockSize, std::deque<ssize_t> &jacobsthal, std::deque<ssize_t> &indexes)
{
	ssize_t								npendingBlocks = data->pending.size() / blockSize;
	ssize_t								n = npendingBlocks;
	//(void)jacobsthal;
	ssize_t								diffjac;

	//data->main.insert(data->main.begin(), data->pending.begin(), data->pending.begin() + blockSize);

	jacobsthal[0] = 1;
	jacobsthal[1] = 3;
	diffjac = jacobsthal[1] - jacobsthal[0];

	if (n < jacobsthal[1])
		return (normalMerge(data, blockSize, n, npendingBlocks, indexes));

	while (npendingBlocks >= diffjac)
	{
		if (npendingBlocks < jacobsthal[1])
			break;
		std::cout << "diffjac = " << diffjac << " jacobsthal = " << jacobsthal[1] << std::endl;
		ssize_t	i = 0;
		while (diffjac > 0)
		{
			std::cout << "indexes = ";
			printContainer(indexes, 1);
	
			std::deque<unsigned int>::iterator	head = data->pending.begin() + (jacobsthal[1] -i) * blockSize -1;
			std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[jacobsthal[1] -i -1] -1;
			if (head == data->pending.end() -1)
				max_ = data->main.end() -1;
			binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, indexes); // NOPE. comme va pas du dernier au premier, la logique d'incrémenentation des indexes est fausse.
			indexes[jacobsthal[1] -i -1] = -2 * data->pending.size();
			i ++;
			npendingBlocks --;
			diffjac --;
		}
		updateJacobsthal(jacobsthal);
		diffjac = jacobsthal[1] - jacobsthal[0];
	}
	return (normalMerge(data, blockSize, n, npendingBlocks, indexes));
}

void	merging(ssize_t pairSize, std::deque<unsigned int> &current, std::deque<ssize_t>	&jacobsthal)
{
	while (pairSize / 2 >= 1)
	{
		t_dataDeq	data;
		std::deque<ssize_t>	indexes;

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
	std::deque<ssize_t>	jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);

	ssize_t	pairSize = swapping(2, this->deq.size(), this->deq);
	std::cout << "*** sorted = ";
	printContainer(this->deq, pairSize / 2);
	//std::cout << "pairSize = " << pairSize << std::endl;
	merging(pairSize / 2, this->deq, jacobsthal);
	std::cout << YELLOW << "Comparaisons : " << g_counter << DEFAULT << std::endl;
}