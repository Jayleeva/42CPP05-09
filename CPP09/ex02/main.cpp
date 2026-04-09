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

int	parse_argVec(char *arg, std::vector<unsigned int> vec)
{
	long int	tmpl = atoi(arg);
	if (tmpl > MAX_INT || tmpl < 0)
	{
		std::cerr << "Error: not an unsigned int." << std::endl;
		return (-1);
	}
	unsigned int tmp = static_cast<unsigned int>(tmpl);
	if (find(vec.begin(), vec.end(), tmp) != vec.end())
	{
		std::cerr << "Error: duplicate." << std::endl;
		return (-1);
	}
	return ((int)tmp);
}

int	parse_argDeq(char *arg, std::deque<unsigned int> deq)
{
	long int	tmpl = atoi(arg);
	if (tmpl > MAX_INT || tmpl < 0)
	{
		std::cerr << "Error: not an unsigned int." << std::endl;
		return (-1);
	}
	unsigned int tmp = static_cast<unsigned int>(tmpl);
	if (find(deq.begin(), deq.end(), tmp) != deq.end())
	{
		std::cerr << "Error: duplicate." << std::endl;
		return (-1);
	}
	return ((int)tmp);
}

// us = microsecondes = secondes / 1000000. ms = millisecondes = secondes / 1000.
int main(int argc, char **argv)
{
	std::vector<unsigned int>	vec;
	std::deque<unsigned int>	deq;
    clock_t						startVec, endVec;
    clock_t 					startDeq, endDeq;
	PmergeMe					p;
	size_t						size;

	//TEST: ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
	// TEST: ./PmergeMe 14 12 8 4 2 1 7 10 13 6 9 5 11 3 16 15
	// after whole swapping, should be : 1 2 7 10 4 8 12 14 5 9 6 13 3 11 15 16
	if (argc < 3)
	{
		std::cerr << "Error: not enough arguments." << std::endl;
		return (0);
	}

	size = argc -1;

	startVec = clock();
	for (size_t i = 0; i < size; i++)
	{
		int tmp = parse_argVec(argv[i + 1], vec);
		if (tmp == -1)
			return (0);
		unsigned int ui = static_cast<unsigned int>(tmp);
		vec.push_back(ui);
	}
	p.setVec(vec.begin(), vec.end());
	std::cout << MAG << "[VEC] Before : ";
	printContainer(vec, 0);
	std::cout << DEFAULT;

	ssize_t counterVec = p.sortVector();
	endVec = clock();

	std::cout << MAG << "[VEC] After : ";
	vec = p.getVec();
	printContainer(vec, 0);
	std::cout << "[VEC] Time to process a range of " << p.getVec().size() << " elements with std::" << "vector : " << static_cast<double>(endVec - startVec) / 1000.0 << " ms" << DEFAULT << std::endl;

	startDeq = clock();
	for (size_t i = 0; i < size; i++)
	{
		int tmp = parse_argDeq(argv[i + 1], deq);
		if (tmp == -1)
			return (0);
		unsigned int ui = static_cast<unsigned int>(tmp);
		deq.push_back(ui);
	}

	p.setDeq(deq.begin(), deq.end());
	std::cout << MAG << "\n[DEQ] Before : ";
	printContainer(deq, 0);
	std::cout << DEFAULT;

	ssize_t counterDeq = p.sortDequeue();
    endDeq = clock();

	deq = p.getDeq();
	std::cout << MAG << "[DEQ] After : ";
	printContainer(deq, 0);
	std::cout << MAG << "[DEQ] Time to process a range of " << p.getDeq().size() << " elements with std::" << "deque : " << static_cast<double>(endDeq - startDeq) / 1000.0 << " ms" << DEFAULT << std::endl;

	if (!is_sorted(size, p.getVec()))
		std::cout << RED << "check: [VEC] KO." << DEFAULT << std::endl;
	else
		std::cout << GREEN << "check: [VEC] OK." << DEFAULT << std::endl;
	if (!is_sorted(size, p.getDeq()))
		std::cout << RED << "check: [DEQ] KO." << DEFAULT << std::endl;
	else
		std::cout << GREEN << "check: [DEQ] OK." << DEFAULT << std::endl;

	if (VERBIOSE)
	{
		std::cout << YELLOW << "Comparaisons [VEC] : " << counterVec << DEFAULT << std::endl;
		std::cout << YELLOW << "Comparaisons [DEQ] : " << counterDeq << DEFAULT << std::endl;
	}
	return (1);
}