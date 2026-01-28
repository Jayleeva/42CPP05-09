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

// 11 2 | 17 0 | 16 8 | 6 15 | 10 3 | 21 1 | 18 9 | 14 19
// 2 [11] | 0 [17] | 8 [16] | 6 [15] | 3 [10] | 1 [21] | 9 [18] | 14 [19]

// 2 [11] | 0 [17] || 8 [16] | 6 [15] || 3 [10] | 1 [21] || 9 [18] | 14 [19]
// 2 [11] | 0 [17] || 6 [15] | 8 [16] || 3 [10] | 1 [21] || 9 [18] | 14 [19]

// 2 [11] | 0 [17] || 6 [15] | 8 [16] ||| 3 [10] | 1 [21] || 9 [18] | 14 [19]
// 6 [15] | 8 [16] || 2 [11] | 0 [17] ||| 9 [18] | 14 [19] || 3 [10] | 1 [21]

// 6 [15] | 8 [16] || 2 [11] 0 [17] ||| 9 [18] | 14 [19] || 3 [10] | 1 [21] already "sorted"

// next would be de tout englober, donc plus de paire de paire de paire... avec quoi comparer, donc fini.

// une fois ce point atteint,

int main(void)
{
	return (0);
}