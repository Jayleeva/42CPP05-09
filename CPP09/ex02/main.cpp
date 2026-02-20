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


void	is_sorted(size_t size, std::vector<unsigned int> container)
{
	if (size != container.size())
	{
		std::cout << RED << "check: KO." << DEFAULT << std::endl;
		return ;
	}
	for (size_t i = 0; i + 1 < container.size(); i++)
	{
		if (container[i] > container[i + 1])
		{
			std::cout << RED << "check: KO." << DEFAULT << std::endl;
			return ;
		}	
	}
	std::cout << GREEN << "check: OK." << DEFAULT << std::endl;
}

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}

int main(void)
{
	PmergeMe			p;
	size_t				size = 21;
	std::vector<int>	vec;

	std::srand((unsigned) time(0));
	for (size_t i = 0; i < size; i++)
	{
		int tmp = rand() % 100;
		while (find(vec.begin(), vec.end(), tmp) != vec.end())
			tmp = rand() % 100;
		vec.push_back(tmp);
	}

	p.setContainer(vec.begin(), vec.end());
	p.printContainer();

	p.sortContainer();	
	p.printContainer();
	is_sorted(size, p.getContainer());
	return (0);
}