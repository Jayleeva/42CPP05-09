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
	if (arg[j -1] != ' ')
		arg.push_back(' ');
	return (arg);
}
void	RPN::setQueue(std::string arg)
{
	arg = trimSpaces(arg);

	std::string			element;
    std::stringstream 	ss(arg);
	int					countdigit;
	int					n = 0;
	
	std::cout << arg << std::endl;
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

	if (n < 2)
		return;

	if (n > 2 && n < 6)
		throw InvalidArgumentException();

	if (!isdigit(arg[0]))
		throw InvalidArgumentException();

	if (n > 2)
	{
		countdigit = 0;
		for (int i = 2; i < n; i+= 2)
		{
			if (arg[i] && !isdigit(arg[i]))
			{
				int countop = 0;
				int j = 0;
				while (arg[i + j] && (!isdigit(arg[i + j])))
				{
					countop ++;
					j += 2;
				}
				if (countdigit != countop)
				{
					throw InvalidArgumentException();
				}
				countdigit = 0;
				i += j - 2;
			}
			else
			{
				countdigit ++;
			}
		}
	}

	if (n > 2 && isdigit(arg[n -1]))
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
	std::queue<std::string>	tmp;
	long		res;
	long		tmpres;
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

	if (this->expression.size() < 3)
		throw InvalidArgumentException();

	int	i = 0;
	int countdigit = 0;
	//int countop = 0;
	while (this->expression.size())
	{
		c = *this->expression.front().c_str();

		if ((i == 0 || i == 1) && !isdigit(c))
			throw InvalidArgumentException();

		if (isdigit(c))
		{
			countdigit = 0;
			while (isdigit(c))
			{
				tmp.push(this->expression.front());
				countdigit ++;
				i ++;
				this->expression.pop();
				c = *this->expression.front().c_str();
			}
			
			if (countdigit == 1)
			{
				if (i > 1)
				{
					std::cout << "   one digit after start\n";
					fill_number(&data.operand, res);
					fill_number(&data.operated, static_cast<long>(*tmp.front().c_str() - '0'));
					tmp.pop();
					data.op = c;
					this->expression.pop();
					res = operate(&data);
					fill_number(&data.operand, res);
					data.operated.full = false;
				}
				else
					throw InvalidArgumentException();
			}

			if (countdigit == 2) //&& countop >= 1) faudra gerer les plus de deux
			{
				std::cout << "   2 digits no matter where\n";

				t_data	newdata;
				std::cout << "front = " << *tmp.front().c_str() - '0' << std::endl;
				fill_number(&newdata.operand, static_cast<long>(*tmp.front().c_str() - '0'));
				tmp.pop();
				fill_number(&newdata.operated, static_cast<long>(*tmp.front().c_str() - '0'));
				tmp.pop();
				newdata.op = c;
				this->expression.pop();
				tmpres = operate(&newdata);
				if (!data.operand.full)
				{
					fill_number(&data.operand, tmpres);
					res = tmpres;
				}
				else if (data.operand.full && !data.operated.full)
					fill_number(&data.operated, tmpres);
			}
			else if (countdigit > 2)
			{
				std::cout << "not handled for now\n";
				return ;
			}
		}
		else
		{
			std::cout << "   operator\n";
			if (data.operand.full && data.operated.full)
			{
				data.op = c;
				this->expression.pop();
				res = operate(&data);
				initialize_data(&data);
			}
			else
				throw InvalidArgumentException();
			i ++;
		}
	}

	//std::cout << "operand full = " << data.operand.full << " operated full = " << data.operated.full << std::endl;

	std::cout << res << std::endl; 
}
