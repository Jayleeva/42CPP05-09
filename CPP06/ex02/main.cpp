#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "genandid.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n***\nOne instance of every derived class are tested as pointers then as references. Every one should be identified correctly in both tests.\n-----------" << std::endl;
        A a;
        B b;
        C c;

        identify(&a);
        identify(&b);
        identify(&c);

        identify(a);
        identify(b);
        identify(c);
        std::cout << "==================" << std::endl;
    }

    {
        std::cout << "Main 1:\n***\nAn instance of randomly chosen derived class is tested as a pointer then as a reference.\n-----------" << std::endl;
        Base *test = generate();
        if (test == NULL)
            return (1);
        else
        {
            identify(test);
            identify(*test);
            delete (test);
        }
        std::cout << "==================" << std::endl;
	}
    return (0);
}