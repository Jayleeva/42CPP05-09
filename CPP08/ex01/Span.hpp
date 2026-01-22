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
		Span(unsigned int N);
		Span(Span const &original);
		Span &operator=(Span const &original);
		~Span();

		void	addNumber(int i);
		int		shortestSpan();
		int		longestSpan();

		void	addRange(std::vector<int> container);

		std::vector<int>	getContainer() const;

	private:
		Span();
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
				return ("Exception : Container is already full.");
			}
		};
};

std::ostream &operator<<(std::ostream &out, Span const &s);

#endif