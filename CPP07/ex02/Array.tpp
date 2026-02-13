#include "Array.hpp"

template <typename T>
Array<T>::Array(): arr(NULL), n(0)
{
    std::cout << YELLOW << "[ARRAY]: Default constructor called" << DEFAULT << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n): n(n)
{
    std::cout << YELLOW << "[ARRAY]: Unsigned int constructor called" << DEFAULT << std::endl;

    try
    {
        this->arr = new T[n];

        unsigned int  i = 0;
        while (i < this->n)
        {
            this->arr[i] = 0;
            i ++;
        }
    }
    catch(const std::bad_alloc & e)
    {
        std::cout << e.what() << std::endl;
        this->arr = NULL;
        this->n = 0;
    }
}

template <typename T>
Array<T>::Array(Array const &original): arr(new T[original.n]), n(original.n)
{
    std::cout << YELLOW << "[ARRAY]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

template <typename T>
Array<T> const &Array<T>::operator=(Array const &original)
{
    std::cout << YELLOW << "[ARRAY]: Assignment operator overload called" << DEFAULT << std::endl;

    if (this != &original)
    {
		delete [] this->arr;
		this->n = original.n;
        try
        {
            this->arr = new T[this->n];
            for (unsigned int i = 0; i < this->n; i++)
                this->arr[i] = original.arr[i];
        }
		catch (const std::bad_alloc &e)
        {
            std::cout << e.what() << std::endl;
            this->arr = NULL;
            this->n = 0;
        }
    }
    return (*this);
}

template <typename T>
Array<T>::~Array()
{
    std::cout << YELLOW << "[ARRAY]: Default destructor called" << DEFAULT << std::endl;
    delete [] this->arr;
}

template <typename T>
unsigned int  Array<T>::size() const
{
    return(this->n);
}

template <typename T>
T &Array<T>::operator[](unsigned int i) const
{
	if (i >= this->n)
		throw std::out_of_range("Exception: out of bounds.");
	return (this->arr[i]);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Array<T> &arr)
{
    unsigned int i = 0;

    while (i < arr.size())
    {
        out << arr[i];
        if (i < arr.size() - 1)
            out << ", ";
        i ++;
    }
	return (out);
}