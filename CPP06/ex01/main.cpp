#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
    Data        data;
    uintptr_t   uiptr;
    Data        *compare;

    data.str = "Am I the same?";
    uiptr = Serializer::serialize(&data);
    compare = Serializer::deserialize(uiptr);

    std::cout << "data = " << data.str << std::endl;
    std::cout << "compare = "  << compare->str << std::endl;
    if (compare == &data)
        std::cout << "GG!! it's the same!" << std::endl;
    else
        std::cout << "Booooo!! it's not the same! You suck!!" << std::endl;
    return (0);
}