#include "MutantStack.hpp"

int	main(void)
{
	{
		MutantStack<int>	logan;

		logan.push(42);
		logan.top();
		logan.size();
		logan.pop();

		logan.begin();
		logan.end();
		logan.begin(); // const
		logan.end(); // const
		logan.rbegin();
		logan.rend();
		logan.rbegin(); // const
		logan.rend(); // const
	}
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
	return (0);
}
