#include "Span.hpp"

Span::Span()
{
	this->N = 0;
    std::cout << YELLOW << "[SPAN]: Default constructor called" << DEFAULT << std::endl;
}

Span::Span(unsigned int N)
{
	this->N = N;
    std::cout << YELLOW << "[SPAN]: Unsigned int constructor called" << DEFAULT << std::endl;
}

Span::Span(Span const &original)
{
	*this = original;
    std::cout << YELLOW << "[SPAN]: Copy constructor called" << DEFAULT << std::endl;
}

Span &Span::operator=(Span const &original)
{
	if (this != &original)
		this->N = original.N;
    std::cout << YELLOW << "[SPAN]: Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

Span::~Span()
{
    std::cout << YELLOW << "[SPAN]: Default destructor called" << DEFAULT << std::endl;
}


void	Span::addNumber(int i)
{

}

int		Span::shortestSpan()
{

}

int		Span::longestSpan()
{

}
