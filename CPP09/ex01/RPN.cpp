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
	int					countdigit = 0;
	int					countop = 0;
	//bool				check = true;

	for (int i = 0; arg[i]; i++)
	{
		if (isdigit(arg[i]))
			countdigit ++;
		else if (arg[i] == '+' || arg[i] == '-'
			|| arg[i] == '/' || arg[i] == '*')
			countop ++;
		else if (arg[i] != ' ')
			throw InvalidArgumentException();
	}

	int	checkdigit = 0;
	int	checkop = 0;
	for (int i = 0; arg[i]; i ++)
	{
		if (!isdigit(arg[i]) && arg[i] != ' ')
			checkop ++;
		else
			checkdigit ++;
		if (checkdigit == 3 && )

	}

	std::cout << "countdigit = " << countdigit << " countop = " << countop << std::endl;
	if ((countdigit % 2 == 0 && countop % 2 == 0)  
		|| (countdigit % 2 != 0 && countop % 2 != 0))
		throw InvalidArgumentException();

    while (getline(ss, element, ' '))
		this->expression.push(element);        
}

std::queue<std::string>	RPN::getQueue() const
{
	return (this->expression);
}

void	fill_number(t_number *n, long value)
{
	n->value = value;
	n->full = true;
}


long	operate(t_data *data)
{
	long	res = data->operand.value;

	if (VERBIOSE)
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

	if (VERBIOSE)
		std::cout << " = " << res << std::endl;
	return (res);
}

char	nextExpression(t_data *data, std::queue<std::string> &container)
{
	char	c;
	int		i = 0;
	
	if (data->operand.full)
		i ++;

	while (i < 3)
	{
		c = *container.front().c_str();
		if (i == 0 && isdigit(c))
			fill_number(&data->operand, static_cast<long>(c - '0'));
		else if (i == 1 && isdigit(c))
			fill_number(&data->operated, static_cast<long>(c - '0'));
		else if (i == 2 && !isdigit(c))
			data->op = c;		
		container.pop();
		i ++;
	}
	return (c);
}

void	initialize_data(t_data *data)
{
	data->operand.full = false;
	data->operated.full = false;
}

void	RPN::printRes()
{
	t_data		data;
	long		res;
	char		c;

	initialize_data(&data);

	if (this->expression.size() == 1)
	{
		c = *this->expression.front().c_str();
		if (isdigit(c))
		{
			std::cout << c << std::endl;
			return ;
		}
		else
			throw InvalidArgumentException();
	}
		
	if (this->expression.size() == 2)
		throw InvalidArgumentException();

	while (this->expression.size())
	{
		c = nextExpression(&data, this->expression);
		
		if (isdigit(c))
		{
			t_data	newdata;

			fill_number(&newdata.operand, data.operated.value);
			fill_number(&newdata.operated, static_cast<long>(c - '0'));
			c = *this->expression.front().c_str();
			this->expression.pop();
			newdata.op = c;

			long tmp = operate(&newdata);
			fill_number(&data.operated, tmp);

			c = *this->expression.front().c_str();
			this->expression.pop();
			data.op = c;
			res = operate(&data);
		}
		else
			res = operate(&data);
		fill_number(&data.operand, res);
		data.operated.full = false;
	}
	std::cout << res << std::endl; 
}
