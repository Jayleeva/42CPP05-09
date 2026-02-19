#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <stack>

int main(void)
{
	{
		std::cout << "Main 1:\n***\nShould test easyfind on a vector of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::vector<int>			v;
		std::vector<int>::iterator	it;

		v.push_back(12);
		v.push_back(23);
		v.push_back(34);

		for (it = v.begin(); it != v.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			easyfind(v, 12);
			easyfind(v, 45);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 2:\n***\nShould test easyfind on a list of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::list<int>				l;
		std::list<int>::iterator	it;
		
		l.push_back(45);
		l.push_back(56);
		l.push_back(67);

		for (it = l.begin(); it != l.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			easyfind(l, 56);
			easyfind(l, 78);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 3:\n***\nShould test easyfind on a dequeue of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::deque<int>				d;
		std::deque<int>::iterator	it;

		d.push_back(78);
		d.push_back(89);
		d.push_back(91);

		for (it = d.begin(); it != d.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			easyfind(d, 91);
			easyfind(d, 12);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 4:\n***\nShould test easyfind on a dequeue of float. Neither values should be found, since easyfind can only search int.\n-----" << std::endl;
		std::deque<float>			d;
		std::deque<float>::iterator	it;

		d.push_back(1.2);
		d.push_back(2.3);
		d.push_back(3.4);

		for (it = d.begin(); it != d.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			easyfind(d, 1.2);
			easyfind(d, 1);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	return (0);
}