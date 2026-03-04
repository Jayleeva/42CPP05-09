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
		this->container = original.container;
		//this->dataDeq.container = original.dataDeq.container;
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
	return (this->container);
}

void	PmergeMe::setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->container.insert(this->container.end(), begin, end);
}

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}

void	binaryInsert(std::deque<unsigned int> &container, unsigned int ui)
{
	size_t			i = 0;

	if (container.size() == 0)
	{
		container.push_back(ui);
		return ;
	}

	if (ui < container[0])
	{
		container.insert(container.begin(), ui);
		return ;
	}
	std::deque<unsigned int>::iterator it = container.begin() + i;
	while (i + 1 < container.size())
	{
		if (ui > container[i] && ui < container[i + 1])
		{
			container.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > container[container.size() -1] && ui < container[container.size()])
	{
		container.insert(it + 1, ui);
		return ;
	}
	if (ui > container[container.size()])
	{
		container.push_back(ui);
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

void	jacobsthalInsert(t_dataDeq *data)
{

	size_t				size = data->pending.size();
	size_t				n = 0;

	update_jacobsthal(data->jacobsthal);
	//std::cout << "[DEQ] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	/*if (size == 0)
	{
		data->main.push_back(data->pending[i]);
		return ;
	}*/

	std::cout << "jacob[1] = " << data->jacobsthal[1] << " jacob[0] = " << data->jacobsthal[0] << std::endl;// << " remaining = " << remaining << std::endl;
	n = data->jacobsthal[1] - data->jacobsthal[0];
	if (n < size)
	{
		while (size > 0)
		{
			std::cout << "[DEQ] standard; pending[i] = " << data->pending[size -1] << std::endl; // PAS UN UNSIGNED INT PAR UNSIGNED INT, MAIS UN ELEMENT PAR ELEMENT!
			binaryInsert(data->main, data->pending[size -1]);
			size --;
		}
	}
	else
	{
		while (n > 0)
		{
			std::cout << "[DEQ] jacobsthal; pending[jacobsthal[1] = " <<  data->pending[data->jacobsthal[1]] << std::endl;
			binaryInsert(data->main, data->pending[data->jacobsthal[1]]);
			n --;
		}
	}	
}

std::deque<unsigned int>	mergeMainAndPending(t_dataDeq *data, bool must_insert)
{
	std::deque<unsigned int>	merged;

	if (must_insert)
		jacobsthalInsert(data);
		
	if (data->remaining.size())
	{
		std::cout << "insert remaining" << std::endl; // on rentre pas
		data->main.insert(data->main.end(), data->remaining.begin(), data->remaining.end());
	}

	merged.insert(merged.end(), data->main.begin(), data->main.end());
	return (merged);
}

std::deque<unsigned int>	formMainAndPending(std::deque<unsigned int>::iterator ite, size_t fixedSize, std::deque<unsigned int> &current, std::deque<size_t> &jacobsthal)//t_dataDeq *data)
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
		res = mergeMainAndPending(&data_, 0);
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

	while (1)
	{
		std::cout << "-----------------still has elements to distribute" << std::endl;
		std::cout << "it = " << *(it -1) << std::endl;
		if (it + fixedSize <= ite)
		{
			std::cout << "maiiiiiiiin" << std::endl;
			data_.main.insert(data_.main.end(), it, it + fixedSize);
			//std::cout << "main container = ";
			//printContainer(data_.main);		
			it += fixedSize;
		}
		else
			break;

		if (it + fixedSize <= ite)
		{
			std::cout << "pendiiiiing" << std::endl;
			data_.pending.insert(data_.pending.end(), it, it + fixedSize);
			//std::cout << "pending container = ";
			//printContainer(data_.pending);
			it += fixedSize;	
		}
		else
			break;
	}
	std::cout << "[MAIN] after distribtion = ";
	printContainer(data_.main);
	std::cout << "[PENDING] after distribution = ";
	printContainer(data_.pending);
	res = mergeMainAndPending(&data_, 1);
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

	size_t	size = this->container.size();
	swapping(size, this->container);
	std::cout << "container after swapping = ";
	printContainer(this->container);

	merging(size, this->container, data.jacobsthal);
	//std::cout << "container after merging = ";
	//printContainer(this->container);
}
