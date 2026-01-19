#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
    Serializer  siri;
    Data        obj;
    uintptr_t   uiptr;
    Data        *compare;

    obj.check = "Am I the same?";
    uiptr = siri.serialize(&obj);
    compare = siri.deserialize(uiptr);

    std::cout << "obj = " << obj.check << std::endl;
    std::cout << "compare = "  << compare->check << std::endl;
    if (compare == &obj)
        std::cout << "GG!! it's the same!" << std::endl;
    else
        std::cout << "Booooo!! it's not the same! You suck!!" << std::endl;
    return (0);
}