#include "PmergeMe.hpp"

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


void	is_sorted(size_t size, t_dataVec *dataVec, t_dataDeq *dataDeq)
{

	if (size != dataVec->container.size() || size != dataDeq->container.size())
	{
		std::cout << RED << "check: KO." << DEFAULT << std::endl;
		return ;
	}
	for (size_t i = 0; i + 1 < dataVec->container.size(); i++)
	{
		if (dataVec->container[i] > dataVec->container[i + 1])
		{
			std::cout << RED << "check: KO." << DEFAULT << std::endl;
			return ;
		}	
	}
	for (size_t i = 0; i + 1 < dataDeq->container.size(); i++)
	{
		if (dataDeq->container[i] > dataDeq->container[i + 1])
		{
			std::cout << RED << "check: KO." << DEFAULT << std::endl;
			return ;
		}	
	}
	std::cout << GREEN << "check: OK." << DEFAULT << std::endl;
}

template<typename T>
void	printContainer(T &container)
{
	size_t	size = container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		std::cout << container[i] << ' ';
	}
	std::cout << container[size -1] << std::endl;
}



int main(void)
{
	std::vector<unsigned int>	vec;
	std::deque<unsigned int>	deq;
    clock_t						startVec, endVec;
    clock_t 					startDeq, endDeq;
	PmergeMe					p;
	size_t						size;

	//NOT WORKING: 32 57 74 38 39 82 59 90 29 23 51 76 91 43 87 68 93 9 72 47 25
	
	ssize_t range_max = 42;
	ssize_t range_min = 21;
	size_t	range = range_max - range_min + 1;
	std::srand((unsigned) time(0));
	size = rand() % range + range_min;

	for (size_t i = 0; i < size; i++)
	{
		int tmp = rand() % range_max + range_min;
		while (find(vec.begin(), vec.end(), tmp) != vec.end())
			tmp = rand() % range_max + range_min;
		vec.push_back(tmp);
		deq.push_back(tmp);
	}

	std::cout << "Before : ";
	printContainer(vec);

	startVec = clock();
	p.setDataVec(vec.begin(), vec.end());
	t_dataVec	dataVec = p.getDataVec();
	p.sortVector(&dataVec);
	endVec = clock();

	std::cout << "After : ";
	printContainer(dataVec.container);
	std::cout << "Time to process a range of " << size << " elements with std::" << "vector : " << double(1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC) << " us" << std::endl;

    startDeq = clock();
	p.setDataDeq(deq.begin(), deq.end());
	t_dataDeq	dataDeq = p.getDataDeq();
	p.sortDequeue(&dataDeq);
    endDeq = clock();
	std::cout << "Time to process a range of " << size << " elements with std::" << "deque : " << double(1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC) << " us" << std::endl;

	is_sorted(size, &dataVec, &dataDeq);
	return (0);
}