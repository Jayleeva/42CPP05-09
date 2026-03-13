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

void	update_jacobsthal(std::deque<size_t> &jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
}

void	formMainAndPending(t_dataDeq *data, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite, size_t blockSize)
{
	size_t	size = current.size();

	if (size < 2)
	{
		data->main.insert(data->main.end(), current.begin(), current.end());
		std::cout << "NOT ENOUGH ELEMENTS" << std::endl;
		return ;
	}

	std::cout << "container before distributing = ";
	printContainer(current);
	std::cout << "size = " << size << " blocksize = " << blockSize << std::endl;
	std::deque<unsigned int>::iterator it = current.begin();

	size_t	i = 0;
	while (i < size / 2)
	{
		if (blockSize == 2)
		{
			data->pending.push_back(*it);
			it ++;
			data->main.push_back(*it);
			it ++;
		}
		else
		{
			std::cout << "here" << std::endl;
			data->pending.insert(data->pending.end(), it, it + blockSize / 2);
			it += blockSize / 2 + 1;
			data->main.insert(data->main.end(), it, it + blockSize / 2);
			it += blockSize / 2 + 1;
		}
		i ++;
	}

	if (ite != current.end())
	{
		data->remaining.insert(data->remaining.end(), ite, current.end());
		std::cout << "[REMAINING] after distribution = ";
		printContainer(data->remaining);
	}

	std::cout << "[MAIN] after distribtion = ";
	printContainer(data->main);
	std::cout << "[PENDING] after distribution = ";
	printContainer(data->pending);
	return ;
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

void	sortPairs(size_t blockSize, size_t iteration, std::deque<unsigned int> &main, std::deque<size_t> &mustSwap, std::deque<unsigned int>::iterator max_)
{
	size_t	i = 0;
	for (std::deque<unsigned int>::iterator it = main.begin(); it + blockSize / 2 < max_; it += blockSize)
	{
		std::deque<unsigned int>::iterator ite = it + blockSize / 2;
		if (*(it + blockSize / 2 - 1) > *(ite))
		{
			swap_elements(blockSize / 2, it, it + blockSize / 2);
			if (iteration > 0)
			{
				std::cout << "must swap = " << i << std::endl;
				mustSwap.push_back(i);
			}
				
		}
		i += blockSize;
	}
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

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator blockEnd, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, size_t *last)
{
	size_t								dist = distance(min_, max_) + 1;
	std::deque<unsigned int>::iterator	it;

	std::cout << "blockEnd = " << *(blockEnd) << " min = " << (*min_) << " max = " << *(max_) << " dist = " << dist << std::endl;
	if (dist <= 2 )
	{
		if (*blockEnd < *(min_))
			it = min_ ;
		else if (*blockEnd > *(min_) && *blockEnd < *(max_))
			it = min_ + 1;
		else if (*blockEnd > *(max_))
			it = max_;
		*last = distance(container.begin(), it);
		container.insert(it, *(blockEnd));
		return ;
	}

	if (dist > 2)
	{
		size_t	middle = dist / 2;
		std::cout << "middle = " << *(container.begin() + middle) << std::endl;
		it = min_ + middle;
		if (*blockEnd > *it)
			binaryInsert(container, blockEnd, it, max_, last);
		else if (*blockEnd < *it)
			binaryInsert(container, blockEnd, min_, it, last);
	}
}


std::deque<unsigned int>	jacobsthalMerge(std::deque<size_t> &jacobsthal, t_dataDeq data)
{
	std::deque<unsigned int>	merged;

	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	blockEnd;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = data.pending.size();
	size_t								difjac = jacobsthal[1] - jacobsthal[0];
	
	std::cout << "* to insert = ";
	printContainer(data.pending);

	(void)jacobsthal;						// essayons déjà de faire marcher le schmilblik sans ça
	(void)difjac;
	/*while (size >= difjac)				
	{
		std::cout << "jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;
		size_t	i = 0;
		while (difjac > 0)
		{
			max_ = data.main.begin() + (jacobsthal[1] + i);
			blockEnd = data.pending.begin() + (jacobsthal[1] - i);
			std::cout << "[DEQ] jacobsthal ;  " << std::endl;
			binaryInsert(data.main, blockEnd, data.main.begin(), max_);
			i ++;
			size --;
			difjac --;
		}
		update_jacobsthal(jacobsthal);
		difjac = jacobsthal[1] - jacobsthal[0];
	}*/
	size_t	last = size -1;
	size_t	i = 0;
	while (size > 0)
	{
		max_ = data.main.begin() + last; 	// main.begin + last = où a été placé le dernier. Fonctionne uniquement si pending a bien été swap quand nécessaire
		blockEnd = data.pending.begin() + (size -1);
		std::cout << "[DEQ] standard ; " << std::endl;
		binaryInsert(data.main, blockEnd, data.main.begin(), max_, &last);
		i ++;
		size --;
	}
	merged.insert(merged.end(), data.main.begin(), data.main.end());
	merged.insert(merged.end(), data.remaining.begin(), data.remaining.end());
	return (merged);
}

void	sortPending(std::deque<size_t> mustSwap, std::deque<unsigned int> &pending)
{
	if (mustSwap.empty())
		return;

	std::deque<unsigned int>::iterator pit;
	for (std::deque<size_t>::iterator it = mustSwap.begin() ; it < mustSwap.end(); it ++)
	{
		
		pit = pending.begin() + *it;
		std::cout << "*it = " << *it << " pit = " << *pit << std::endl;
		swap_elements(1, pit, pit + 1);
	}
}

std::deque<unsigned int>	fordJohnson(std::deque<size_t> &jacobsthal, size_t pairSize, size_t iteration, size_t size, std::deque<unsigned int> &container)
{
	t_dataDeq					data;
	std::deque<unsigned int>	tmp;
	std::deque<size_t>			mustSwap;
	size_t						blockSize;

	if (size / 2 < 2)
	{
		return (container);
	}
	
	blockSize = getBlockSize(size);

	size_t								nblocks = container.size() / blockSize;
	size_t 								remaining = container.size() - nblocks * blockSize;
	std::deque<unsigned int>::iterator	ite = container.end() - remaining;
	
	sortPairs(pairSize, iteration, container, mustSwap, ite); 

	

	tmp = fordJohnson(jacobsthal, pairSize * 2, iteration + 1, size / 2, container);

	
	std::cout << "******************************** tmp = ";
	printContainer(tmp);
	/*data.main = tmp; 		// pas même que tmp for some reason
	std::cout << "*** main = ";
	printContainer(data.main);*/

	formMainAndPending(&data, container, ite, blockSize);

	/*if (size / 2 >= 2)	// comment utiliser le mustswap de l'itération précédente????
	{
		sortPending(mustSwap, data.pending);
		std::cout << "sorted pending = ";
		printContainer(data.pending);
	}*/

	tmp = jacobsthalMerge(jacobsthal, data);
	return (tmp);
}

void		PmergeMe::sortDequeue()
{
	std::deque<size_t>	jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	this->deq = fordJohnson(jacobsthal, 2, 0, this->deq.size(), this->deq);
}
