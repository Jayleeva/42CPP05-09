#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(PmergeMe const &original)
{

}

PmergeMe &PmergeMe::operator=(PmergeMe const &original)
{

}

PmergeMe::~PmergeMe()
{

}


std::vector<unsigned int>	PmergeMe::getContainer() const
{

}

void	PmergeMe::setContainer()
{

}


void	PmergeMe::sortContainer()
{

}



std::ostream &operator<<(std::ostream &out, PmergeMe const &p)
{
	out << p.getContainer() << std::endl;
	return (out);
}