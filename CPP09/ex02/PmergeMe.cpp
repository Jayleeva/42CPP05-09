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

std::deque<size_t>	update_jacobsthal(std::deque<size_t> &jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}

t_dataDeq	formMainAndPending(std::deque<unsigned int> &current, size_t blockSize, std::deque<unsigned int>::iterator ite)
{
	t_dataDeq							data;
	size_t								size = current.size();

	std::cout << "blocksize in FORM = " << blockSize << std::endl;

	if (size < 2)
	{
		data.main.insert(data.main.end(), current.begin(), current.end());
		std::cout << "NOT ENOUGH ELEMENTS" << std::endl;
		return (data);
	}

	std::cout << "container before distributing = ";
	printContainer(current);
	std::cout << "size = " << size << ", blockSize = " << blockSize << ", size / blockSize = " << size / blockSize << std::endl;
	std::deque<unsigned int>::iterator it = current.begin();



	size_t	i = 0;
	while (i < size / blockSize)
	{
		std::cout << "-----------------still has elements to distribute: " << std::endl;
		std::cout << "it + blockSize -1 = " << *(it + blockSize -1) << std::endl;
		if (blockSize == 2)
		{
			data.pending.push_back(*it);
			it ++;
			data.main.push_back(*it);
			it ++;
			i ++;
		}
		else
		{
			std::cout << "pendiiiiing" << std::endl;
			data.pending.insert(data.pending.end(), it, it + blockSize /2 -1);
			it += blockSize /2;

			std::cout << "maiiiiiiiin" << std::endl;
			data.main.insert(data.main.end(), it, it + blockSize /2 -1);	
			it += blockSize /2;
		
			i ++;
		}
	}

	if (ite != current.end())
	{
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
	//std::cout << "blocksize in SORT = " << blockSize << std::endl;
	for (std::deque<unsigned int>::iterator it = container.begin(); it + blockSize / 2 < max_; it += blockSize)
	{
		std::deque<unsigned int>::iterator ite = it + blockSize / 2; // -1
		if (*(it + blockSize / 2 - 1) > *(ite))
			swap_elements(blockSize / 2, it, it + blockSize / 2);
	}
	//std::cout << "sorted = ";
	//printContainer(container);
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

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator blockEnd, size_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_)
{
	size_t								dist = distance(min_, max_) + 1;
	std::deque<unsigned int>::iterator	it;

	std::cout << "blockEnd = " << *(blockEnd) << " min = " << (*min_) << " max = " << *(max_) << std::endl;
	if (dist == 2)
	{
		if (*blockEnd < *(min_))
			it = min_ ; 
		else if (*blockEnd > *(min_) && *blockEnd < *(max_))
			it = min_ + 1; // + blockSize;
		else if (*blockEnd > *(max_))
			it = max_;
		container.insert(it, *(blockEnd)); // it - blockSize, blockEnd);
		return;
	}

	if (dist > 2)
	{
		if (dist % 2 == 0)
			dist = dist / 2 - 1;
		else 
			dist /= 2;
		it = max_ - dist;
		if (*blockEnd > *it)
			binaryInsert(container, blockEnd, blockSize, it, max_);
		else if (*blockEnd < *it)
			binaryInsert(container, blockEnd, blockSize, min_, it);
	}
}


std::deque<unsigned int>	jacobsthalMerge(t_dataDeq *data, size_t blockSize)
{
	std::deque<unsigned int>	merged;

	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	blockEnd;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = data->pending.size();
	size_t								difjac = data->jacobsthal[1] - data->jacobsthal[0];
	
	std::cout << "jacob[0] = " << data->jacobsthal[0] << " jacob[1] = " << data->jacobsthal[1] << std::endl;

	/*std::cout << "main = ";
	printContainer(data->main);
	std::cout << "pending = ";	 			//pas bon passé un certain niveau
	printContainer(data->pending);*/

	while (size >= difjac) // du coup size pas bonne, du coup on rentre trop souvent dans jacobsthal;
	{
		size_t	i = 0;
		while (difjac > 0)
		{
			max_ = data->main.begin() + ((data->jacobsthal[1]) + i) * blockSize; // -1  * blockSize;
			blockEnd = data->pending.begin() + (data->jacobsthal[1] - i) * blockSize; // -1 * blockSize;
			std::cout << "[DEQ] jacobsthal ;  " << std::endl;
			binaryInsert(data->main, blockEnd, blockSize, data->main.begin(), max_);
			i ++;
			size --;
			difjac --;
		}
		update_jacobsthal(data->jacobsthal);
		difjac = data->jacobsthal[1] - data->jacobsthal[0];
	}
	size_t	i = 0;
	while (size > 0)	// du coup pas bonne ici non plus
	{
		max_ = data->main.begin() + (size); // -1 )* blockSize;
		blockEnd = data->pending.begin() + (size -1); // - 1); // * blockSize;
		std::cout << "[DEQ] standard ; " << std::endl;
		binaryInsert(data->main, blockEnd, blockSize, data->main.begin(), max_);
		i ++;
		size --;
	}
	merged.insert(merged.end(), data->main.begin(), data->main.end());
	return (merged);
}

std::deque<unsigned int>	fordJohnson(t_dataDeq *data, size_t pairSize, size_t size, std::deque<unsigned int> &container)
{
	std::deque<unsigned int>	tmp;
	//std::deque<unsigned int>	main;
	//std::deque<unsigned int>	pending;
	size_t						blockSize;

	if (size / 2 < 2)
		return (container);

	blockSize = getBlockSize(size);

	size_t								nblocks = container.size() / blockSize;
	size_t 								remaining = container.size() - nblocks * blockSize;
	std::deque<unsigned int>::iterator	ite = container.end() - remaining;

	sortPairs(pairSize, container, ite);

	*data = formMainAndPending(container, pairSize, ite);

	//main.insert(main.end(), data->main.begin(), data->main.end());
	//pending.insert(pending.end(), data->pending.begin(), data->pending.end());
	tmp = fordJohnson(data, pairSize * 2, size / 2, container);

	std::cout << "******************************** tmp = ";
	printContainer(tmp);

	//sortPairs(size, data->pending, data->pending.end()); // impression que c'est des comparaisons de trop + si mon main = 8 10 9 16 et mon pending = 14 2 13 11 par ex, je dois rien swap dans mon main mais je dois swap dans mon pending ==> casse la paire.
	
	//data->jacobsthal.push_back(0);
	//data->jacobsthal.push_back(1);

	tmp = jacobsthalMerge(data, pairSize);
	tmp.insert(tmp.end(), data->remaining.begin(), data->remaining.end());
	return (tmp);
}

void		PmergeMe::sortDequeue()
{
	t_dataDeq	data;
	data.jacobsthal.push_back(0);
	data.jacobsthal.push_back(1);

	this->deq = fordJohnson(&data, 2, this->deq.size(), this->deq);
}
