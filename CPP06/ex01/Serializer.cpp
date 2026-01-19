#include "Serializer.hpp"

Serializer::Serializer()
{
    std::cout << YELLOW << "[SERIALIZER] : Default constructor called." << DEFAULT << std::endl;
}

Serializer::Serializer(const Serializer &original)
{
    std::cout << YELLOW << "[SERIALIZER] : Copy constructor called." << DEFAULT << std::endl;
    *this = original;
}

Serializer &Serializer::operator=(const Serializer &original)
{
    std::cout << YELLOW << "[SERIALIZER] : Assignment operator overload called." << DEFAULT << std::endl;
    (void)original;
    return (*this);
}

Serializer::~Serializer()
{
    std::cout << YELLOW << "[SERIALIZER] : Default destructor called." << DEFAULT << std::endl;
}

uintptr_t Serializer::serialize(Data* ptr)
{
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return (reinterpret_cast<Data*>(raw));
}