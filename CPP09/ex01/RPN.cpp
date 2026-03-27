#include "RPN.hpp"

RPN::RPN()
{
	//std::cout << YELLOW << "[RPN] : Default constructor called." << DEFAULT << std::endl;
}

RPN::RPN(RPN const &original)
{
	//std::cout << YELLOW << "[RPN] : Copy constructor called." << DEFAULT << std::endl;
	*this = original;
}

RPN &RPN::operator=(RPN const &original)
{
	if (this != &original)
	{
		this->expression = original.expression;
	}
	//std::cout << YELLOW << "[RPN] : Assignment operator overload called." << DEFAULT << std::endl;
	return (*this);
}

RPN::~RPN()
{
	//std::cout << YELLOW << "[RPN] : Default destructor called." << DEFAULT << std::endl;
}


std::string	trimSpaces(std::string arg)
{
	int	i = 0;
	while (arg[i] == ' ')
		i ++;
	arg = arg.substr(i, arg.size());

	int j = 0;
	while (arg[j])
	{
		int k = 0;
		while (arg[j + k] == ' ')
			k ++;
		if (k > 1)
		{
			k --;
			while (k)
			{
				arg.erase(j + k, 1);
				k --;
			}
		}
		j ++;
	}
	return (arg);
}
void	RPN::setQueue(std::string arg)
{
	arg = trimSpaces(arg);

	std::string			element;
    std::stringstream 	ss(arg);
	int					countdigit;
	int					n = 0;
		
	for (int i = 0; arg[i]; i++)
	{
		if (!isdigit(arg[i])
			&& arg[i] != '+' && arg[i] != '-'
			&& arg[i] != '/' && arg[i] != '*'
			&& arg[i] != ' ')
			throw InvalidArgumentException();
		n ++;
	}

	for (int i = 0; arg[i]; i++)
	{
		if (i % 2 != 0 && arg[i] != ' ')
			throw InvalidArgumentException();
	}

	if (n == 3)
	{
		//std::cout << "not enough args\n";
		throw InvalidArgumentException();
	}

	if (n == 0)
	{
		return;
	}

	/*if (n > 2)
	{
		for (int i = 0; i <= 2; i+= 2)
		{
			if (i <= 2 && !isdigit(arg[i]))
			{
				//std::cout << "first not digits\n";
				throw InvalidArgumentException();
			}
		}
	}*/

	if (!isdigit(arg[0]))
	{
		//std::cout << "first not digit\n";
		throw InvalidArgumentException();
	}

	if (n > 4)
	{
		countdigit = 0;
		for (int i = 4; i < n; i+= 2)
		{
			if (!arg[i])
			{
				throw InvalidArgumentException();
			}
			if (!isdigit(arg[i]))
			{
				if (countdigit > 1 && countdigit % 2 != 0)
				{
					//std::cout << "expected a digit " << std::endl;
					throw InvalidArgumentException();
				}
				int j;
				for (j = 2; j < countdigit * 2; j += 2)
				{
					if (!arg[i + j] || (arg[i + j] && isdigit(arg[i + j])))
					{
						//std::cout << "expected an operator " << std::endl;
						throw InvalidArgumentException();
					}
				}
				countdigit = 0;
				i += j - 2;
			}
			else
			{
				if (i == 4)
				{
					//std::cout << "expected an operator for first operation " << std::endl;
					throw InvalidArgumentException();
				}
				countdigit ++;
			}
		}
	}

	if (arg[n -1] == ' ')
		n --;
	if (n > 1 && isdigit(arg[n -1]))
	{
		//std::cout << "finish with digit (" << arg[n-1] << ")" << std::endl;
		throw InvalidArgumentException();
	}

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
		
	//if (this->expression.size() == 2)
	//	throw InvalidArgumentException();

	int	i = 0;
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
		i ++;
	}
	std::cout << res << std::endl; 
}
