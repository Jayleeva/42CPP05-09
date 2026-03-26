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

bool	is_expression_complete(t_data *data)
{
	if (data->operand.full &&
		data->operated.full &&
		data->op != ' ')
		return (true);
	else
		return (false);
}

void	fill_number(t_number *n, long value)
{
	n->value = value;
	n->full = true;
}


long	operate(t_data *data)
{
	long	res = data->operand.value;

	std::cout << data->operand.value << data->op << data->operated.value;

	if (data->op == '+')
		res += data->operated.value;
	else if (data->op == '-')
		res -= data->operated.value;
	else if (data->op == '/')
	{
		if (data->operated.value == 0)
			throw DivisionByZeroException();
		res /= data->operated.value;
	}
	else if (data->op == '*')
		res *= data->operated.value;

	std::cout << " = " << res << std::endl;
	return (res);
}

// si de nouveau 2 chiffres equivalent de parentheses. On fait d'abord l'operation entre les deux chiffres puis l'operation entre le resultat et le dernier resultat avant toute cette merde.
void	RPN::printRes()
{
	t_data		data;
	long		res;
	char		c;

	while (this->expression.size())
	{
		data.op = ' ';
		//while (!is_expression_complete(&data))
		//{
			c = *this->expression.front().c_str();
			
			if (isdigit(c))
			{
				if (!data.operand.full)
					fill_number(&data.operand, static_cast<long>(c - '0'));
				else if (data.operand.full && data.op != ' ') // && !data.operated.full )
					fill_number(&data.operated, static_cast<long>(c - '0'));
			}
			else
			{
				data.op = c;
			}
			this->expression.pop();
		//}

		if (is_expression_complete(&data))
		{
			res = operate(&data);
			fill_number(&data.operand, res);
			data.operated.full = false;
		}
		//this->expression.pop();
	}
	std::cout << res << std::endl; 
}
