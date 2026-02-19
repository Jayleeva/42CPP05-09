#include "Span.hpp"
# include <ctime>

int	main(void)
{
	{
		std::cout << "Main 0:\n***Subject given main. Everything should work.\n------" << std::endl;
		Span sp = Span(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "sp =\t\t" << sp << std::endl;
		std::cout << "shortest =\t" << sp.shortestSpan() << std::endl;
		std::cout << "longest =\t" << sp.longestSpan() << std::endl;
		std::cout << "=============" << std::endl;
	}
	{
		std::cout << "Main 1:\n***Testing addRange: should work.\n------" << std::endl;
		std::vector<int>			v;
		std::vector<int>::iterator	it;
		int							n = 5;
		Span						sp = Span(n);
	
		v.reserve(n);
		std::cout << "v = ";
		std::srand((unsigned) time(0));
		//for (int i = 0; i < n; i ++)
		for (it = v.begin(); it != v.end(); ++it)
		{
			int tmp = rand() % n;
			while (find(v.begin(), v.end(), tmp) != v.end())
				tmp = rand() % n;
			v.push_back(tmp);
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		try
		{
			sp.addRange(v);
			std::cout << sp << std::endl;
			std::cout << sp.shortestSpan() << std::endl;
			std::cout << sp.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}
	{
		std::cout << "Main 2:\n***Testing addNumber: should throw FullException.\n------" << std::endl;
		Span				sp = Span(3);
	
		try
		{
			sp.addNumber(6);
			sp.addNumber(3);
			sp.addNumber(17);
			sp.addNumber(9);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}
	{
		std::cout << "Main 3:\n***Testing addRange: should throw FullException.\n------" << std::endl;
		std::vector<int>			v;
		std::vector<int>::iterator	it;

		Span						sp = Span(3);
	
		v.reserve(5);
		std::cout << "v = ";
		int tmp = 1;
		for (it = v.begin(); it != v.end(); ++it)
		{
			v.push_back(tmp++);
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		try
		{
			sp.addRange(v);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}
	{
		std::cout << "Main 4:\n***Testing shortest: should throw NoNumberStoredException.\n------" << std::endl;
		Span	sp = Span(1);

		try
		{
			std::cout << sp.shortestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}
	{
		std::cout << "Main 5:\n***Testing longest: should throw NoNumberStoredException.\n------" << std::endl;
		Span	sp = Span(1);

		try
		{
			std::cout << sp.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}

	{
		std::cout << "Main 5:\n***Testing constructors: everything should work.\n------" << std::endl;
		Span	sp1 = Span(3);
		Span	sp2 = Span(sp1);
		Span	sp3 = sp2;

		for (int i = 0; i < 9; i++)
		{
			if (i < 3)
				sp1.addNumber(i);
			else if (i >= 3 && i < 6)
				sp2.addNumber(i);
			else if (i >= 6 && i < 9)
				sp3.addNumber(i);
		}
		std::cout << sp1 << std::endl;
		std::cout << sp2 << std::endl;
		std::cout << sp3 << std::endl;
	}
	{
		std::cout << "Main 1:\n***Testing addRange with enormous range: should work.\n------" << std::endl;
		std::vector<int>			v;
		std::vector<int>::iterator	it;
		int							n = 1000000;
		Span						sp = Span(n);
	
		v.reserve(n);

		std::srand((unsigned) time(0));
		for (it = v.begin(); it != v.end(); ++it)
		{
			int tmp = rand() % n * 10;
			while (find(v.begin(), v.end(), tmp) != v.end())
				tmp = rand() % n * 10;
			v.push_back(tmp);
		}

		try
		{
			sp.addRange(v);
			std::cout << sp.shortestSpan() << std::endl;
			std::cout << sp.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		std::cout << "=============" << std::endl;
	}
	return (0);
}