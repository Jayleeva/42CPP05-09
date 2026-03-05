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

void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator ite, size_t blockSize, std::deque<unsigned int>::iterator max_)
{
	if (container.size() == 0 || *ite < *(container.begin()))
	{
		container.insert(container.begin(), ite - blockSize, ite);
		return ;
	}

	size_t								i = 0;
	std::deque<unsigned int>::iterator	it = container.begin();
	while (it + blockSize < max_) // doit aller jusqu'a l'ancien voisin
	{
		if (*ite > *(it) && *ite < *(it + blockSize))
		{
			container.insert(it, ite - blockSize, ite);
			return ;
		}
		it++;
		i++;
	}

	if (*ite > *(container.end() - blockSize) && *ite < *(max_)) // doit aller jusqu'a l'ancien voisin
	{
		container.insert(max_ - blockSize, ite - blockSize, ite); // doit aller jusqu'a l'ancien voisin
		return ;
	}
	if (*ite > *(container.end()))
	{
		container.insert(max_, ite - blockSize, ite); // doit aller jusqu'a l'ancien voisin
		return ;
	}
	//std::cout << "not inserted" << std::endl;
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

void	jacobsthalInsert(t_dataDeq *data, size_t blockSize)
{
	std::deque<unsigned int>::iterator	it;
	std::deque<unsigned int>::iterator	ite;
	std::deque<unsigned int>::iterator	max_;
	size_t								size = data->pending.size();
	size_t								pending_nblocks = size / blockSize;
	size_t								difjac = data->jacobsthal[1] - data->jacobsthal[0];
	
	std::cout << "jacob[1] = " << data->jacobsthal[1] << " jacob[0] = " << data->jacobsthal[0] << std::endl;// << " remaining = " << remaining << std::endl;
	
	// une fois un level fini, les blocs paires (0, 2, ..) sont les 'b', et les impaires sont les 'a'.
	// 	main = b1, a1, a2, a3, ...
	// 	pending = b2, b3, ...
	// si jacob[1] == 5, on commence par inserer b5, et a cause des swap etc precedents, on sait qu'il sera forcement avant a5:
	//   le binary insert se fait donc uniquement depuis le debut du main jusqu'au a5.
	// apres avoir insere b5, on insere b4, meme logique qu'avant. 
	// comme 5 - 3 = 2, on s'arrete la pour cette suite et on update jacobsthal.
	// jacob[1] == 11 desormais, on commence par inserer b11 (s'il existe).
	// s'il reste des blocs a inserer apres avoir epuise les jacobsthal, on commence par le dernier bloc, et comme avant, on sait qu'il sera forcement avant son ancien voisin.
	// 
	while (pending_nblocks >= difjac)
	{
		while (difjac > 0)
		{
			//max_ = ?
			//ite = ?
			std::cout << "[DEQ] jacobsthal ; pending. = " ; //<< *(data->pending.begin() + size / blockSize) << std::endl;
			binaryInsert(data->main, ite, blockSize, max_);
			pending_nblocks --;
			difjac --;
		}
		update_jacobsthal(data->jacobsthal);
		difjac = data->jacobsthal[1] - data->jacobsthal[0];
	}
	while (pending_nblocks > 0)
	{
		//max_ = ?
		ite = data->pending.begin() + size / blockSize;
		std::cout << "[DEQ] standard ; pending.begin() + size / blockSize = " << *(data->pending.begin() + size / blockSize) << std::endl;
		binaryInsert(data->main, ite, blockSize, max_);
		size -= size / blockSize;
		pending_nblocks --;
	}
}

std::deque<unsigned int>	mergeMainAndPending(t_dataDeq *data, bool must_insert, size_t fixedSize)
{
	std::deque<unsigned int>	merged;

	if (must_insert)
		jacobsthalInsert(data, fixedSize);
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
	
	/*data_.labels.push_back(data_.main.begin());
	data_.labels.push_back(data_.pending.begin());
	data_.labels.push_back(data_.main.begin() + fixedSize);*/

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

	/*size_t	i = 0;
	while (i < nblocks)
	{
		std::deque<unsigned int>::iterator	tmpit;
		if (i % 2 == 0)
			tmpit = data_.main.begin() + i * fixedSize;
		else
			tmpit = data_.pending.begin() + i * fixedSize;
		data_.labels.insert(data_.labels.end(), tmpit, tmpit + fixedSize);
		i ++;
	}*/
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

void		PmergeMe::sortDequeue()
{
	t_dataDeq	data;
	data.jacobsthal.push_front(1);
	data.jacobsthal.push_front(0);

	size_t	size = this->deq.size();
	swapping(size, this->deq);
	std::cout << "container after swapping = ";
	printContainer(this->deq);

	merging(size, this->deq, data.jacobsthal);
	//std::cout << "container after merging = ";
	//printContainer(this->container);
}
