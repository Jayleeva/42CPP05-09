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

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator blockEnd, size_t blockSize, std::deque<unsigned int>::iterator max_)
{
	size_t								dist = distance(min_, max_);
	std::deque<unsigned int>::iterator	it;

	std::cout << "blocksize in BINARY = " << blockSize << std::endl;
	if (dist / blockSize == 2)
	{
		if (*blockEnd < *(min_))
			it = min_ - blockSize;
		else if (*blockEnd > *(min_) && *blockEnd < *(max_))
			it = min_;
		else if (*blockEnd > *(max_))
			it = max_;
		container.insert(it, blockEnd - blockSize, blockEnd);
		return;
	}

	if (dist / 2 >= 1)
	{
		if (dist % 2 == 0)
			dist = dist / 2 - 1;
		else 
			dist /= 2;
		it = max_ - dist;
		if (*blockEnd > *it)
			binaryInsert(container, it, blockEnd, blockSize, max_);
		else if (*blockEnd < *it)
			binaryInsert(container, min_, blockEnd, blockSize, it);
	}
}


t_dataDeq	formMainAndPending(std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite)
{
	t_dataDeq							data;
	size_t								size = current.size();

	if (size < 2)
	{
		data.main.insert(data.main.end(), current.begin(), current.end());
		std::cout << "NOT ENOUGH ELEMENTS" << std::endl;
		return (data);
	}
	
	std::deque<unsigned int>::iterator it = current.begin();
	size_t	i = 0;
	while (i < size)
	{
		std::cout << "-----------------still has elements to distribute: i " << i << std::endl;
		std::cout << "it = " << *(it) << std::endl;
		if (i % 2 == 0)
		{
			std::cout << "pendiiiiing" << std::endl;
			data.pending.insert(data.pending.end(), it, it + 1);
			//std::cout << "pending container = ";
			//printContainer(data_.pending);
			it += 1;
		}
		else
		{		
			std::cout << "maiiiiiiiin" << std::endl;
			data.main.insert(data.main.end(), it, it + 1);
			//std::cout << "main container = ";
			//printContainer(data_.main);		
			it += 1 ;
		}
		i ++;
	}

	if (ite != current.end())
	{
		//std::cout << "remainiiiiiing" << std::endl;
		data.remaining.insert(data.remaining.end(), ite, current.end());
		std::cout << "[REMAINING] after distribution = ";
		printContainer(data.remaining);
	}

	std::cout << "[MAIN] after distribtion = ";
	printContainer(data.main);
	std::cout << "[PENDING] after distribution = ";
	printContainer(data.pending);
	return (data);
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

void	sortPairs(size_t blockSize, std::deque<unsigned int> &container, std::deque<unsigned int>::iterator max_)
{
	std::cout << "blocksize in SORT = " << blockSize << std::endl;
	for (std::deque<unsigned int>::iterator it = container.begin(); it + blockSize / 2 < max_; it += blockSize)
	{
		std::deque<unsigned int>::iterator ite = it + blockSize - 1;
		if (*(it + blockSize / 2 - 1) > *(ite))
		{
			//std::cout << "must swap it = " << *(it + size / 2 - 1) << " and ite = " << *(ite) << std::endl;
			swap_elements(blockSize / 2, it, it + blockSize / 2);
		}
	}
	std::cout << "sorted = ";
	printContainer(container);
}


size_t	getBlockSize(size_t size)
{
	size_t	blockSize = size;
	size_t	n = 2;
	while (n * 2 < size)
	{
		n *= 2;
	}
	if (n * 2 >= size)
	{
		blockSize = n;
	}
	return (blockSize);
}


std::deque<unsigned int>	jacobsthalMerge(std::deque<unsigned int> &main, std::deque<unsigned int> &pending, size_t blockSize, std::deque<size_t> &jacobsthal)
{
	std::deque<unsigned int>	merged;

	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	blockEnd;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = pending.size();
	//size_t								pending_nblocks = size / blockSize;
	size_t								difjac = jacobsthal[1] - jacobsthal[0];
	
	std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << std::endl;
	std::cout << "blocksize in MERGE = " << blockSize << std::endl;

	std::cout << "main = ";
	printContainer(main);
	std::cout << "pending = ";
	printContainer(pending);

	while (size >= difjac)
	{
		while (difjac > 0)
		{
			max_ = main.begin() + (jacobsthal[1] - 1) * blockSize;
			blockEnd = pending.begin() + (jacobsthal[1] - 1) * blockSize;
			std::cout << "[DEQ] jacobsthal ;  " << std::endl;
			binaryInsert(main, main.begin(), blockEnd, blockSize, max_);
			size --;
			difjac --;
		}
		update_jacobsthal(jacobsthal);
		difjac = jacobsthal[1] - jacobsthal[0];
	}
	size_t	i = 0;
	while (size > 0)
	{
		//max_ = container.begin() + (size * 2 - 1) * blockSize;
		max_ = main.begin() + (size - 1) * blockSize;
		blockEnd = pending.begin() + (size - 1) * blockSize;
		std::cout << "[DEQ] standard ; " << std::endl;
		binaryInsert(main, main.begin(), blockEnd, blockSize, max_);
		i ++;
		size --;
	}
	merged.insert(merged.end(), main.begin(), main.end());
	return (merged);
}

std::deque<unsigned int>	fordJohnson(t_dataDeq *data, size_t pairSize, size_t size, std::deque<unsigned int> &container)
{
	std::deque<unsigned int>	tmp;
	size_t						blockSize;

	if (size / 2 < 2)
		return (container);

	blockSize = getBlockSize(size);

	size_t								nblocks = container.size() / blockSize;
	size_t 								remaining = container.size() - nblocks * blockSize;
	std::deque<unsigned int>::iterator	ite = container.end() - remaining;

	sortPairs(pairSize, container, ite);

	*data = formMainAndPending(container, ite);

	tmp = fordJohnson(data, pairSize * 2, size / 2, data->main);

	std::cout << "tmp = ";
	printContainer(tmp);

	sortPairs(size, data->pending, data->pending.end()); // impression que c'est des comparaisons de trop + si mon main = 8 10 9 16 et mon pending = 14 2 13 11 par ex, je dois rien swap dans mon main mais je dois swap dans mon pending ==> casse la paire.
	tmp = jacobsthalMerge(tmp, data->pending, pairSize, data->jacobsthal);
	tmp.insert(tmp.end(), data->remaining.begin(), data->remaining.end());
	return (tmp);
}

void		PmergeMe::sortDequeue()
{
	t_dataDeq	data;
	data.jacobsthal.push_front(1);
	data.jacobsthal.push_front(0);

	this->deq = fordJohnson(&data, 2, this->deq.size(), this->deq);
}
