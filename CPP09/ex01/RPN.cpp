#include "RPN.hpp"

RPN::RPN()
{
	std::cout << YELLOW << "[RPN] : Default constructor called." << DEFAULT << std::endl;
}

RPN::RPN(RPN const &original)
{
	std::cout << YELLOW << "[RPN] : Copy constructor called." << DEFAULT << std::endl;
	*this = original;
}

RPN &RPN::operator=(RPN const &original)
{
	if (this != &original)
	{
		this->expression = original.expression;
	}
	std::cout << YELLOW << "[RPN] : Assignment operator overload called." << DEFAULT << std::endl;
	return (*this);
}

RPN::~RPN()
{
	std::cout << YELLOW << "[RPN] : Default destructor called." << DEFAULT << std::endl;

}


void	RPN::setQueue(std::string arg)
{
	std::string			element;
    std::stringstream 	ss(arg);

	for (int i = 0; arg[i]; i++)
	{
		if (!isdigit(arg[i])
			&& arg[i] != '+' && arg[i] != '-'
			&& arg[i] != '/' && arg[i] != '*'
			&& arg[i] != ' ')
			std::cout << "Error" << std::endl;
	}

    while (getline(ss, element, ' '))
	{
		//std::cout << "element = " << element << std::endl;
		this->expression.push(element);
	}
        
}

std::queue<std::string>	RPN::getQueue() const
{
	return (this->expression);
}

// si de nouveau 2 chiffres equivalent de parentheses. On fait d'abord l'operation entre les deux chiffres puis l'operation entre le resultat et le dernier resultat avant toute cette merde.
void	RPN::printRes()
{
	long		res;
	char		tmp;
	long		operated = -1;
	//int			full = 0;
	long		tmpop;

	tmp = *this->expression.front().c_str();
	res = static_cast<long>(tmp - '0');
	this->expression.pop();
	//full ++;

	while (this->expression.size())
	{
		//std::cout << "front = " << this->expression.front() << std::endl;
		tmp = *this->expression.front().c_str(); 
		//std::cout << "tmp   = " << *this->expression.front().c_str() << std::endl;
		if (isdigit(tmp))
		{
			operated = static_cast<long>(tmp - '0');
			tmpop = static_cast<long>(tmp - '0');
			//std::cout << "operated = " << operated << std::endl;
		}
		else
		{
			std::cout << res << tmp << operated;
			if (tmp == '+')
				res += operated;
			else if (tmp == '-')
				res -= operated;
			else if (tmp == '/')
			{
				if (operated == 0)
					throw DivisionByZeroException();
				res /= operated;
			}
				
			else if (tmp == '*')
				res *= operated;
			std::cout << " = " << res << std::endl;
			operated = -1;
		}
		this->expression.pop();
	}
	std::cout << res << std::endl; 
}
