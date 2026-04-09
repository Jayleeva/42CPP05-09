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
	
	if (VERBIOSE)
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

	if (n < 2)
		return;

	if (n > 2 && n < 6)
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

	if (n > 2 && isdigit(arg[n -2]))
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

void	initialize_data(t_data *data)
{
	data->operand.full = false;
	data->operated.full = false;
}

void	RPN::printRes()
{
	t_data		data;
	std::string	str;
	long		res;
	long		tmpres;
	char		c;

	initialize_data(&data);

	if (this->expression.size() <= 1)
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
				str.push_back(*this->expression.front().c_str());
				countdigit ++;
				i ++;
				this->expression.pop();
				c = *this->expression.front().c_str();
			}
			//std::cout << "str = " << str << std::endl;
			if (countdigit == 1)
			{
				if (i > 1)
				{
					fill_number(&data.operand, res);
					fill_number(&data.operated, static_cast<long>(*(str.end() -1) - '0'));
					str.erase(str.end() -1);
					//std::cout << "str = " << str << std::endl;
					data.op = c;
					this->expression.pop();
					res = operate(&data);
					fill_number(&data.operand, res);
					data.operated.full = false;
				}
				else
					throw InvalidArgumentException();
			}

			if (countdigit >= 2)
			{
				while (countdigit >= 2)
				{
					t_data	newdata;
					fill_number(&newdata.operated, static_cast<long>(*(str.end() -1) - '0'));
					str.erase(str.end() -1);
					//std::cout << "str = " << str << std::endl;
					fill_number(&newdata.operand, static_cast<long>(*(str.end() -1) - '0'));
					str.erase(str.end() -1);
					//std::cout << "str = " << str << std::endl;
					newdata.op = c;
					this->expression.pop();
					tmpres = operate(&newdata);

					countdigit -= 2;

					if (countdigit == 0)
					{
						fill_number(&data.operand, tmpres);
						res = tmpres;
					}
					else if (countdigit >= 1)
					{
						fill_number(&data.operated, tmpres);
						fill_number(&data.operand, static_cast<long>(*(str.end() -1) - '0'));
						str.erase(str.end() -1);
						//std::cout << "str = " << str << std::endl;					
						break;
					}
				}
			}
		}
		else // NOPE
		{			
			std::cout << "str = " << *(str.end() -1) - '0' << " operand = " << data.operand.value << " operated = " << data.operated.value << std::endl;
			if (data.operand.full) // && !data.operated.full)
			{
				std::cout << "here\n";
				long	tmpval = data.operand.value;
				fill_number(&data.operated, tmpval);
			}
			if (!str.empty())
			{
				std::cout << "not empty\n";
				fill_number(&data.operand, static_cast<long>(*(str.end() -1) - '0'));
				str.erase(str.end() -1);
			}
			else
			{
				std::cout << "empty\n";
				fill_number(&data.operand, data.operated.value);
			}


			std::cout << "operand = " << data.operand.value << " operated = " << data.operated.value << std::endl;
			
			data.op = c;
			this->expression.pop();
			res = operate(&data);
			initialize_data(&data);
			fill_number(&data.operated, res);
			i ++;
		}
	}
	std::cout << res << std::endl; 
}
