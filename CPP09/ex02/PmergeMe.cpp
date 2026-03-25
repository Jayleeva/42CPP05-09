#include "PmergeMe.hpp"

ssize_t		g_counterDeq;

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
		this->vec = original.vec;
		this->deq = original.deq;
	}
	std::cout << YELLOW << "[PMERGEME] : Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default destructor called" << DEFAULT << std::endl;
}

std::vector<unsigned int>	PmergeMe::getVec() const
{
	return (this->vec);
}

void	PmergeMe::setVec(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end)
{
	this->vec.insert(this->vec.end(), begin, end);
}

std::deque<unsigned int>	PmergeMe::getDeq() const
{
	return (this->deq);
}

void	PmergeMe::setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->deq.insert(this->deq.end(), begin, end);
}


//------------------------ VECTOR ----------------------------------------

ssize_t		g_counterVec;

void	updateJacobsthal(std::vector<ssize_t> &jacobsthal)
{
	ssize_t tmp1 = jacobsthal[0];
	ssize_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
}

void	swapElements(ssize_t blockSize, std::vector<unsigned int>::iterator it, std::vector<unsigned int>::iterator ite)
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

void	sortPairs(ssize_t pairSize, std::vector<unsigned int> &current, std::vector<unsigned int>::iterator max_)
{
	ssize_t	i = 0;
	for (std::vector<unsigned int>::iterator it = current.begin(); it + pairSize / 2 < max_; it += pairSize)
	{
		g_counterVec ++;
		std::vector<unsigned int>::iterator a = it + pairSize / 2 -1;
		std::vector<unsigned int>::iterator b = a + pairSize / 2;
		if (*(a) > *(b))
		{
			swapElements(pairSize / 2, it, it + pairSize / 2);				
		}
		i += pairSize;
	}
}

std::vector<unsigned int>::iterator getIte(std::vector<unsigned int> &current, ssize_t pairSize)
{
	std::vector<unsigned int>::iterator	ite;

	ssize_t	npairs = current.size() / pairSize;
	ssize_t	remaining = current.size() - npairs * pairSize; 

	ite = current.end() - remaining; // 7 - 3 = 4
	return (ite);
}

ssize_t	swapping(ssize_t pairSize, ssize_t size, std::vector<unsigned int> &current)
{
	while (size / pairSize >= 1)
	{
		sortPairs(pairSize, current, getIte(current, pairSize));
		if (VERBIOSE)
		{
			std::cout << "*** sorted = ";
			printContainer(current, pairSize / 2);		
		}
		pairSize *= 2;
	}
	return (pairSize);
}


std::vector<ssize_t>	formMainAndPending(t_dataVec *data, ssize_t blockSize, std::vector<unsigned int> &current, std::vector<unsigned int>::iterator ite)
{
	std::vector<ssize_t>	indexes;
	std::vector<unsigned int>::iterator	it = current.begin();
	ssize_t				i = blockSize;
	ssize_t				tmp;

	while (it != ite)
	{
		data->pending.insert(data->pending.end(), it, it + blockSize);
		it += blockSize;
		data->main.insert(data->main.end(), it, it + blockSize);
		it += blockSize;
		indexes.push_back(i);
		i += blockSize;
	}

	tmp = *(indexes.end() -1);
	if (ite != current.end())
	{
		if ((ssize_t)distance(ite, current.end()) >= blockSize)
		{
			data->pending.insert(data->pending.end(), it, it + blockSize);
			it += blockSize;
			indexes.push_back(tmp);
		} 
		data->remaining.insert(data->remaining.end(), it, current.end());
	}

	if (VERBIOSE)
	{
		std::cout << "[MAIN] ";
		printContainer(data->main, blockSize);
		std::cout << "[PENDING] ";
		printContainer(data->pending, blockSize);
		if (!data->remaining.empty())
		{
			std::cout << "[REMAINING] ";
			printContainer(data->remaining, 1);
		}
	}
	return (indexes);
}

void	updateIndexes(std::vector<ssize_t> &indexes, ssize_t i, ssize_t blockSize, bool nomatch)
{
	if (VERBIOSE)
	{
		std::cout << "-----------------------------\nentered updateIndexes with i = " << i << " blockSize = " << blockSize << std::endl;
		std::cout << "indexes BEFORE UPDATE = ";
		printContainer(indexes, 1);
	}

	std::vector<ssize_t>::iterator	tmpit; 
	bool							found = false;
	ssize_t							j = 0;

	if (i > *(indexes.end() -1))
	{
		tmpit = indexes.end();
		found = true;
	}
	if (i < 0)
		i = blockSize;

	while (found == false)
	{
		for (std::vector<ssize_t>::iterator it = indexes.begin(); it < indexes.end(); it ++)
		{
			if (*it == i + j)
			{
				tmpit = it;
				found = true;
			}
		}
		j += blockSize;
	}

	for (std::vector<ssize_t>::iterator it = tmpit; it < indexes.end(); it ++)
			*it += blockSize;
	if (nomatch)
		*(indexes.end()) = *(indexes.end() -1);

	if (VERBIOSE)
	{
		std::cout << "indexes AFTER UPDATE = ";
		printContainer(indexes, 1);
		std::cout << "-----------------------------\n";
	}
}

void	binaryInsert(std::vector<unsigned int> &container, std::vector<unsigned int>::iterator head, ssize_t blockSize, std::vector<unsigned int>::iterator min_, std::vector<unsigned int>::iterator max_, int type, std::vector<ssize_t> &indexes, bool nomatch)
{
	ssize_t								dist = (distance(min_, max_)) / blockSize;
	std::vector<unsigned int>::iterator	it;

	if (VERBIOSE)
	{
		std::cout << "*************************** HEAD = " << *(head) << std::endl;
		std::cout << " dist = " << dist << " type = " << type << " min = " << *(min_) << " max = " << *(max_) << std::endl;		
	}

	if (dist == 0)
	{
		if (*(head) < *(min_))
			it = min_ - blockSize + 1; // avant min
		else
			it = min_ + 1; // après min
		g_counterVec ++;
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize, nomatch);
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
			g_counterVec ++;
		}
		if (type == 1)	//  (> min)
		{
			if (*(head) < *(max_))
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") bigger than max (" << *(max_) << ")" << std::endl;
				it = max_ + 1;
			}
			g_counterVec ++;
		}
		else if (type == -1)	// ( < max)
		{
			if (*(head) > *(min_))
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") smaller than min (" << *(min_) << ")" << std::endl;
				it = min_ - blockSize + 1;
			}
			g_counterVec ++;
		}
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize, nomatch);
		return ;
	}

	if (dist > 1)
	{
		ssize_t	middle = dist / 2;
		it = min_ + middle * blockSize;
		if (VERBIOSE)
			std::cout << " middle = " << *(it) << std::endl;
		g_counterVec ++;
		if (*(head) > *(it))
			binaryInsert(container, head, blockSize, it, max_, 1, indexes, nomatch);
		else
			binaryInsert(container, head, blockSize, min_, it, -1, indexes, nomatch);
	}
}

std::vector<unsigned int>	normalMerge(t_dataVec *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::vector<ssize_t> &indexes, std::vector<bool> used, bool nomatch)
{
	std::vector<unsigned int>	merged;
	ssize_t						i = n;

	if (remaining)
	{
		while (n > 0)
		{
			if (used[n -1] == false) // if n * blockSize -1 > jacobsthal[1]
			{
				std::vector<unsigned int>::iterator	head = data->pending.begin() + n * blockSize -1;
				std::vector<unsigned int>::iterator	max_ = data->main.begin() + indexes[n - 1] -1;
				if (i == n)
					max_ = data->main.end() -1;
				binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes, nomatch);
				if (VERBIOSE)
				{
					std::cout << "main after new insertion = ";
					printContainer(data->main, blockSize);
				}
			}
			else
			{
				if (VERBIOSE)
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

std::vector<unsigned int>	jacobsthalMerge(t_dataVec *data, ssize_t blockSize, std::vector<ssize_t> &indexes, bool nomatch)
{
	ssize_t								npendingBlocks = data->pending.size() / blockSize;
	ssize_t								n = npendingBlocks;
	std::vector<bool>					used;

	std::vector<ssize_t> 				jacobsthal;
	ssize_t								diffjac;

	for (ssize_t i = 0; i < n; i ++)
		used.push_back(false);

	data->main.insert(data->main.begin(), data->pending.begin(), data->pending.begin() + blockSize);
	updateIndexes(indexes, blockSize, blockSize, nomatch);

	used[0] = true;
	npendingBlocks --;

	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	diffjac = jacobsthal[1] - jacobsthal[0];

	while (npendingBlocks >= diffjac)
	{
		
		if (n < jacobsthal[1])
			break;
		if (VERBIOSE)
			std::cout << "diffjac = " << diffjac << " jacobsthal = " << jacobsthal[1] << std::endl;
		ssize_t	i = 0;
		while (diffjac > 0)
		{
			std::vector<unsigned int>::iterator	head = data->pending.begin() + (jacobsthal[1] -i) * blockSize -1;
			std::vector<unsigned int>::iterator	max_ = data->main.begin() + indexes[jacobsthal[1] -i -1] -1;
			if (head == data->pending.end() -1)
				max_ = data->main.end() -1;
			binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes, nomatch);
			used[jacobsthal[1] -i -1] = true;
			if (VERBIOSE)
			{
				std::cout << "main after new insertion = ";
				printContainer(data->main, blockSize);
			}
			i ++;
			npendingBlocks --;
			diffjac --;
		}
		updateJacobsthal(jacobsthal);
		diffjac = jacobsthal[1] - jacobsthal[0];
	}
	return (normalMerge(data, blockSize, n, npendingBlocks, indexes, used, nomatch));
}

bool	hasNomatch(std::vector<ssize_t>	indexes)
{
	if (*(indexes.end()) == *(indexes.end() -1))
		return (true);
	else
		return (false);
}

void	merging(ssize_t pairSize, std::vector<unsigned int> &current)
{
	while (pairSize / 2 >= 1)
	{
		t_dataVec	data;
		std::vector<ssize_t>	indexes;

		if (VERBIOSE)
			std::cout << "-----------------------------" << std::endl;

		indexes = formMainAndPending(&data, pairSize / 2, current, getIte(current, pairSize));
		current = jacobsthalMerge(&data, pairSize / 2, indexes, hasNomatch(indexes));

		if (VERBIOSE)
		{
			std::cout << "*** merged = ";
			printContainer(current, pairSize / 2);
		}
		pairSize /= 2;
	}
}

ssize_t	PmergeMe::sortVector()
{
	g_counterVec = 0;
	ssize_t	pairSize = swapping(2, this->vec.size(), this->vec);
	merging(pairSize / 2, this->vec);
	return (g_counterVec);
	//if (VERBIOSE)
	//	std::cout << YELLOW << "Comparaisons : " << g_counterVec << DEFAULT << std::endl;
}

//--------------------------DEQUEUE----------------------------------------

void	updateJacobsthal(std::deque<ssize_t> &jacobsthal)
{
	ssize_t tmp1 = jacobsthal[0];
	ssize_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
}

void	swapElements(ssize_t blockSize, std::deque<unsigned int>::iterator it, std::deque<unsigned int>::iterator ite)
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
		g_counterDeq ++;
		std::deque<unsigned int>::iterator a = it + pairSize / 2 -1;
		std::deque<unsigned int>::iterator b = a + pairSize / 2;
		if (*(a) > *(b))
		{
			swapElements(pairSize / 2, it, it + pairSize / 2);				
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
		if (VERBIOSE)
		{
			std::cout << "*** sorted = ";
			printContainer(current, pairSize / 2);		
		}
		pairSize *= 2;
	}
	return (pairSize);
}


std::deque<ssize_t>	formMainAndPending(t_dataDeq *data, ssize_t blockSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite)
{
	std::deque<ssize_t>	indexes;
	std::deque<unsigned int>::iterator	it = current.begin();
	ssize_t				i = blockSize;
	ssize_t				tmp;

	while (it != ite)
	{
		data->pending.insert(data->pending.end(), it, it + blockSize);
		it += blockSize;
		data->main.insert(data->main.end(), it, it + blockSize);
		it += blockSize;
		indexes.push_back(i);
		i += blockSize;
	}

	tmp = *(indexes.end() -1);
	if (ite != current.end())
	{
		if ((ssize_t)distance(ite, current.end()) >= blockSize)
		{
			data->pending.insert(data->pending.end(), it, it + blockSize);
			it += blockSize;
			indexes.push_back(tmp);
		} 
		data->remaining.insert(data->remaining.end(), it, current.end());
	}

	if (VERBIOSE)
	{
		std::cout << "[MAIN] ";
		printContainer(data->main, blockSize);
		std::cout << "[PENDING] ";
		printContainer(data->pending, blockSize);
		if (!data->remaining.empty())
		{
			std::cout << "[REMAINING] ";
			printContainer(data->remaining, 1);
		}
	}
	return (indexes);
}

void	updateIndexes(std::deque<ssize_t> &indexes, ssize_t i, ssize_t blockSize, bool nomatch)
{
	if (VERBIOSE)
	{
		std::cout << "-----------------------------\nentered updateIndexes with i = " << i << " blockSize = " << blockSize << std::endl;
		std::cout << "indexes BEFORE UPDATE = ";
		printContainer(indexes, 1);
	}

	std::deque<ssize_t>::iterator	tmpit; 
	bool							found = false;
	ssize_t							j = 0;

	if (i > *(indexes.end() -1))
	{
		tmpit = indexes.end();
		found = true;
	}
	if (i < 0)
		i = blockSize;

	while (found == false)
	{
		for (std::deque<ssize_t>::iterator it = indexes.begin(); it < indexes.end(); it ++)
		{
			if (*it == i + j)
			{
				tmpit = it;
				found = true;
			}
		}
		j += blockSize;
	}

	for (std::deque<ssize_t>::iterator it = tmpit; it < indexes.end(); it ++)
			*it += blockSize;
	if (nomatch)
		*(indexes.end()) = *(indexes.end() -1);

	if (VERBIOSE)
	{
		std::cout << "indexes AFTER UPDATE = ";
		printContainer(indexes, 1);
		std::cout << "-----------------------------\n";
	}
}

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator head, ssize_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, int type, std::deque<ssize_t> &indexes, bool nomatch)
{
	ssize_t								dist = (distance(min_, max_)) / blockSize;
	std::deque<unsigned int>::iterator	it;

	if (VERBIOSE)
	{
		std::cout << "*************************** HEAD = " << *(head) << std::endl;
		std::cout << " dist = " << dist << " type = " << type << " min = " << *(min_) << " max = " << *(max_) << std::endl;		
	}

	if (dist == 0)
	{
		if (*(head) < *(min_))
			it = min_ - blockSize + 1; // avant min
		else
			it = min_ + 1; // après min
		g_counterDeq ++;
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize, nomatch);
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
			g_counterDeq ++;
		}
		if (type == 1)	//  (> min)
		{
			if (*(head) < *(max_))
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") bigger than max (" << *(max_) << ")" << std::endl;
				it = max_ + 1;
			}
			g_counterDeq ++;
		}
		else if (type == -1)	// ( < max)
		{
			if (*(head) > *(min_))
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") between min (" << *(min_) << ") and max (" << *(max_) << ")" << std::endl;
				it = min_ + 1;
			}
			else
			{
				if (VERBIOSE)
					std::cout << "[INSERTED] head (" << *(head) << ") smaller than min (" << *(min_) << ")" << std::endl;
				it = min_ - blockSize + 1;
			}
			g_counterDeq ++;
		}
		container.insert(it, head - blockSize + 1, head + 1);
		updateIndexes(indexes, distance(container.begin(), it), blockSize, nomatch);
		return ;
	}

	if (dist > 1)
	{
		ssize_t	middle = dist / 2;
		it = min_ + middle * blockSize;
		if (VERBIOSE)
			std::cout << " middle = " << *(it) << std::endl;
		g_counterDeq ++;
		if (*(head) > *(it))
			binaryInsert(container, head, blockSize, it, max_, 1, indexes, nomatch);
		else
			binaryInsert(container, head, blockSize, min_, it, -1, indexes, nomatch);
	}
}

std::deque<unsigned int>	normalMerge(t_dataDeq *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::deque<ssize_t> &indexes, std::deque<bool> used, bool nomatch)
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
				binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes, nomatch);
				if (VERBIOSE)
				{
					std::cout << "main after new insertion = ";
					printContainer(data->main, blockSize);
				}
			}
			else
			{
				if (VERBIOSE)
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

std::deque<unsigned int>	jacobsthalMerge(t_dataDeq *data, ssize_t blockSize, std::deque<ssize_t> &indexes, bool nomatch)
{
	ssize_t								npendingBlocks = data->pending.size() / blockSize;
	ssize_t								n = npendingBlocks;
	std::deque<bool>					used;

	std::deque<ssize_t> 				jacobsthal;
	ssize_t								diffjac;

	for (ssize_t i = 0; i < n; i ++)
		used.push_back(false);

	data->main.insert(data->main.begin(), data->pending.begin(), data->pending.begin() + blockSize);
	updateIndexes(indexes, blockSize, blockSize, nomatch);
	used[0] = true;
	npendingBlocks --;

	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	diffjac = jacobsthal[1] - jacobsthal[0];

	while (npendingBlocks >= diffjac)
	{
		if (n < jacobsthal[1])
			break;
		if (VERBIOSE)
			std::cout << "diffjac = " << diffjac << " jacobsthal = " << jacobsthal[1] << std::endl;
		ssize_t	i = 0;
		while (diffjac > 0)
		{
			std::deque<unsigned int>::iterator	head = data->pending.begin() + (jacobsthal[1] -i) * blockSize -1;
			std::deque<unsigned int>::iterator	max_ = data->main.begin() + indexes[jacobsthal[1] -i -1] -1;
			if (head == data->pending.end() -1)
				max_ = data->main.end() -1;
			binaryInsert(data->main, head, blockSize, data->main.begin() + blockSize -1, max_, 0, indexes, nomatch);
			used[jacobsthal[1] -i -1] = true;
			if (VERBIOSE)
			{
				std::cout << "main after new insertion = ";
				printContainer(data->main, blockSize);
			}
			i ++;
			npendingBlocks --;
			diffjac --;
		}
		updateJacobsthal(jacobsthal);
		diffjac = jacobsthal[1] - jacobsthal[0];
	}
	return (normalMerge(data, blockSize, n, npendingBlocks, indexes, used, nomatch));
}

bool	hasNomatch(std::deque<ssize_t>	indexes)
{
	if (*(indexes.end()) == *(indexes.end() -1))
		return (true);
	else
		return (false);
}

void	merging(ssize_t pairSize, std::deque<unsigned int> &current)
{
	while (pairSize / 2 >= 1)
	{
		t_dataDeq	data;
		std::deque<ssize_t>	indexes;

		if (VERBIOSE)
			std::cout << "-----------------------------" << std::endl;

		indexes = formMainAndPending(&data, pairSize / 2, current, getIte(current, pairSize));
		current = jacobsthalMerge(&data, pairSize / 2, indexes, hasNomatch(indexes));

		if (VERBIOSE)
		{
			std::cout << "*** merged = ";
			printContainer(current, pairSize / 2);
		}
		pairSize /= 2;
	}
}

ssize_t	PmergeMe::sortDequeue()
{
	g_counterDeq = 0;
	ssize_t	pairSize = swapping(2, this->deq.size(), this->deq);
	merging(pairSize / 2, this->deq);
	return (g_counterDeq);
	//if (VERBIOSE)
	//	std::cout << YELLOW << "Comparaisons : " << g_counterDeq << DEFAULT << std::endl;
}