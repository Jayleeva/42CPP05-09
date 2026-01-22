#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <algorithm>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class Span
{
	public:
		Span();
		Span(unsigned int N);
		Span(Span const &original);
		Span &operator=(Span const &original);
		~Span();

		void	addNumber(int i);
		int		shortestSpan();
		int		longestSpan();

		void	addMultipleNumbers(std::vector<int> container);

	private:
		std::vector<int>	container;

		class NoNumberStoredException : public std::exception
		{
			virtual const char *what() const throw()
			{
				return ("Exception : No number stored.");
			}
		};

		class FullException : public std::exception
		{
			virtual const char *what() const throw()
			{
				return ("Exception : Container is full.");
			}
		};
};

#endif