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

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator elend, size_t blockSize, std::deque<unsigned int>::iterator max_)
{
	size_t								dist = distance(min_, max_) / blockSize;
	std::deque<unsigned int>::iterator	it;

	if (dist == 2)
	{
		if (*elend < *(min_))
			it = min_ - blockSize;
		else if (*elend > *(min_) && *elend < *(max_))
			it = min_;
		else if (*elend > *(max_))
			it = max_;
		container.insert(it, elend - blockSize, elend);
		return;
	}

	std::deque<unsigned int>::iterator	it;
	if (dist / 2 >= 1)
	{
		if (dist % 2 == 0)
			dist = dist / 2 - 1;
		else 
			dist /= 2;
		it = max_ - dist;
		if (*elend > *it)
			binaryInsert(container, it, elend, blockSize, max_);
		else if (*elend < *it)
			binaryInsert(container, min_, elend, blockSize, it);
	}
}


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

void	prepareLabels(t_dataDeq *data, size_t blockSize)
{
	size_t								nblocks = (data->pending.size() + data->main.size()) / blockSize;
	std::deque<unsigned int>::iterator 	mit = data->main.begin() + blockSize;
	std::deque<unsigned int>::iterator	pit = data->pending.begin() + blockSize;

	data->labels.push_back(mit);
	mit += blockSize;
	data->labels.push_back(mit);
	data->labels.push_back(pit);

	size_t	i = 3;
	while (i < nblocks)
	{
		if (i % 2 != 0)
		{
			mit += blockSize;
			data->labels.push_back(mit);
		}
		else
		{
			pit += blockSize;
			data->labels.push_back(pit);
		}
		i ++;
	}
}

void	jacobsthalInsert(t_dataDeq *data, size_t blockSize)
{
	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	elend;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = data->pending.size();
	size_t								pending_nblocks = size / blockSize;
	size_t								difjac = data->jacobsthal[1] - data->jacobsthal[0];
	
	std::cout << "jacob[1] = " << data->jacobsthal[1] << " jacob[0] = " << data->jacobsthal[0] << std::endl;// << " remaining = " << remaining << std::endl;
	
	// une fois un level fini, les blocs paires (0, 2, ..) sont les 'b', et les impaires sont les 'a'.
	// 	main = b1, a1, a2, a3, ...
	// 	pending = b2, b3, ...
	// si jacob[1] == 5, on commence par insérer b5, et à cause des swap etc précédents, on sait qu'il sera forcément avant a5:
	//   le binary insert se fait donc uniquement depuis le début du main jusqu'au a5.
	// après avoir inséré b5, on insère b4, même logique qu'avant. 
	// comme 5 - 3 = 2, on s'arrête là pour cette suite et on update jacobsthal.
	// jacob[1] == 11 désormais: on commence par insérer b11 s'il existe; s'il n'existe pas, on abandonne la logique jacobsthal.
	// s'il reste des blocs à insérer après avoir épuisé les jacobsthal, on commence par le dernier bloc, et comme avant, on sait qu'il sera forcément avant son ancien voisin.
	

	while (pending_nblocks >= difjac)
	{
		while (difjac > 0)
		{
			//max_ = ?
			//ite = ?
			std::cout << "[DEQ] jacobsthal ;  " ;
			binaryInsert(data->main, data->main.begin(), elend, blockSize, max_);
			pending_nblocks --;
			difjac --;
		}
		update_jacobsthal(data->jacobsthal);
		difjac = data->jacobsthal[1] - data->jacobsthal[0];
	}
	size_t	i = 0;
	while (pending_nblocks > 0)
	{
		if (i == 0) // si le bloc actuel est à la toute fin du pending
			max_ = data->main.end();
		/*else
			max_ = ?*/
		elend = data->pending.begin() + size / blockSize;
		std::cout << "[DEQ] standard ; pending.begin() + size / blockSize = " << *(data->pending.begin() + size / blockSize) << std::endl;
		binaryInsert(data->main, data->main.begin(), elend, blockSize, max_);
		size -= size / blockSize;
		i ++;
		pending_nblocks --;
	}
}

std::deque<unsigned int>	mergeMainAndPending(t_dataDeq *data, bool must_insert, size_t fixedSize)
{
	std::deque<unsigned int>	merged;

	if (must_insert)
	{
		prepareLabels(data, fixedSize);
		jacobsthalInsert(data, fixedSize);
	}
		
	else
		update_jacobsthal(data->jacobsthal);
		
	if (data->remaining.size())
	{
		std::cout << "insert remaining" << std::endl; // on rentre pas
		data->main.insert(data->main.end(), data->remaining.begin(), data->remaining.end());
	}

	merged.insert(merged.end(), data->main.begin(), data->main.end());
	return (merged);
}

std::deque<unsigned int>	formMainAndPending(std::deque<unsigned int>::iterator ite, size_t fixedSize, std::deque<unsigned int> &current, std::deque<size_t> &jacobsthal)
{
	//main = 'b1' puis tous les 'a' : premier bloc, deuxième bloc, puis un sur deux (4ème, 6ème...)
	//pending = tous les autres 'b' : troisième bloc, puis un sur sur deux (5ème, 7ème...)
	t_dataDeq	data_;
	std::deque<unsigned int>	res;
	std::deque<unsigned int>::iterator begin = current.begin();

	data_.jacobsthal = jacobsthal;

	static size_t	n = 1;
	if (n < 3)
	{
		data_.main.insert(data_.main.end(), begin, current.end());
		std::cout << "FIRST / SECOND" << std::endl;
		n ++;
		res = mergeMainAndPending(&data_, 0, fixedSize);
		return (res);
	}

	std::cout << "ite = " << *(ite -1) << std::endl;

	if (ite != current.end())
	{
		std::cout << "remainiiiiiing" << std::endl;
		data_.remaining.insert(data_.remaining.end(), ite, current.end());
		//std::cout << "[REMAINING] after distribution = ";
		//printContainer(data_.remaining);
	}

	data_.main.insert(data_.main.end(), begin, begin + fixedSize * 2);
	data_.pending.insert(data_.pending.end(), begin + fixedSize * 2, begin + fixedSize * 3);

	std::deque<unsigned int>::iterator it = begin + fixedSize * 3;

	size_t	nblocks = current.size() / fixedSize - 3;
	size_t	i = 0;
	while (i < nblocks)
	{
		std::cout << "-----------------still has elements to distribute" << std::endl;
		std::cout << "it = " << *(it -1) << std::endl;
		if (i % 2 == 0)
		{
			std::cout << "maiiiiiiiin" << std::endl;
			data_.main.insert(data_.main.end(), it, it + fixedSize);
			//std::cout << "main container = ";
			//printContainer(data_.main);		
			it += fixedSize;
		}
		else
		{
			std::cout << "pendiiiiing" << std::endl;
			data_.pending.insert(data_.pending.end(), it, it + fixedSize);
			//std::cout << "pending container = ";
			//printContainer(data_.pending);
			it += fixedSize;	
		}
		i ++;
	}
	std::cout << "[MAIN] after distribtion = ";
	printContainer(data_.main);
	std::cout << "[PENDING] after distribution = ";
	printContainer(data_.pending);
	res = mergeMainAndPending(&data_, 1, fixedSize);
	return (res);
}

void	merging(size_t size, std::deque<unsigned int> &container, std::deque<size_t> &jacobsthal) //, std::deque<unsigned int> &current)
{
	if (size / 2 >= 1)
	{
		size_t	fixedSize = size;
		size_t	n = 2;
		while (n * 2 < size)
		{
			n *= 2;
		}

		if (n * 2 > size)
		{
			fixedSize = n;
		}

		size_t nlvl = 0;
		while (fixedSize * nlvl < container.size())
			nlvl ++;
		if (fixedSize * nlvl > container.size())
		{
			nlvl --;
		}
		size_t remaining = container.size() - fixedSize * nlvl;
		std::cout << "entered merging with lvl = " << nlvl << " remaining = " << remaining << " and fixedSize = " << fixedSize << std::endl;
		container = formMainAndPending(container.end() - remaining, fixedSize, container, jacobsthal);
		std::cout << "merged container = ";
		printContainer(container);
		jacobsthal = update_jacobsthal(jacobsthal);
		merging(size / 2, container, jacobsthal);
	}
}

void	fordJohnson(t_dataDeq *data, size_t size, std::deque<unsigned int> &container)
{
	std::deque<unsigned int> newContainer;

	if (n de pair < 2)
		return pair;

	swapping(pair[])
	data = formMainAndPending(data, size, container);
	newContainer = pair(main)

	sortedmain[] = ford-jonhson(newContainer)

	sortedpending[] = sortedpair[pair] -> new position des éléments du pending
	result = mergeWithJacobsthal(sortedpair, pending)
	return result;
}



void		PmergeMe::sortDequeue()
{
	//pair = { petit : grand }
	t_dataDeq	data;
	data.jacobsthal.push_front(1);
	data.jacobsthal.push_front(0);

	size_t	size = this->deq.size();
	fordJohnson(&data, size, this->deq);
	
	/*swapping(size, this->deq);
	std::cout << "container after swapping = ";
	printContainer(this->deq);

	merging(size, this->deq, data.jacobsthal);*/
	//std::cout << "container after merging = ";
	//printContainer(this->container);
}
