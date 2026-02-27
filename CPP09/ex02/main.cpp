#include "PmergeMe.hpp"
//DEQ ne marche pas parfois, ne parvient pas a push un des elements. VEc n'a pas ce probleme.


// Ford-Johnson: 
// - organiser le container par paires 
// - trier l'interieur des paires: le plus petit de la paire en premier, le plus grand de la paire en deuxieme
// - former des paires de paires (a, b), si reste un nombre, son max devient bn.
// - trier les paires de paires en ne comparant que les b (max) de chaque paire de paires.
//

// recursif. On fait des paires de paires de paires de paires de paires.... jusqu'a ???? ce que ce qui reste ne puisse plus etre mis en paire de paire de paire

// comment utiliser un container du coup? puisque va avoir un nombre de "couches" differentes en fonction de la longueur de la suite?



// 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19

// 11 2 | 17 0 | 16 8 | 6 15 | 10 3 | 21 1 | 18 9 | 14 19						niveau 1
// 2 [11] | 0 [17] | 8 [16] | 6 [15] | 3 [10] | 1 [21] | 9 [18] | 14 [19]		

// 2 [11] | 0 [17] || 8 [16] | 6 [15] || 3 [10] | 1 [21] || 9 [18] | 14 [19]	niveau 2
// 2 [11] | 0 [17] || 6 [15] | 8 [16] || 3 [10] | 1 [21] || 9 [18] | 14 [19]

// 2 [11] | 0 [17] || 6 [15] | 8 [16] ||| 3 [10] | 1 [21] || 9 [18] | 14 [19]	niveau 3
// 6 [15] | 8 [16] || 2 [11] | 0 [17] ||| 9 [18] | 14 [19] || 3 [10] | 1 [21]

// next would be de tout englober, donc plus de paire de paire de paire... avec quoi comparer, donc fini.

// une fois ce point atteint, on va effectuer initialisation et insertion sur chaque niveau.


// une fois cette etape atteinte, on effectue le merge?


// former une paire = merge ?

// microsecondes = secondes / 1000000 
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

/*template<typename T>
void	printContainer(T &container)
{
	size_t	max_ = 10;
	size_t	size = container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		if (i == max_)
		{
			std:: cout << "[...]" << std::endl;
			return ;
		}
		std::cout << container[i] << ' ';
	}
	std::cout << container[size -1] << std::endl;
}*/

int	parse_arg(char *arg, std::deque<std::pair<unsigned int, unsigned int>>::iterator begin, std::deque<std::pair<unsigned int, unsigned int>>::iterator end)
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



int main(int argc, char **argv)
{
	//std::vector<unsigned int>	vec;
	//std::deque<unsigned int>	deq;
	std::deque<std::pair<unsigned int, unsigned int>>	deq;
    //clock_t						startVec, endVec;
    clock_t 					startDeq, endDeq;
	PmergeMe					p;
	size_t						size;

	//NOT WORKING: 32 57 74 38 39 82 59 90 29 23 51 76 91 43 87 68 93 9 72 47 25
	//JACOBSTHAL NOT WORKING:  23 30 60 22 43 27 58 25 38 29 41 37 26 50 53 56 47 44 55 45 39 62 48 46 59 33 28 57
	
	if (argc < 3)
	{
		std::cerr << "Error: not enough arguments." << std::endl;
		return (0);
	}

	size = argc -1;
	if (size % 2 != 0)
	{
		int tmp = parse_arg(argv[size -1], deq.begin(), deq.end());
		p.getDataDeq().remaining.push_back(tmp);
		size --;
	}
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		int tmp0 = parse_arg(argv[i + 1], deq.begin(), deq.end());
		int tmp1 = parse_arg(argv[i + 2], deq.begin(), deq.end());
		if (tmp0 == -1 || tmp1 == -1)
			return (0);
		static_cast<unsigned int>(tmp0);
		static_cast<unsigned int>(tmp1);
		std::pair<unsigned int, unsigned int> pair(tmp0, tmp1);
		//vec.push_back(tmp);
		deq.push_back(pair);
	}
	/*std::cout << "[VEC] Before : ";
	printContainer(vec);

	startVec = clock();
	p.setDataVec(vec.begin(), vec.end());
	t_dataVec	dataVec = p.getDataVec();
	p.sortVector(&dataVec);
	endVec = clock();

	std::cout << "[VEC] After : ";
	printContainer(dataVec.container);
	std::cout << "[VEC] Time to process a range of " << dataVec.container.size() << " elements with std::" << "vector : " << static_cast<double>(endVec - startVec) * 1.0 << " us" << std::endl;
	std::cout << std::endl;*/

	std::cout << "[DEQ] Before : ";
	printContainer(deq);

    startDeq = clock();
	p.setDataDeq(deq.begin(), deq.end());
	t_dataDeq	dataDeq = p.getDataDeq();
	//std::cout << "[DEQ] size = " << dataDeq.container.size() << std::endl;
	p.sortDequeue(&dataDeq);
    endDeq = clock();

	std::cout << "[DEQ] After : ";
	printContainer(dataDeq.container);
	std::cout << "[DEQ] Time to process a range of " << dataDeq.container.size() << " elements with std::" << "deque : " << static_cast<double>(endDeq - startDeq) * 1.0 << " us" << std::endl;
	std::cout << std::endl;

	//if (!is_sorted(size, dataVec.container))
	//	std::cout << RED << "check: [VEC] KO." << DEFAULT << std::endl;
	if (!is_sorted(size, dataDeq.container))
		std::cout << RED << "check: [DEQ] KO." << DEFAULT << std::endl;
	//if (is_sorted(size, dataVec.container) && is_sorted(size, dataDeq.container))
	else
		std::cout << GREEN << "check: OK." << DEFAULT << std::endl;
	return (1);
}