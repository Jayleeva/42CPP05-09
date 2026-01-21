#include "easyfind.hpp"
//#include <array> 
#include <vector>
#include <list>
#include <deque>

int main(void)
{
	/*{
		std::cout << "Main 0:\n***\nShould test easyfind on an array of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::array<int> arr;

		arr.push_back(12);
		arr.push_back(23);
		arr.push_back(34);

		std::cout << arr[0] << std::endl;
		std::cout << arr[1] << std::endl;
		std::cout << arr[2] << std::endl;

		try
		{
			easyfind(arr, 34);
			easyfind(arr, 67);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}*/
	{
		std::cout << "Main 1:\n***\nShould test easyfind on a vector of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::vector<int>	v;
		
		v.push_back(12);
		v.push_back(23);
		v.push_back(34);

		std::cout << v[0] << std::endl;
		std::cout << v[1] << std::endl;
		std::cout << v[2] << std::endl;

		try
		{
			easyfind(v, 34);
			easyfind(v, 67);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 2:\n***\nShould test easyfind on a list of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::list<int>	l;
		
		l.push_back(12);
		l.push_back(23);
		l.push_back(34);

		/*for (int i : l)
			std::cout << i << std::endl;*/

		try
		{
			easyfind(l, 34);
			easyfind(l, 67);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 3:\n***\nShould test easyfind on a dequeue of int. First value should be found, second should throw an exception.\n-----" << std::endl;
		std::deque<int>	d;
		
		d.push_back(12);
		d.push_back(23);
		d.push_back(34);

		std::cout << d[0] << std::endl;
		std::cout << d[1] << std::endl;
		std::cout << d[2] << std::endl;

		try
		{
			easyfind(d, 34);
			easyfind(d, 67);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	{
		std::cout << "Main 4:\n***\nShould test easyfind on a dequeue of float. Neither values should be found.\n-----" << std::endl;
		std::deque<float>	d;
		
		d.push_back(1.2);
		d.push_back(2.3);
		d.push_back(3.4);

		std::cout << d[0] << std::endl;
		std::cout << d[1] << std::endl;
		std::cout << d[2] << std::endl;

		try
		{
			easyfind(d, 1);
			easyfind(d, 1.2);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "===========" << std::endl;
	}
	return (0);
}