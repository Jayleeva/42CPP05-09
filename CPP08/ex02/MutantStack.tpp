#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>()
{
    std::cout << YELLOW << "[MUTANT]: Default constructor called" << DEFAULT << std::endl;
}

template <typename T>
MutantStack<T>::MutantStack(MutantStack const &original) : std::stack<T>(original)
{
	*this = original;
    std::cout << YELLOW << "[MUTANT]: Copy constructor called" << DEFAULT << std::endl;
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(MutantStack const &original)
{
	if (this != &original)
	{

	}
    std::cout << YELLOW << "[MUTANT]: Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

template <typename T>
MutantStack<T>::~MutantStack()
{
    std::cout << YELLOW << "[MUTANT]: Default destructor called" << DEFAULT << std::endl;
}

template <typename T>
MutantStack<T>::iterator MutantStack<T>::begin()
{
	return (std::stack<T>::c.begin());
}

template <typename T>
MutantStack<T>::iterator MutantStack<T>::end()
{
	return (std::stack<T>::c.end());
}

template <typename T>
MutantStack<T>::const_iterator MutantStack<T>::begin() const
{
	return (std::stack<T>::c.begin());
}

template <typename T>
MutantStack<T>::const_iterator MutantStack<T>::end() const
{
	return (std::stack<T>::c.end());
}

template <typename T>
MutantStack<T>::reverse_iterator MutantStack<T>::rbegin()
{
	return (std::stack<T>::c.rbegin());
}

template <typename T>
MutantStack<T>::reverse_iterator MutantStack<T>::rend()
{
	return (std::stack<T>::c.rend());
}


template <typename T>
MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const
{
	return (std::stack<T>::c.rbegin());
}

template <typename T>
MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const
{
	return (std::stack<T>::c.rend());
}
