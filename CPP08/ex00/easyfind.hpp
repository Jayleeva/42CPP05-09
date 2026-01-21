#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <algorithm>


class NotFoundException: public std::exception
{
	public:
        virtual const char *what() const throw()
        {
            return ("Exception : Value not in container.");
        }
};

template<typename F, typename T>
void	easyfind(T container, int n)
{
	typename T::iterator it;

	it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw NotFoundException();
	std::cout << "Value " << n << " found in container." << std::endl;
}

#endif