#include "Span.hpp"

Span::Span()
{
    std::cout << YELLOW << "[SPAN]: Default constructor called" << DEFAULT << std::endl;
}

Span::Span(unsigned int N)
{
	this->container.reserve(N);
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
	{
		this->container.reserve(original.container.capacity());
		this->container = original.container;
	}
    std::cout << YELLOW << "[SPAN]: Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

Span::~Span()
{
    std::cout << YELLOW << "[SPAN]: Default destructor called" << DEFAULT << std::endl;
}


void	Span::addNumber(int i)
{
	if (this->container.size() == this->container.capacity())
		throw FullException();
	this->container.push_back(i);
}

int		Span::shortestSpan()
{
	int							N = this->container.size();
	std::vector<int> 			tmp(this->container);

	if (N <= 1)
		throw NoNumberStoredException();

	std::sort(tmp.begin(), tmp.end());
	int shortest = tmp[1] - tmp[0]; // base de comparaison

	for (int i = 2; i < N; i ++)
	{
		if (tmp[i] - tmp[i - 1] < shortest)
			shortest = tmp[i] - tmp[i - 1];
	}
	return (shortest);
}

int		Span::longestSpan()
{
	int					N = this->container.size();
	std::vector<int>	tmp(this->container);

	if (N <= 1)
		throw NoNumberStoredException();
	std::sort(tmp.begin(), tmp.end());
	return (tmp[N -1] - tmp[0]);
}

void	Span::addRange(std::vector<int> range)
{
	std::vector<int>::iterator begin = range.begin();
	std::vector<int>::iterator end = range.end();

	if (range.size() > this->container.capacity())
		throw FullException();
	this->container.insert(this->container.end(), begin, end);
}

std::vector<int>	Span::getContainer() const
{
	return(this->container);
}

std::ostream &operator<<(std::ostream &out, Span const &s)
{
	std::vector<int>	tmp = s.getContainer();
	int	N = tmp.size();

	for (int i = 0; i < N; i ++)
	{
		if (i == N -1)
			out << tmp[i];
		else
			out << tmp[i] << ", ";
	}
	return (out);
}