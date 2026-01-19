#ifndef GENANDID_HPP
# define GENANDID_HPP

# include <iostream>
# include <ctime>
# include <cstdlib>
# include "Base.hpp"
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"


Base    *generate(void);
void    identify(Base* p);
void    identify(Base& p);

Base    *testAptr(Base *p);
Base    *testBptr(Base *p);
Base    *testCptr(Base *p);
int     testAref(Base &p);
int     testBref(Base &p);
int     testCref(Base &p);

#endif