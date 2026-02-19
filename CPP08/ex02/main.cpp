#include "MutantStack.hpp"
#include <list>

int	main(void)
{
	/*{
		MutantStack<int>	logan;

		logan.push(12);
		logan.push(23);
		logan.push(34);
		logan.push(45);
	
		std::cout << "top = " << logan.top() << std::endl;
		std::cout << "size = " << logan.size() << std::endl;
		logan.pop();
		std::cout << "top = " << logan.top() << std::endl;

		for (MutantStack<int>::iterator	it = logan.begin(); it != logan.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		logan.begin(); // const
		logan.end(); // const

		for (MutantStack<int>::reverse_iterator	it = logan.rbegin(); it != logan.rend(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		logan.rbegin(); // const
		logan.rend(); // const
	}*/
	{
		std::cout << "Main 1\n***Subject given main\n-------" << std::endl;
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << mstack.top() << std::endl;
	
		mstack.pop();

		std::cout << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		std::stack<int> s(mstack);
	}
	{
		std::cout << "Main 1\n***Subject given main, MutantStack replaced with list, should have same output.\n-------" << std::endl;
		std::list<int> mstack;

		mstack.push_back(5);
		mstack.push_back(17);

		std::cout << mstack.front() << std::endl;
	
		mstack.pop_front();

		std::cout << mstack.size() << std::endl;

		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		//[...]
		mstack.push_back(0);

		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		//std::list<int> s(mstack);
	}
	return (0);
}
