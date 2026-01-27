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
			{
				std::cout << "Error" << std::endl;
				return ;
			}
	}
    while (getline(ss, element, ' '))
        this->expression.push(element);
}

std::queue<int>	RPN::getQueue() const
{
	return (this->expression);
}

void	RPN::printRes()
{
	double		res = 0;
	
	int			tmp;
	char		operator_;
	double		operated;

	//std::cout << "first front = " << this->expression.front() << std::endl;
	tmp = this->expression.front();
	std::cout << "first = " << res << std::endl;
	if (!isdigit(tmp))
	{
		std::cout << "Error: first not a digit" << std::endl;
		return ;
	}
	res += tmp;
	this->expression.pop();

	while (this->expression.size())
	{
		tmp = this->expression.front();
		if (!isdigit(tmp))
		{
			std::cout << "Error: not a digit" << std::endl;
			break;
		}
		operated = tmp;
		this->expression.pop();

		operator_ = char(this->expression.front());
		if (operator_ == '+')
			res += operated;
		else if (operator_ == '-')
			res -= operated;
		else if (operator_ == '/')
			res /= operated;
		else if (operator_ == '*')
			res *= operated;
		else
		{
			std::cout << "Error: not an operator" << std::endl;
			break;
		}
		this->expression.pop();
	}
	std::cout << res << std::endl;
}
