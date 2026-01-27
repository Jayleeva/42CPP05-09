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
        this->expression.push(element);
}

std::queue<std::string>	RPN::getQueue() const
{
	return (this->expression);
}

void	RPN::printRes()
{
	long		res;
	char		tmp;
	char		operator_;
	long		operated;

	tmp = *this->expression.front().c_str();
	if (!isdigit(tmp))
	{
		std::cout << "Error: first not a digit" << std::endl;
		return ;
	}
	res = atol(&tmp);
	this->expression.pop();
	std::cout << "first =" << res << std::endl;
	while (this->expression.size())
	{
		tmp = *this->expression.front().c_str();
		if (!isdigit(tmp))
		{
			std::cout << "Error: not a digit" << std::endl;
			break;
		}
		operated = atol(&tmp);
		this->expression.pop();

		operator_ = *this->expression.front().c_str();
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
		std::cout << "temp res = " << res << std::endl;
	}
	std::cout << res << std::endl;
}
