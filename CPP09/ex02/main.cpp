#include "PmergeMe.hpp"

template<typename T>
int	is_sorted(size_t size, T container)
{
	if (size != container.size())
	{
		std::cout << RED << "size KO : " << container.size() << DEFAULT << std::endl;
		return (0);
	}
	for (size_t i = 0; i + 1 < container.size(); i++)
	{
		if (container[i] > container[i + 1])
		{
			std::cout << RED << "sort KO : " << i << DEFAULT << std::endl;
			return (0);
		}	
	}
	return (1);
}


int	parse_arg(char *arg, std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	long int	tmpl = atoi(arg);
	if (tmpl > MAX_INT || tmpl < 0)
	{
		std::cerr << "Error: not an unsigned int." << std::endl;
		return (-1);
	}
	unsigned int tmp = static_cast<unsigned int>(tmpl);
	if (find(begin, end, tmp) != end)
	{
		std::cerr << "Error: duplicate." << std::endl;
		return (-1);
	}
	return ((int)tmp);
}



// microsecondes = secondes / 1000000 
int main(int argc, char **argv)
{
	//std::vector<unsigned int>	vec;
	std::deque<unsigned int>	deq;
    //clock_t						startVec, endVec;
    clock_t 					startDeq, endDeq;
	PmergeMe					p;
	size_t						size;


	// TEST: ./PmergeMe 14 12 8 4 2 1 7 10 13 6 9 5 11 3 16 15
	// after whole swapping, should be : 1 2 7 10 4 8 12 14 5 9 6 13 3 11 15 16
	if (argc < 3)
	{
		std::cerr << "Error: not enough arguments." << std::endl;
		return (0);
	}

	size = argc -1;

	/*startVec = clock();
	for (size_t i = 0; i < size; i++)
	{
		int tmp = parse_arg(argv[i + 1], vec.begin(), vec.end());
		if (tmp == -1)
			return (0);
		unsigned int ui = static_cast<unsigned int>(tmp)
		vec.push_back(ui);
	}
	p.setVec(vec.begin(), vec.end());
	std::cout << MAG << << "[VEC] Before : ";
	printContainer(vec);
	std::cout << DEFAULT;

	p.sortVector();
	endVec = clock();

	std::cout << MAG << "[VEC] After : ";
	vec = p.getDeq();
	printContainer(vec);
	std::cout << "[VEC] Time to process a range of " << dataVec.container.size() << " elements with std::" << "vector : " << static_cast<double>(endVec - startVec) * 1.0 << " us" << std::endl;
	std::cout << DEFAULT << std::endl;*/

	startDeq = clock();
	for (size_t i = 0; i < size; i++)
	{
		int tmp = parse_arg(argv[i + 1], deq.begin(), deq.end());
		if (tmp == -1)
			return (0);
		unsigned int ui = static_cast<unsigned int>(tmp);
		deq.push_back(ui);
	}
	p.setDeq(deq.begin(), deq.end());
	std::cout << MAG << "[DEQ] Before : ";
	printContainer(deq);
	std::cout << DEFAULT;

	p.sortDequeue();
    endDeq = clock();

	std::cout << MAG << "[DEQ] After : ";
	deq = p.getDeq();
	printContainer(deq);
	std::cout << "[DEQ] Time to process a range of " << p.getDeq().size() << " elements with std::" << "deque : " << static_cast<double>(endDeq - startDeq) * 1.0 << " us" << std::endl;
	std::cout << DEFAULT << std::endl;

	//if (!is_sorted(size, dataVec.container))
	//	std::cout << RED << "check: [VEC] KO." << DEFAULT << std::endl;
	if (!is_sorted(size, p.getDeq()))
		std::cout << RED << "check: [DEQ] KO." << DEFAULT << std::endl;
	//if (is_sorted(size, dataVec.container) && is_sorted(size, dataDeq.container))
	else
		std::cout << GREEN << "check: OK." << DEFAULT << std::endl;
	return (1);
}