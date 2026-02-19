#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <algorithm>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class NotFoundException: public std::exception
{
	public:
        virtual const char *what() const throw()
        {
            return ("Exception : Value not found in container.");
        }
};

template<typename T>
void	easyfind(T container, int n)
{
	typename T::iterator it;

	std::cout << YELLOW << "[DEBUG] : trying to find " << n << DEFAULT << std::endl;
	it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw NotFoundException();
	std::cout << "Value found in container." << std::endl;
}

#endif