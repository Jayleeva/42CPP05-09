#include "ScaleConverter.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    convert(argv[1].c_str());
    return (0);
}