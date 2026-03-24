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
	ssize_t	i = 0;
	for (std::deque<unsigned int>::iterator it = current.begin(); it + pairSize / 2 < max_; it += pairSize)
	{
		g_counter ++;
		std::deque<unsigned int>::iterator a = it + pairSize / 2 -1;
		std::deque<unsigned int>::iterator b = a + pairSize / 2;
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

	ssize_t	npairs = current.size() / pairSize;
	ssize_t	remaining = current.size() - npairs * pairSize; 

	ite = current.end() - remaining; // 7 - 3 = 4
	return (ite);
}

ssize_t	swapping(ssize_t pairSize, ssize_t size, std::deque<unsigned int> &current)
{
	while (size / pairSize >= 1)
	{
		sortPairs(pairSize, current, getIte(current, pairSize));
		std::cout << "*** sorted = ";
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

void	updateIndexes(std::deque<ssize_t> &indexes, ssize_t i, ssize_t blockSize)
{
	std::cout << "-----------------------------\nentered updateIndexes with i = " << i << " blockSize = " << blockSize << std::endl;

	std::cout << "indexes BEFORE UPDATE = ";
	printContainer(indexes, 1);

	std::deque<ssize_t>::iterator tmp;
	if (i < *(indexes.begin()))
		tmp = indexes.begin();
	else
		tmp = find(indexes.begin(), indexes.end(), i);
	for (std::deque<ssize_t>::iterator it = tmp; it < indexes.end(); it ++) // ne doit pas incrémenter le dernier si était un sans main
		*it += blockSize;

	std::cout << "indexes AFTER UPDATE = ";
	printContainer(indexes, 1);
	std::cout << "-----------------------------\n";
}

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator head, ssize_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, int type, std::deque<ssize_t> &indexes)
{
	ssize_t								dist = (distance(min_, max_)) / blockSize;
	std::deque<unsigned int>::iterator	it;

	std::cout << "*************************** HEAD = " << *(head) << std::endl;
	std::cout << " dist = " << dist << " type = " << type << " min = " << *(min_) << " max = " << *(max_) << std::endl;

	if (dist == 0)
	{
		if (*(head) < *(min_))
			it = min_ - blockSize + 1; // avant min
		else
			it = min_ + 1; // après min
		g_counter ++;
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize);
		return ;
	}
	
	if (dist == 1)
	{
		if (type == 0)
		{
			if (*(head) > *(min_))
				type = 1;
			else
				type = -1;
			g_counter ++;
		}
		if (type == 1)	//  (> min)
		{
			if (*(head) < *(max_))
			{
				std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				std::cout << "[INSERTED] head (" << *(head) << ") bigger than max (" << *(max_) << ")" << std::endl;
				it = max_ + 1;
			}
			g_counter ++;
		}
		else if (type == -1)	// ( < max)
		{
			if (*(head) > *(min_))
			{
				std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				std::cout << "[INSERTED] head (" << *(head) << ") smaller than min (" << *(min_) << ")" << std::endl;
				it = min_ - blockSize + 1;
			}
			g_counter ++;
		}
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize);
		return ;
	}

	if (dist > 1)
	{
		ssize_t	middle = dist / 2;
		it = min_ + middle * blockSize;
		std::cout << " middle = " << *(it) << std::endl;
		g_counter ++;
		if (*(head) > *(it))
		{
			//std::cout << "head (" << *(head) << ") bigger than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, it, max_, 1, indexes);
		}
		else
		{
			//std::cout << "head (" << *(head) << ") smaller than middle (" << *(it) << ")" << std::endl;
			binaryInsert(container, head, blockSize, min_, it, -1, indexes);
		}	
	}
}

std::deque<unsigned int>	normalMerge(t_dataDeq *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::deque<ssize_t> &indexes, std::deque<bool> used)
{
	std::deque<unsigned int>	merged;
	ssize_t						i = n;

	if (remaining)
	{
		while (n > 0)
		{
			if (used[n -1] == false) // if n * blockSize -1 > jacobsthal[1]
			{
				std::deque<unsigned int>::iterator	head = data->pending.begin() + n * blockSize -1;
				std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[n - 1] -1;
				if (i == n)
					max_ = data->main.end() -1;
				binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes);
				std::cout << "main after new insertion = ";
				printContainer(data->main, blockSize);
			}
			else
			{
				std::cout << "!!!!! already inserted !!!!" << std::endl;
				break;
			}
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
	std::deque<bool>					used;
	//(void)jacobsthal;
	ssize_t								diffjac;

	for (ssize_t i = 0; i < n; i ++)
		used.push_back(false);

	data->main.insert(data->main.begin(), data->pending.begin(), data->pending.begin() + blockSize);
	updateIndexes(indexes, blockSize, blockSize);
	used[0] = true;
	npendingBlocks --;

	jacobsthal[0] = 1;
	jacobsthal[1] = 3;
	diffjac = jacobsthal[1] - jacobsthal[0];

	while (npendingBlocks >= diffjac)
	{
		if (n < jacobsthal[1])
			break;
		std::cout << "diffjac = " << diffjac << " jacobsthal = " << jacobsthal[1] << std::endl;
		ssize_t	i = 0;
		while (diffjac > 0)
		{
			std::deque<unsigned int>::iterator	head = data->pending.begin() + (jacobsthal[1] -i) * blockSize -1;
			std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[jacobsthal[1] -i -1] -1;
			if (head == data->pending.end() -1)
				max_ = data->main.end() -1;
			binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes);
			used[jacobsthal[1] -i -1] = true;
			std::cout << "main after new insertion = ";
			printContainer(data->main, blockSize);
			i ++;
			npendingBlocks --;
			diffjac --;
		}
		updateJacobsthal(jacobsthal);
		diffjac = jacobsthal[1] - jacobsthal[0];
	}
	return (normalMerge(data, blockSize, n, npendingBlocks, indexes, used));
}

void	merging(ssize_t pairSize, std::deque<unsigned int> &current, std::deque<ssize_t>	&jacobsthal)
{
	while (pairSize / 2 >= 1)
	{
		t_dataDeq	data;
		std::deque<ssize_t>	indexes;

		std::cout << "-----------------------------" << std::endl;

		indexes = formMainAndPending(&data, pairSize / 2, current, getIte(current, pairSize));
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
	merging(pairSize / 2, this->deq, jacobsthal);
	std::cout << YELLOW << "Comparaisons : " << g_counter << DEFAULT << std::endl;
}