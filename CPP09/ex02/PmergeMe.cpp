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

void	sortPairs(size_t blockSize, size_t iteration, std::deque<unsigned int> &main, std::deque<size_t> &mustSwap, std::deque<unsigned int>::iterator max_)
{
	size_t	i = 0;
	for (std::deque<unsigned int>::iterator it = main.begin(); it + blockSize / 2 < max_; it += blockSize)
	{
		g_counter ++;
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

void	formMainAndPending(t_dataDeq *data, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite) //size_t blockSize, std::deque<size_t> &mustSwap,
{
	size_t	size = current.size();

	//std::cout << "blocksize in FORM = " << blockSize << std::endl;

	if (size < 2)
	{
		data->main.insert(data->main.end(), current.begin(), current.end());
		std::cout << "NOT ENOUGH ELEMENTS" << std::endl;
		return ;
	}

	std::cout << "container before distributing = ";
	printContainer(current);
	std::cout << "size = " << size << std::endl;//<< ", blockSize = " << blockSize << ", size / blockSize = " << size / blockSize << std::endl;
	std::deque<unsigned int>::iterator it = current.begin();

	size_t	i = 0;
	while (i < size / 2)
	{
		//std::cout << "-----------------still has elements to distribute: " << std::endl;
		//std::cout << "it + 1 = " << *(it + 1) << std::endl;
		//if (blockSize == 2)
		//{
			data->pending.push_back(*it);
			it ++;
			data->main.push_back(*it);
			it ++;
			i ++;
		/*}
		else
		{
			std::cout << "pendiiiiing" << std::endl;
			data->pending.insert(data->pending.end(), it, it + blockSize /2 -1);
			it += blockSize /2;

			std::cout << "maiiiiiiiin" << std::endl;
			data->main.insert(data->main.end(), it, it + blockSize /2 -1);	
			it += blockSize /2;
		
			i ++;
		}*/
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


void	sortPending(std::deque<size_t> mustSwap, std::deque<unsigned int> &pending)
{
	if (mustSwap.empty())
		return;

	std::deque<unsigned int>::iterator pit;
	for (std::deque<size_t>::iterator it = mustSwap.begin() ; it < mustSwap.end(); it ++)
	{
		g_counter ++;
		pit = pending.begin() + *it;
		std::cout << "*it = " << *it << " pit = " << *pit << std::endl;
		swap_elements(1, pit, pit + 1);
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

/*size_t	getContainerIt(std::deque<unsigned int> container, std::deque<unsigned int>::iterator it)
{
	size_t	i = 0;
	while (container.begin() + i < it)
		i ++;
	return (i);
}*/

void	binarySearch(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator blockEnd, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, size_t *pos) //, size_t *last)
{
	size_t								dist = distance(min_, max_) + 1;
	std::deque<unsigned int>::iterator	it;

	//std::cout << "blockEnd = " << *(blockEnd) << " min = " << (*min_) << " max = " << *(max_) << " dist = " << dist << std::endl;
	if (dist <= 2 )
	{
		if (*blockEnd < *(min_))
			it = min_ ;
		else if (*blockEnd > *(min_) && *blockEnd < *(max_))
			it = min_ + 1;
		else if (*blockEnd > *(max_))
			it = max_;
		//*last = distance(container.begin(), it);
		//*pos = it;
		*pos = distance(container.begin(), it);
		//container.insert(it, *(blockEnd));
		g_counter ++;
		return ;
	}

	if (dist > 2)
	{
		size_t	middle = dist / 2;
		//std::cout << "middle = " << *(container.begin() + middle) << std::endl;
		it = min_ + middle;
		g_counter ++;
		if (*blockEnd > *it)
			binarySearch(container, blockEnd, it, max_, pos); // last);
		else if (*blockEnd < *it)
			binarySearch(container, blockEnd, min_, it, pos); //, last);
	}
}


std::deque<unsigned int>	jacobsthalMerge(std::deque<size_t> &jacobsthal, t_dataDeq data)
{
	std::deque<unsigned int>	merged;

	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	blockEnd;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = data.pending.size();
	//size_t								difjac = jacobsthal[1] - jacobsthal[0];
	
	//data.main.insert(data.main.begin(), *(data.pending.begin())); // mettre b1 directement avant a1

	/*merged.insert(merged.end(), *(data.pending.begin()));
	merged.insert(merged.end(), *(data.main.begin()));*/

	(void)jacobsthal;
	/*std::cout << "main = ";
	printContainer(data->main);
	std::cout << "pending = ";	 			//pas bon passé un certain niveau
	printContainer(data->pending);*/

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


	std::deque<size_t>	pos_;
	size_t				pos;
	//std::deque<unsigned int>::iterator	pos;
	
	size_t	i = 0;
	while (size > 0)
	{
		max_ = data.main.begin() + (size -1);
		blockEnd = data.pending.begin() + (size -1);
		std::cout << "[DEQ] standard ; " << std::endl;
		binarySearch(data.main, blockEnd, data.main.begin(), max_, &pos);
		pos_.push_back(pos);
		i ++;
		size --;
	}

	/*size_t	totalSize = data.pending.size() + data.main.size();
	size_t	j = 0;
	size_t	k = 0;
	while (j < totalSize -1)
	{
		
		if (j == pos_[k])
		{
			std::cout << "j = " << j << " pos_k = " << pos_[k] << " pending[i] " << data.pending[i] << std::endl;
			merged.push_back(data.pending[i]);
			k ++;
		}
			
		else
		{
			std::cout << "j = " << j << " pos_k = " << pos_[k] << " main[i] " << data.main[i] << std::endl;
			merged.push_back(data.main[i]);
		}
			
		i --;
		j ++;
	}*/

	/*std::deque<unsigned int>::iterator mit = data.main.begin()
	size_t j = 0;
	while (j < i)
	{
		std::cout << "blockEnd = " << *(data.pending.begin() + j) << " pos = " << *(pos_[j]) << std::endl;
		data.main.insert(pos_[j], *(data.pending.begin() + j)); // même problème que dans l'autre sens: main.begin() change.... il faudrait commencer l'insertion à la première itération.
		if () //itérateur d'insertion pos_[j] distance(tmp, pos_[j]))
		j ++;
	}
	merged.insert(merged.end(), data.main.begin(), data.main.end());*/

	merged.insert(merged.end(), data.remaining.begin(), data.remaining.end());
	return (merged);
}



std::deque<unsigned int>	fordJohnson(std::deque<size_t> &jacobsthal, size_t iteration, size_t size, std::deque<unsigned int> &main, std::deque<unsigned int> &pending)
{
	t_dataDeq					data;
	std::deque<unsigned int>	tmp;
	std::deque<size_t>			mustSwap;
	size_t						blockSize;

	if (size / 2 < 2)
	{
		return (main);
	}

	blockSize = getBlockSize(size);

	size_t								nblocks = main.size() / blockSize;
	size_t 								remaining = main.size() - nblocks * blockSize;
	std::deque<unsigned int>::iterator	ite = main.end() - remaining;

	sortPairs(2, iteration, main, mustSwap, ite);

	if (!pending.empty())
		sortPending(mustSwap, pending);
	std::cout << "sorted pending = ";
	printContainer(pending);
	
	formMainAndPending(&data, main, ite);

	tmp = fordJohnson(jacobsthal, iteration + 1, size / 2, data.main, data.pending);

	std::cout << "******************************** tmp = ";
	printContainer(tmp);
	data.main = tmp;
	std::cout << "*** main = ";
	printContainer(data.main);

	tmp = jacobsthalMerge(jacobsthal, data);
	return (tmp);
}

void		PmergeMe::sortDequeue()
{
	std::deque<size_t>	jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	std::deque<unsigned int>	pending;
	this->deq = fordJohnson(jacobsthal, 0, this->deq.size(), this->deq, pending);
	std::cout << YELLOW << "Comparaison counter = " << g_counter << DEFAULT << std::endl;
}