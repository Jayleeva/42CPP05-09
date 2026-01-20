#ifndef ARRAY_HPP
# define ARRAY_HPP

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

# include <iostream>

template <typename T>
class Array
{
  public:
    Array();
    Array(unsigned int n);
    Array(Array const &original);
    Array const &operator=(Array const &original);
    ~Array();
  
		T				&operator[](unsigned int i) const;
  
    unsigned int  size() const;

  private:
    T             *arr;
    unsigned int  n;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, Array<T> &arr);

#endif